#include "pch.h"
#include "SessionStorage.h"
#include "imgui.h"
#include "CoreSystem.h"
#include "Application.h"
#include "implot.h"
#include <chrono>

long long TimePointToMilliseconds(const Stopwatch::SystemTime& timePoint) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch()).count();
}

void GenerateDummySessions(const std::string& filePath) {
    std::vector<Session> dummySessions;
    auto now = std::chrono::system_clock::now();

    // Generate 20 dummy sessions
    for (int i = 1; i <= 20; ++i) {
        Session session;
        session.startTime = now + std::chrono::milliseconds(60000 * i); // Offset start times
        session.duration = 60000 * (100 + i);                           // Incremental durations
        session.title = "Session " + std::to_string(i);

        dummySessions.push_back(session);
    }

    // Convert sessions to JSON and save
    nlohmann::json jsonArray;
    for (const auto& session : dummySessions) {
        jsonArray.push_back({
            {"startTime", TimePointToMilliseconds(session.startTime)},
            {"duration", session.duration},
            {"title", session.title}
        });
    }

    // Write JSON to file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << jsonArray.dump(4); // Pretty-print with 4 spaces
        outFile.close();
        std::cout << "Dummy sessions saved to " << filePath << std::endl;
    } else {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
    }
}


CoreSystem::CoreSystem():mStorage("./.cache/cache.json"){
	// GenerateDummySessions("./.cache/cache.json");
	mSessions=mStorage.Load();
}

CoreSystem::~CoreSystem(){}

void CoreSystem::Render(){
	const ImVec2 windowSize=Application::Get().GetSize();
	const float headerContainer=40.0f;
	const float timerContainer=100.0f;
	const float listContainer=windowSize.y-headerContainer-timerContainer;


	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize,0.0f);


		ImGui::SetNextWindowPos({0,0});
		ImGui::SetNextWindowSize({windowSize.x,headerContainer});
		ImGui::Begin("##header",0,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoDecoration|ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::Text("ChronoFlow");
		ImGui::End();




		ImGui::SetNextWindowPos({0,headerContainer});
		ImGui::SetNextWindowSize({windowSize.x,timerContainer});
		ImGui::PushStyleColor(ImGuiCol_WindowBg,IM_COL32(20, 20, 20, 255));
		ImGui::Begin("##timer",0,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoDecoration|ImGuiWindowFlags_NoBringToFrontOnFocus);
		if(this->mStopWatch.Render() && mStopWatch.GetTime()>0)
		{
		    int minutes = (mStopWatch.GetTime() % (1000 * 60 * 60)) / (1000 * 60);
		    if(minutes > 10){
				mSessions.emplace_back(mStopWatch.GetStartTime(),mStopWatch.GetTime(),"Session 0X");
				Session& session=mSessions.back();
				session.timeRange=std::move(Stopwatch::FormatTimeRange(session.startTime, session.duration));
				mStopWatch.Reset();
		    }
		}
		ImGui::End();
		ImGui::PopStyleColor();





		ImGui::SetNextWindowPos({0,headerContainer+timerContainer});
		ImGui::SetNextWindowSize({windowSize.x,listContainer});
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,{0.0f,0.0f});
		ImGui::Begin("##sessions",0,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoBringToFrontOnFocus|ImGuiWindowFlags_NoTitleBar);
			for(const auto& session:mSessions)
				RenderSession(session);
		ImGui::End();
		ImGui::PopStyleVar();


	ImGui::PopStyleVar();

	ImPlot::ShowDemoWindow();

}

std::string FormatDuration(std::time_t duration_ms) {
    // Convert milliseconds to hours and minutes
    int hours = duration_ms / (1000 * 60 * 60);
    int minutes = (duration_ms % (1000 * 60 * 60)) / (1000 * 60);

    std::ostringstream oss;

    // Format the string based on the presence of hours and minutes
    if (hours > 0) {
        oss << hours << "Hr ";
        if (minutes > 0) {
            oss << minutes << "Mins";
        }
    } else if (minutes > 0) {
        oss << minutes << "Mins";
    } else {
        oss << "0Mins"; // Handle the case of 0 duration
    }

    return oss.str();
}


void CoreSystem::RenderSession(const Session& session)const
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems) return;

	time_t uid=session.startTime.time_since_epoch().count();
	ImGui::PushID(uid);
	const std::string eid="##"+std::to_string(uid);
	const char* title="Session 01";

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(eid.c_str());
	const ImVec2 textSize = ImGui::CalcTextSize(title);
	const ImVec2 itemSize(window->Size.x, 56);
	const ImVec2 pos{window->DC.CursorPos};
		ImVec2 end=window->ScrollMax.y > 0.0f ? ImVec2{window->ScrollbarSizes.x+1.0f,1.0f} : ImVec2{1.0f,1.0f};

	const float scrollBarXWidth= window->ScrollMax.y >0.0f ? window->ScrollbarSizes.x : 0.0f;

	const ImRect bb(pos, ImVec2(pos.x + itemSize.x - scrollBarXWidth, pos.y + itemSize.y));
	const ImVec2 titlePos(pos.x + 10.0f, pos.y + 5.0f);


	ImGui::ItemSize(bb, 0.0f);
	if (!ImGui::ItemAdd(bb, id)){
		ImGui::PopID();
		return ;
	}
	bool hovered;
	bool isClicked = ImGui::ButtonBehavior(bb, id, &hovered, NULL);
	bool isHovered = false;
	bool pressed = false;


	ImRect buttonSize(ImVec2(pos.x+itemSize.x-100- 19.5 + g.FontSize / 2, pos.y + 10), ImVec2(pos.x+itemSize.x-100 + 29.5 - (g.FontSize / 2), pos.y + 45));
	// ImGui::ButtonBehavior(buttonSize, NULL, &isHovered, &pressed);

	// Container
	window->DrawList->AddRectFilled(pos, bb.Max, hovered ? ImColor(40, 40, 40) : ImColor(50, 50, 50, 0));

	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
	ImGui::RenderText(titlePos, session.title.c_str());
	ImGui::PushStyleColor(ImGuiCol_Text, ImColor(113, 113, 113).Value);
	ImGui::RenderText(ImVec2(titlePos.x, titlePos.y + textSize.y + style.FramePadding.y), session.timeRange.c_str());
	ImGui::PopStyleColor();


	// // Active Song indicator
	// if (this->mIsSelected) {
	// 	window->DrawList->AddRectFilled(ImVec2(pos.x, pos.y + 5), ImVec2((pos.x + 5) * t, pos.y - 5 + itemSize.y), ImColor(49, 85, 164), 2.0f,ImDrawFlags_RoundCornersRight);
	// }



	// Overlay for player button display on hover of song
	window->DrawList->AddRectFilled(ImVec2(pos.x+itemSize.x-130, pos.y), bb.Max,hovered ? ImColor(40, 40, 40) : ImColor(30, 30, 30));
	if (hovered) {
		// Play button
		window->DrawList->AddRectFilled(buttonSize.Min, buttonSize.Max, isHovered ? ImColor(255, 250, 250, 50) : ImColor(0, 0, 0, 0), 4.0f);
		if (isHovered) ImGui::PushStyleColor(ImGuiCol_Text, ImColor(111, 136, 191).Value);
		// ImGui::RenderText(ImVec2(pos.x+itemSize.x-100, pos.y + 20), this->mIsSelected ? ICON_FA_PAUSE : ICON_FA_PLAY);
		if (isHovered) ImGui::PopStyleColor();
	}

	ImGui::RenderText(ImVec2(pos.x+itemSize.x-120, pos.y + 15), FormatDuration(session.duration).c_str());
	ImGui::PopFont();

	ImGui::PopID();

	return;
}