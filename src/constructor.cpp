#include "constructor.hpp"
#include <chrono>


namespace module
{

constructor_t* 
constructor::get(std::string str)
{
	auto s = map.find(str);
    if (s != map.end())
    {
        return &s->second;
    }
    return nullptr;
}

void
constructor::merge(constructor_map_t extension)
{
	map.insert(extension.begin(), extension.end());
}


std::vector<std::future<Module>>
constructor::spawn(std::vector<std::string>& segments, Config& config)
{
    std::vector<std::future<Module>> futures;
    futures.reserve(segments.size());
    for (auto str: segments)
    {
        if (auto fun = get(str))
        {
            futures.push_back( std::async( 
                std::launch::async, [=, &config](){
                    return (*fun)(config);
                }
            ));
        }
    }
    return futures;
}

std::vector<Segment>
constructor::join(std::vector<std::future<Module>>& futures, int duration)
{
    using milliseconds = std::chrono::milliseconds;
    
    std::vector<int> priority_lookup;
    std::vector<Segment> segments;
    segments.reserve(futures.size());
    
    for (auto& future: futures)
    {
        future.wait_for(milliseconds(duration));
        if (auto module = future.get())
        {
            for (auto&& segment: module)
            {
                if (segment)
                    segments.emplace_back(segment);
            }
        }
    }
    return segments;
}


}