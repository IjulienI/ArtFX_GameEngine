#include "Time.h"

#include <algorithm>
#include <SDL_timer.h>

unsigned int Time::mFrameStart = 0;
unsigned int Time::mFrameTime = 0;
unsigned int Time::mLastFrame = 0;
float Time::deltaTime = 0;

unsigned int Time::ComputeDeltaTime()
{
    mFrameStart = SDL_GetTicks();
    unsigned int dt = mFrameStart - mLastFrame;
    mLastFrame = mFrameStart;
    dt = std::min(dt, MAX_DT);
    deltaTime = dt / 1000.0f;
    return dt;
}

void Time::DelayTime()
{
    mFrameTime = SDL_GetTicks() - mFrameStart;
    if(mFrameTime < FRAME_DELAY)
        SDL_Delay(FRAME_DELAY - mFrameTime);
}
