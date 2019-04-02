#ifndef PS1_H
#define PS1_H

#include <unordered_map> 
#include <vector>

#include "colorutils.hpp"
#include "modules.hpp"

class Prompt
{
public:
    Prompt(PromptOpt options);
    void parse_left_segments();
    void parse_right_segments();
    void print_left();
    void print_right();

private:
    std::unordered_map<std::string, ThreadedSegment*> segments_;
    std::vector<ThreadedSegment*> threads_;
    std::vector<ThreadedSegment*> right_threads_;

    std::string left_;
    std::string right_;
    
    PromptOpt options_;
    ColorPrinter printer_;
    size_t length_   =  0;
    size_t length_r_ =  0;
    int prev_color_  = -1;
    
    void parse_left_segments(std::vector<std::string> segments);
    void parse_right_segments(std::vector<std::string> segments);
    void print_segment(Segment s);
    void print_r_segment(Segment s);
    void reset();

    ThreadedSegment* get_segment_by_name(std::string str);
};

#endif
