#ifndef PS1_H
#define PS1_H

#include <unordered_map> 
#include <vector>

#include "colorutils.hpp"
#include "modules.hpp"

class Prompt
{
public:
    Prompt(PromptConfig options);
    void parse_segments();
    std::string print_left_segments();
    std::string print_right_segments();

    size_t left_length();
    size_t right_length();
    PromptConfig options_;

    int prev_color_  = -1;
private:
    std::unordered_map<std::string, std::function<ThreadedSegment*()>> segments_map_;

    std::vector<ThreadedSegment*> l_segments_;
    std::vector<ThreadedSegment*> r_segments_;

    ColorPrinter printer_;
    
    void        parse_segments(std::vector<std::string> list, std::vector<ThreadedSegment*>& threads);
    std::string merge_segments(std::vector<ThreadedSegment*>& threads, std::string(Prompt::*f)(Segment));
    std::string print_segment(Segment s);
    std::string print_left_segment(Segment s);
    std::string print_right_segment(Segment s);

    ThreadedSegment* get_segment_by_name(std::string str);
};

#endif
