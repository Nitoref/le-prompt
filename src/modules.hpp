#ifndef MODULES_H
#define MODULES_H

#include "module.hpp"
#include "config.hpp"

#include <string>
#include <future>
#include <vector>
#include <functional>
#include <unordered_map>
#include <nlohmann/json.hpp>


Module SegmentUser  (Config c);
Module SegmentShell (Config c);
Module SegmentPwd   (Config c);
Module SegmentHost  (Config c);
Module SegmentExit  (Config c);
Module SegmentJobs  (Config c);
Module SegmentTime  (Config c);
Module SegmentGit   (Config c);
Module SegmentPerms (Config c);
Module SegmentSsh   (Config c);
Module SegmentAws   (Config c);
Module SegmentVirtualEnv (Config c);

namespace module {
enum class id: unsigned int {
	user,
	shell,
	host,
	exit,
	jobs,
	time,
	perms,
	cwd,
	path,
	home,
	git_branch,
	git_ahead,
	git_behind,
	git_staged,
	git_not_staged,
	git_untracked ,
	git_conflicted,
	git_stash,
	ssh,
	aws,
	virtual_env,
	Count
};
}

namespace module {

using constructor_t     = std::function<Module(Config)>;
using constructor_map_t = std::unordered_map<std::string, constructor_t>;


class constructor
{
public:
	static constructor_map_t map;

    static constructor_t* get(std::string str)
    {
    	auto s = map.find(str);
	    if (s != map.end())
	    {
	        return &s->second;
	    }
	    return nullptr;
    }

    static std::vector<std::future<Module>>
	spawn(std::vector<std::string>& segments, Config& config)
	{
	    std::vector<std::future<Module>> futures;
	    futures.reserve(segments.size());
	    for (auto str: segments)
	    {
	        if (auto fun = get(str))
	        {
	            futures.push_back( std::async( 
	                std::launch::async, [=](){
	                    return (*fun)(config);
	                }
	            ));
	        }
	    } 
	    return futures;
	}

	static std::vector<Segment>
	join(std::vector<std::future<Module>>& futures, duration d)
	{
	    std::vector<int> priority_lookup;
	    std::vector<Segment> segments;
	    segments.reserve(futures.size());
	    
	    for (auto& future: futures)
	    {
	        auto status = future.wait_for(d);
	        if (status != std::future_status::ready)
	        {
	        	continue;
	        }
	        if (auto module = future.get())
	        {
	            for (auto&& segment: module)
	            {
	                segment && segments.emplace_back(segment);
	            }
	        }
	    }
	    return segments;
	}
	static std::vector<Segment>
	parse(std::vector<std::string>& segments_str, Config& config)
	{
	    std::vector<Segment> segments;
	    segments.reserve(segments_str.size());
	    for (auto str: segments_str)
	    {
	        if (auto fun = get(str))
	        {
	        	for (auto s: (*fun)(config))
	        	{
	            	segments.push_back(s);
	        	}
	        }
	    }
	    return segments;
	}
};
}


void from_json(const nlohmann::json& j, module::constructor_map_t& m);

#endif
