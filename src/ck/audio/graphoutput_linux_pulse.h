#pragma once

#include "ck/audio/graphoutput.h"
#include "ck/core/thread.h"
#include <pulse/mainloop.h>
#include <pulse/context.h>
#include <pulse/stream.h>


namespace Cki
{


class GraphOutputLinux : public GraphOutput
{
public:
    GraphOutputLinux();
    virtual ~GraphOutputLinux();

protected:
    virtual void startImpl();
    virtual void stopImpl();

private:
	pa_context_state_t m_state;
	pa_mainloop *m_pa;
	pa_context *m_context;
	pa_stream *m_stream;
	pa_buffer_attr m_ba;
    Thread m_thread;
	size_t m_defaultBufBytes;
	bool m_stop;

	bool init();
	void shutdown();
	void stateCallback(pa_context*);
	void writeCallback(pa_stream*, size_t);
	void underflowCallback(pa_stream*);
    void threadLoop();
    static void* threadFunc(void*);
	static void stateFunc(pa_context*, void*);
	static void writeFunc(pa_stream*, size_t, void*);
	static void underflowFunc(pa_stream*, void*);
};


}



