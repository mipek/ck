#include "ck/audio/graphoutput_linux_pulse.h"
#include "ck/audio/audioutil.h"
#include "ck/core/debug.h"
#include "ck/core/mem.h"
#include "ck/core/system.h"
#include "ck/core/logger.h"
#include <pulse/error.h>

namespace Cki
{

GraphOutputLinux::GraphOutputLinux() :
    m_pa(0),
    m_thread(threadFunc),
    m_stop(false)
{
	memset(&m_ba, 0, sizeof(m_ba));

	float bufferMs = System::get()->getConfig().audioUpdateMs;
	float bufferFrames = Math::round(bufferMs * 0.001f * AudioNode::k_maxSampleRate);
	m_defaultBufBytes = bufferFrames * AudioNode::k_maxChannels * sizeof(float);

	m_ba.fragsize = -1;
	m_ba.maxlength = -1;
	m_ba.minreq = -1;
	m_ba.prebuf = -1;
	m_ba.tlength = m_defaultBufBytes;
}

GraphOutputLinux::~GraphOutputLinux()
{
    m_stop = true;
    m_thread.join();
}

bool GraphOutputLinux::init()
{
	const char *applicationName = System::get()->getConfig().applicationName;

	m_pa = pa_mainloop_new();
	m_context = pa_context_new(
			pa_mainloop_get_api(m_pa),
			applicationName ? applicationName : "Cricket-Audio"
	);

	int err = pa_context_connect(m_context, NULL, PA_CONTEXT_NOFLAGS, NULL);
	if (err < 0) {
		CK_LOG_ERROR("Could not connect to the server (%s)", pa_strerror(err));
		return false;
	}
	pa_context_set_state_callback(m_context, stateFunc, this);

	// iterate until we're connected
	int error = 0;
	while (error >= 0 && m_state != PA_CONTEXT_READY) {
		error = pa_mainloop_iterate(m_pa, 1, nullptr);
	}

	if (error < 0) {
		CK_LOG_ERROR("Could connect to pulseaudio (%s)", pa_strerror(err));
		return false;
	}

	pa_sample_spec ss;
	ss.format = PA_SAMPLE_FLOAT32LE;
	ss.rate = AudioNode::k_maxSampleRate;
	ss.channels = AudioNode::k_maxChannels;
	m_stream = pa_stream_new(m_context, "audio stream", &ss, NULL);
	if (!m_stream) {
		CK_LOG_ERROR("Failed to create stream (%s)", pa_strerror(err));
		return false;
	}
	pa_stream_set_write_callback(m_stream, writeFunc, this);
	pa_stream_set_underflow_callback(m_stream, underflowFunc, this);

	//pa_stream_flags flags = pa_stream_flags(PA_STREAM_INTERPOLATE_TIMING | PA_STREAM_ADJUST_LATENCY | PA_STREAM_AUTO_TIMING_UPDATE);
	pa_stream_flags flags = pa_stream_flags::PA_STREAM_NOFLAGS;
	err = pa_stream_connect_playback(m_stream, NULL, &m_ba, flags, NULL, NULL);
	if (err < 0) {
		CK_LOG_ERROR("Failed to connect the stream to sink (%s)", pa_strerror(err));
		return false;
	}

	return true;
}

void GraphOutputLinux::shutdown()
{
	pa_context_disconnect(m_context);
	pa_context_unref(m_context);
	pa_mainloop_free(m_pa);
}

void GraphOutputLinux::startImpl()
{
    m_stop = false;
	m_thread.setName("CK pulse audio");
    m_thread.start(this);
}

void GraphOutputLinux::stopImpl()
{
    m_stop = true;
    m_thread.join();
}

void GraphOutputLinux::stateCallback(pa_context* ctx)
{
	m_state = pa_context_get_state(ctx);
}

void GraphOutputLinux::writeCallback(pa_stream* stream, size_t length)
{
	void *buffer;
	int err = pa_stream_begin_write(stream, (void **) &buffer, &length);
	if (err < 0) {
		CK_LOG_ERROR("Failed to request audio buffer (%s)", pa_strerror(err));
		return;
	}

	int frames = (int)(length / AudioNode::k_maxChannels / sizeof(float));
	if (System::get()->getSampleType() == kCkSampleType_Float) {
		render((float *) buffer, frames);
	} else {
		render((int32 *) buffer, frames);
		AudioUtil::convert((const int32 *) buffer, (float *) buffer, frames);
	}

	err = pa_stream_write(stream, buffer, length, nullptr, 0, PA_SEEK_RELATIVE);
	if (err < 0) {
		CK_LOG_ERROR("Failed to write audio buffer (%s)", pa_strerror(err));
	}
}

void GraphOutputLinux::underflowCallback(pa_stream* stream)
{
	// try increasing out buffer by a few milliseconds when we underflow..
	float additionalBufferMs = 10.0f;
	float additionalFrames = Math::round(additionalBufferMs * 0.001f * AudioNode::k_maxSampleRate);;
	size_t additionalBytes = additionalFrames * AudioNode::k_maxChannels * sizeof(float);

	if (m_ba.tlength + additionalBytes <= m_defaultBufBytes * 5) {
		m_ba.tlength += additionalBytes;
		pa_stream_set_buffer_attr(stream, &m_ba, nullptr, nullptr);
		CK_LOG_INFO("Buffer underflow! increasing buffer size by ~10ms");
	} else {
		CK_LOG_WARNING("Buffer underflow but buffer is already too large!");
	}
}

void GraphOutputLinux::threadLoop()
{
	if (!init()) {
		CK_FAIL("couldn't init pulse audio");
		return;
	}

	int error = 0;
	while(!m_stop && error >= 0) {
		error = pa_mainloop_iterate(m_pa, 1, nullptr);
		if (error < 0) {
			CK_LOG_ERROR("PulseAudio backend error: (%s)", pa_strerror(error));
		}
	}

	shutdown();
}

void* GraphOutputLinux::threadFunc(void* arg)
{
    GraphOutputLinux* me = (GraphOutputLinux*) arg;
    me->threadLoop();
    return NULL;
}

void GraphOutputLinux::stateFunc(pa_context* ctx, void* arg)
{
	GraphOutputLinux* me = (GraphOutputLinux*) arg;
	me->stateCallback(ctx);
}

void GraphOutputLinux::writeFunc(pa_stream* stream, size_t length, void* arg)
{
	GraphOutputLinux* me = (GraphOutputLinux*) arg;
	me->writeCallback(stream, length);
}

void GraphOutputLinux::underflowFunc(pa_stream* stream, void* arg)
{
	GraphOutputLinux* me = (GraphOutputLinux*) arg;
	me->underflowCallback(stream);
}

}


