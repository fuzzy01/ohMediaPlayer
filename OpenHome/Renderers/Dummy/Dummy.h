#ifndef HEADER_OPENHOME_MEDIAPLAYER_RENDERERS_DUMMY
#define HEADER_OPENHOME_MEDIAPLAYER_RENDERERS_DUMMY

#include <OhNetTypes.h>
#include "..\..\Renderer.h"
#include <Timer.h>
#include <iostream>
#include <string>

namespace OpenHome {
namespace MediaPlayer {

class Dummy : public IRenderer
{
public:
    Dummy();
    ~Dummy();
    virtual void Play(uint32_t aHandle, const ITrack& aTrack, uint32_t aSecond);
    virtual void Pause();
    virtual void Unpause();
    virtual void Stop();
    virtual void FinishAfter(uint32_t aId);
    virtual void SetStatusHandler(IRendererStatus& aStatus);
private:
    void Tick();
    void Prefetch();
private:
    Functor iTickFunctor;
    Timer iTickTimer;
    Functor iPrefetchFunctor;
    Timer iPrefetchTimer;
    IRendererStatus* iStatus;

    uint32_t iHandle;
    uint32_t iId;
    std::string iUri;
    uint32_t iSecond;

    uint32_t iDuration;
};

} // namespace MediaPlayer
} // namespace OpenHome

#endif // HEADER_OPENHOME_MEDIAPLAYER_RENDERERS_DUMMY

