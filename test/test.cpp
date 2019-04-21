#include <stdio.h>
#include "unistd.h"
#include "sys/types.h"
#include "sys/resource.h"
#include <sys/cdefs.h>
#include <IOKit/IOTypes.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/OSMessageNotification.h>
#include <sys/cdefs.h>
#include <IOKit/ps/IOPowerSources.h>

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

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>


int main(int argc, char **argv, char **envp)
{

	auto blob = IOPSCopyPowerSourcesInfo();
	auto ps   = IOPSCopyPowerSourcesList(blob);
	auto dict = IOPSGetPowerSourceDescription(blob, ps);
	

	std::cout << *dict[kIOPSACPowerValue] << "\n";







    // vm_size_t page_size;
    // mach_port_t mach_port;
    // mach_msg_type_number_t count;
    // vm_statistics64_data_t vm_stats;

    // mach_port = mach_host_self();
    // count = sizeof(vm_stats) / sizeof(natural_t);
    // if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
    //     KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
    //                                     (host_info64_t)&vm_stats, &count))
    // {
    //     long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

    //     long long used_memory = ((int64_t)vm_stats.active_count +
    //                              (int64_t)vm_stats.inactive_count +
    //                              (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
    //     printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
    // }


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

	// int mib[4];
	// size_t len;

 //    /* Fill out the first three components of the mib */
	// struct kinfo_proc kp;
	// len = 4;
	// sysctlnametomib("kern.proc.pid", mib, &len);

	// mib[3] = getppid();
	// len = sizeof(kp);
	// if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1)
	// 	perror("sysctl");
	// else if (len > 0)
	// 	std::cout << kp.kp_eproc.e_jobc;
}
