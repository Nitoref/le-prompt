#include <IOKit/IOTypes.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/OSMessageNotification.h>
#include <sys/cdefs.h>
#include <IOKit/ps/IOPowerSources.h>


#include <stdio.h>
#include "unistd.h"
#include "sys/types.h"
#include "sys/resource.h"
#include <sys/cdefs.h>
#include <sys/cdefs.h>

#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#include "sys/sysctl.h"
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iterator>
#include <iterator>
#include <functional>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <git2.h>

using namespace std;

// struct cpusample {
//     uint64_t totalSystemTime;
//     uint64_t totalUserTime;
//     uint64_t totalIdleTime;
// };

void cpusample()
{
    kern_return_t kr;
    mach_msg_type_number_t count;
    host_cpu_load_info_data_t r_load;

    // uint64_t totalSystemTime = 0, totalUserTime = 0, totalIdleTime = 0;
    count = HOST_CPU_LOAD_INFO_COUNT;
    kr = host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (int *)&r_load, &count);
    if (kr != KERN_SUCCESS) {
        printf("oops: %s\n", mach_error_string(kr));
        return;
    }

    std::cout << "totalSystemTime = " << r_load.cpu_ticks[CPU_STATE_SYSTEM];
    std::cout << "totalUserTime = "   << r_load.cpu_ticks[CPU_STATE_USER] + r_load.cpu_ticks[CPU_STATE_NICE];
    std::cout << "totalIdleTime = "   << r_load.cpu_ticks[CPU_STATE_IDLE];

}


struct A {};
struct B: public A{};
struct C: public A{};





struct Status
{
	string branch;
	string workdir;
	bool staged;
	bool notstaged;
	bool untracked;
};


int git_diff_callback(const git_diff* a, const git_diff_delta* delta, const char* c, void* payload){
	if (delta -> status == GIT_DELTA_UNTRACKED) {
		(*(Status*)payload).untracked = true;
	} else {
		(*(Status*)payload).notstaged = true;
	}
	if ((*(Status*)payload).notstaged && (*(Status*)payload).untracked)
		return -10;
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	Status status;

    git_repository     *repository = NULL;
    git_reference      *head       = NULL;
    git_commit         *commit     = NULL;
    git_index          *index      = NULL;
    git_tree           *tree       = NULL;
    git_diff           *diff       = NULL;
	git_diff_options   options    = GIT_DIFF_OPTIONS_INIT;

	options.flags = GIT_DIFF_SKIP_BINARY_CHECK | GIT_DIFF_DISABLE_PATHSPEC_MATCH |
              		GIT_DIFF_INCLUDE_UNTRACKED | GIT_DIFF_RECURSE_UNTRACKED_DIRS;

    git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION,     0);
    git_libgit2_opts(GIT_OPT_DISABLE_INDEX_CHECKSUM_VERIFICATION, 1);
    git_libgit2_opts(GIT_OPT_DISABLE_INDEX_FILEPATH_VALIDATION,   1);
    git_libgit2_init();

    if (git_repository_open_ext(&repository, ".", 0, NULL)) {
    	cout << "Unable to open repository.";
        return 1;
    }
    
    if (git_repository_is_empty(repository)) {
        cout << "Repository empty\n";
    	return 1;
    }
    
    if (git_repository_index(&index, repository)) {
    	cout << "Unable to get index.\n";
    	return 1;
    }

	if (git_repository_head(&head, repository))
	{
		cout << "Couldn't get head.\n";
		return 1;
	};
    status.branch = git_reference_shorthand(head);
	cout << "On branch " << status.branch << "\n";


	if (git_commit_lookup(&commit, repository, git_reference_target(head)))
	{
		cout << "Couldn't get commit.\n";
		return 1;
	};

	if (git_commit_tree(&tree, commit)) {
		cout << "Couldn't get tree.\n";
		return 1;
	};

	options.notify_cb = git_diff_callback;

	options.payload = (void*)&status.staged;
	if (auto e = git_diff_tree_to_index(&diff, repository, tree, index, &options); e && e != -10 ) {
		cout << "Tree/index diff error.\n";
		return 1;
	}

	options.payload = (void*)&status.notstaged;
	if (auto e = git_diff_index_to_workdir(&diff, repository, index, &options); e && e != -10 ) {
		cout << "Index/workdir diff error.\n";
		return 1;
	}

	git_diff_free(diff);
    git_repository_free(repository);
    git_libgit2_shutdown();

	// auto blob = IOPSCopyPowerSourcesInfo();
	// auto ps   = IOPSCopyPowerSourcesList(blob);
	// auto dict = IOPSGetPowerSourceDescription(blob, ps);
	// std::cout << *dict[kIOPSACPowerValue] << "\n";
	
	// cpusample();

	// auto path =  std::filesystem::current_path();
	// auto path = std::filesystem::path("");

    // std::string output;
    // if (folders.size() > 2)
    // {
    // 	output = 
    // }


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
