#include "segments.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>


Segment
SegmentTime(PromptConfig p)
{
	Segment segment;
	auto time  = std::chrono::system_clock::now();
	auto ctime = std::chrono::system_clock::to_time_t(time);
    std::stringstream s;
    s << std::put_time(std::localtime(&ctime), p.args.time_format.data());
    segment.content = s.str();
	segment.style = p.theme.time;
	return segment;
}
