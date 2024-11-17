#pragma once
#include "vector"
#include "SessionStorage.h"


class CoreSystem{
	Stopwatch mStopWatch;
	std::vector<Session> mSessions;
	SessionStorage mStorage;
public:
	CoreSystem();
	~CoreSystem();
	void Render();
	void RenderSession(const Session& session)const;
	std::vector<Session> GetSessions()const{return mSessions;}
};