#pragma once

#include "ck/audio/graphoutput.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

namespace Cki
{


class GraphOutputAndroid : public GraphOutput
{
public:
    GraphOutputAndroid();
    virtual ~GraphOutputAndroid();

protected:
    virtual void startImpl();
    virtual void stopImpl();

private:
    SLObjectItf m_playerObj;
    SLAndroidSimpleBufferQueueItf m_playerBufferQueue;
    SLPlayItf m_playerPlay;
    SLVolumeItf m_playerVolume;

    int m_framesPerBuffer;
    int m_bytesPerBuffer;
    void* m_bufs[2];
    void* m_renderBuf;
    int m_curBuf;

    void* m_primingBuf;
    int m_androidSdkVersion;

    static void bufferDoneCallback(SLAndroidSimpleBufferQueueItf, void *context);
    void bufferDone(SLAndroidSimpleBufferQueueItf);
    static void realizeDoneCallback(SLObjectItf, const void *context, SLuint32 event, SLresult result, SLuint32 param, void* interface);
    void realizeDone();
    void enqueue();
};


}

