#pragma once
#include <chrono>
#include <ctime>
#include "imgui.h"

enum class TimerState {
    Stopped,
    Running,
    Paused
};

class Stopwatch {
public:
    Stopwatch();
    typedef std::chrono::system_clock::time_point SystemTime;
    typedef std::chrono::steady_clock::time_point SteadyTime;

    void Play();
    void Pause();
    void Reset();
    SystemTime GetStartTime()const{return mStartTime;}
    int GetTime() const;
    TimerState GetState() const;
    bool Render();
    bool IsRunning()const{return mState==TimerState::Running;}
    static std::string FormatTime(SystemTime time);
    static std::string FormatTimeRange(SystemTime startTime, std::time_t duration_ms);

private:
    TimerState mState;
    SteadyTime start_time;
    int elapsed_time; // in milliseconds
    SystemTime mStartTime;
};
