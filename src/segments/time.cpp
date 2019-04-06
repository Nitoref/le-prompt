#include "modules.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>


void
SegmentTime::make()
{
	auto time  = std::chrono::system_clock::now();
	auto ctime = std::chrono::system_clock::to_time_t(time);
    std::stringstream s;
    s << std::put_time(std::localtime(&ctime), opt.args.time_format.data());
    segment.content = s.str();
	segment.style = opt.theme.time;
}
