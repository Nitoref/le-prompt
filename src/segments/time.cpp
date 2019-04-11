#include "modules.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>


Module
SegmentTime(Config c)
{
	Segment segment;
	auto time  = std::chrono::system_clock::now();
	auto ctime = std::chrono::system_clock::to_time_t(time);
    std::stringstream s;
    s << std::put_time(std::localtime(&ctime), c.args.time_format.data());
    segment.content = s.str();
	segment.style = c.theme.time;
	segment.id = module::id::time;
	return Module {segment};
}
