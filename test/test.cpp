#include <stdio.h>
#include "unistd.h"
#include "sys/types.h"
#include "sys/resource.h"


#include "sys/sysctl.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>

static unsigned long long _previousTotalTicks = 0;
static unsigned long long _previousIdleTicks = 0;

float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
  unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
  unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;
  float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);
  _previousTotalTicks = totalTicks;
  _previousIdleTicks  = idleTicks;
  return ret;
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.
float GetCPULoad()
{
   host_cpu_load_info_data_t cpuinfo;
   mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
   if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
   {
      unsigned long long totalTicks = 0;
      for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
      return CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
   }
   else return -1.0f;
}



int main(int argc, char **argv, char **envp)
{

	std::cout << GetCPULoad() << "\n";
	std::cout << GetCPULoad() << "\n";
	std::cout << GetCPULoad() << "\n";
	std::cout << GetCPULoad() << "\n";
	std::cout << GetCPULoad() << "\n";
	std::cout << GetCPULoad() << "\n";
	// struct sysinfo memInfo;

	// sysinfo (&memInfo);
	// std::cout << "memInfo.totalram : "  << memInfo.totalram;
	// //Add other values in next statement to avoid int overflow on right hand side...
	// std::cout << "memInfo.totalswap : " << memInfo.totalswap;
	// std::cout << "memInfo.mem_unit : "  << memInfo.mem_unit;



	// int i;
	// size_t a = 512;
	// size_t b = 0;
	// string s;
	// char *c = (char*)malloc(512*sizeof(char));
	// int val[1] = {HW_MACHINE};
	// int info;
	// size_t size = sizeof(int);
	// std::cout << sysctl(val, 1, &info, &size, NULL, 0) << "\n";
	// std::cout << sysctlbyname("ncpu", (void*)&i, &a, NULL, 0) << "\n";

	// std::cout << a << "\n";
	// std::cout << b << "\n";
	// std::cout << c << "\n";

 
	// sysctlbyname("ncpu", )
	// sysctlbyname("physmem", )
	// sysctlbyname("usermem", )
	// sysctlbyname("diskstats", )
	// sysctlbyname("memsize", )
	// sysctlbyname("availcpu", )


	int mib[4];
	size_t len;

    /* Fill out the first three components of the mib */
	struct kinfo_proc kp;
	len = 4;
	sysctlnametomib("kern.proc.pid", mib, &len);

	mib[3] = getppid();
	len = sizeof(kp);
	if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1)
		perror("sysctl");
	else if (len > 0)
		std::cout << "";

	double load[3];
	getloadavg(load, 3);
	std::cout << load[0] << ", " << load[0] << ", "  << load[0] << "\n" ;

}
