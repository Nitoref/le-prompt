#include "../modules.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>


Module
SegmentTime(const Config& c)
{
	auto time  = std::chrono::system_clock::now();
	auto ctime = std::chrono::system_clock::to_time_t(time);
    std::stringstream s;
    s << std::put_time(std::localtime(&ctime), c.args.time_format.data());

	return Module {
		{
			module::id::time,
			s.str(),
			c.theme.time
		}
	};
}
