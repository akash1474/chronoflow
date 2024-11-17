#pragma once
#include "Stopwatch.h"


struct Session{
    // Time when session began
    Stopwatch::SystemTime startTime;
    std::time_t duration;
    std::string title;
    std::string timeRange;
    Session(){}
    Session(Stopwatch::SystemTime aStart,std::time_t aDuration,std::string aTitle,std::string aClockTime=""):startTime(aStart),duration(aDuration),title(aTitle),timeRange(aClockTime){}
};
