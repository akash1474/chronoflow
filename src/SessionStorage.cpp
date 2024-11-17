#include "pch.h"
#include "SessionStorage.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

void SessionStorage::Save(const std::vector<Session>& sessions) {
    nlohmann::json jsonArray;

    for (const auto& session : sessions) {
        jsonArray.push_back({
            {"startTime", TimePointToMilliseconds(session.startTime)},
            {"duration", session.duration},
            {"title", session.title}
        });
    }

    std::ofstream outFile(mFilePath);
    if (outFile.is_open()) {
        outFile << jsonArray.dump(4); // Pretty-print with 4 spaces
        outFile.close();
        std::cout << "Sessions saved to " << mFilePath << std::endl;
    } else {
        std::cerr << "Failed to open file for writing: " << mFilePath << std::endl;
    }
}

std::vector<Session> SessionStorage::Load() {
    std::vector<Session> sessions;
    nlohmann::json jsonArray;

    std::ifstream inFile(mFilePath);
    if (inFile.is_open()) {
        inFile >> jsonArray;
        inFile.close();

        for (const auto& jsonSession : jsonArray) {
            Session session;
            session.startTime = MillisecondsToTimePoint(jsonSession.at("startTime").get<long long>());
            session.duration = jsonSession.at("duration").get<std::time_t>();
            session.title = jsonSession.at("title").get<std::string>();
            session.timeRange=Stopwatch::FormatTimeRange(session.startTime, session.duration);

            // `timeRange` is not stored and will remain empty
            sessions.push_back(session);
        }
    } else {
        std::cerr << "Failed to open file for reading: " << mFilePath << std::endl;
    }

    return sessions;
}

long long SessionStorage::TimePointToMilliseconds(const Stopwatch::SystemTime& timePoint) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch()).count();
}

Stopwatch::SystemTime SessionStorage::MillisecondsToTimePoint(long long milliseconds) {
    return Stopwatch::SystemTime(std::chrono::milliseconds(milliseconds));
}
