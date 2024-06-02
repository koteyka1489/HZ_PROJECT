#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float MarkRealDt();
	float MarkFixDt();
private:
	std::chrono::steady_clock::time_point last;
};