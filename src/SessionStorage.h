#pragma once

#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "Session.h"

class SessionStorage {
public:
    SessionStorage(std::string aFilePath):mFilePath(aFilePath){};
    // Save sessions to a JSON file
    void Save(const std::vector<Session>& sessions);

    // Load sessions from a JSON file
    std::vector<Session> Load();

private:
    std::string mFilePath;
    // Helper function to convert time_point to milliseconds since epoch
    static long long TimePointToMilliseconds(const Stopwatch::SystemTime& timePoint);

    // Helper function to convert milliseconds since epoch to time_point
    static Stopwatch::SystemTime MillisecondsToTimePoint(long long milliseconds);
};
