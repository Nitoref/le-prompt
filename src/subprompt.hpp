#ifndef SUBPROMPT_H
#define SUBPROMPT_H

#include <unordered_set>
#include <optional>
#include <functional>
#include <vector>
#include <string>
#include "utils.hpp"
#include "modules.hpp"
#include "printer.hpp"

class SubPrompt
{
public:
    
    // Constructor
    template<typename F>
    SubPrompt (std::string a, std::string b, int c, int d, F f):
    separator(a),
    separator2(b),
    separator_length(utils::strlen(a)),
    separator2_length(utils::strlen(b)),
    padding_left(c),
    padding_right(d),
    append(f)
    {}

    // Content
    std::vector<Segment> segments;

    // Symbols
    std::string separator;
    std::string separator2;
    int separator_length;
    int separator2_length;
    int padding_left;
    int padding_right;

    // Information
    size_t length = 0;
    size_t actual_length = 0;

    std::vector<std::optional<int>> id_lookup;

    // Output status
    int prev_color  = -2;

    // Output function
    std::function<
        void(std::string&, std::string)
    >append;

    void
    preformat();
    
    std::string
    format_without(std::unordered_set<segment::id>& ignored);

    inline std::string
    format_segment(Segment s);
    
    inline std::string
    make_separator(Segment s);
    
    inline std::string
    final_separator();
};



#endif