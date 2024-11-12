#pragma once

class Time
{
public:
    Time() = default;
    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;

    static unsigned int ComputeDeltaTime();
    static void DelayTime();

    static float deltaTime;

private:
    const static unsigned int FPS = 60;
    const static unsigned int FRAME_DELAY = 1000 / FPS;
    //Maximum Delta Time
    const static unsigned int MAX_DT = 50; 

    //Time when current frame started
    static unsigned int mFrameStart;  
    //Last frame start time 
    static unsigned int mLastFrame;   
    //Time needed to run the loop 
    static unsigned int mFrameTime;    
};
