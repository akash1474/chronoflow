#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "pch.h"
#include "imgui.h"
#include <stdio.h>
#include "Stopwatch.h"

Stopwatch::Stopwatch() : mState(TimerState::Stopped), elapsed_time(0) {}

void Stopwatch::Play() {
    if (mState == TimerState::Stopped || mState == TimerState::Paused) {
        start_time = std::chrono::steady_clock::now();
        mState = TimerState::Running;
    }
}

void Stopwatch::Pause() {
    if (mState == TimerState::Running) {
        elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - start_time)
                            .count();
        mState = TimerState::Paused;
    }
}

void Stopwatch::Reset() {
    mState = TimerState::Stopped;
    elapsed_time = 0;
}

int Stopwatch::GetTime() const {
    if (this->IsRunning()) {
        return elapsed_time + std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time) .count();
    }
    return elapsed_time;
}

TimerState Stopwatch::GetState() const {
    return mState;
}

bool Stopwatch::Render() {
    int total_milliseconds = this->GetTime();
    int hours = total_milliseconds / (1000 * 60 * 60);
    int minutes = (total_milliseconds % (1000 * 60 * 60)) / (1000 * 60);
    int seconds = (total_milliseconds % (1000 * 60)) / 1000;
    int milliseconds = total_milliseconds % 1000;
    char buff[14];
    sprintf_s(buff,"%02d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds);

    const ImVec2 winSize=ImGui::GetWindowSize();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

        const ImVec2 timerSize=ImGui::CalcTextSize(buff);
        const ImVec2 timerPos{(winSize.x-timerSize.x)*0.5f,(timerSize.y-winSize.y)*0.5f};
        ImGui::SetCursorPos(ImGui::GetWindowPos()+timerPos);
        ImGui::Text("%s", buff);

    ImGui::PopFont();



    ImGui::SetCursorPosX((winSize.x-140-ImGui::GetStyle().ItemSpacing.x)*0.5f);
    if (ImGui::Button(mState == TimerState::Running ? "Pause" : mState==TimerState::Stopped ? "Begin Session" : "Resume",{70.0f,28.0f})) {
        if (mState == TimerState::Running) {
            this->Pause(); 
        } else {
            if(mState==TimerState::Stopped) mStartTime = std::chrono::system_clock::now();
            this->Play();
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("End Session",{70.0f,28.0f})) {
        return true;
    }

    // const ImVec2 start{}

    // ImGui::GetCurrentWindow()->DrawList->AddRectFilled({}, const ImVec2 &p_max,IM_COL32(30,30,30,255));

    return false;
}

std::string Stopwatch::FormatTime(Stopwatch::SystemTime time) {
    std::time_t time_t_val = std::chrono::system_clock::to_time_t(time);
    std::tm local_tm = *std::localtime(&time_t_val);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%I:%M %p");
    return oss.str();
}

std::string Stopwatch::FormatTimeRange(Stopwatch::SystemTime startTime, std::time_t duration_ms) {
    auto system_now = std::chrono::system_clock::now();
    auto steady_now = std::chrono::steady_clock::now();
    auto system_start = startTime;

    auto system_end = system_start + std::chrono::milliseconds(duration_ms);

    std::string start_formatted = FormatTime(system_start);
    std::string end_formatted = FormatTime(system_end);

    return start_formatted + " to " + end_formatted;
}