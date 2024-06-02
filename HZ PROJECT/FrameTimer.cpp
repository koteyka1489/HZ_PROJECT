#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::MarkRealDt()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float FrameTimer::MarkFixDt()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	if (frameTime.count() > 0.016)
	{
		return 0.016f;
	}
	return frameTime.count();
}
