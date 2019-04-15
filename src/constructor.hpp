#ifndef CONSTUCTOR_H
#define CONSTUCTOR_H

#include "module.hpp"
#include "config.hpp"

#include <string>
#include <future>
#include <vector>
#include <functional>
#include <unordered_map>


namespace module
{

using constructor_t     = std::function<Module(const Config&)>;
using constructor_map_t = std::unordered_map<std::string, constructor_t>;


class constructor
{
private:
	
	static constructor_map_t map;

public:
    static constructor_t*
    get(std::string str);
    
	static std::vector<Segment>
	parse(std::vector<std::string>& strings, Config& config);
	
    static std::vector<std::future<Module>>
	spawn(std::vector<std::string>& segments, Config& config);

	static std::vector<Segment>
	join(std::vector<std::future<Module>>& futures, int duration);
    
    static void
    merge(constructor_map_t extension);
};

}



#endif