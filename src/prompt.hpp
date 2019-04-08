#ifndef PS1_H
#define PS1_H

#include <unordered_map> 
#include <vector>
#include <string>

#include "colorutils.hpp"
#include "segments.hpp"

class Prompt
{
public:
    Prompt(PromptConfig options);
    void make_segments();
    
    std::string format_left_segments();
    std::string format_right_segments();

    size_t left_length();
    size_t right_length();

    PromptConfig options_;
    ColorPrinter printer_;
    int prev_color_  = -1;

private:

    std::vector<Segment> left_segments_;
    std::vector<Segment> right_segments_;

    std::string format_segment(Segment s);
    std::string make_separator(Segment s, std::string regular, std::string thin);
    std::string end_prompt(std::string separator);
    
    std::string format_left_segment(Segment s);
    std::string format_right_segment(Segment s);
    
    std::string format_segments(
        std::vector<Segment> segments,
        std::function<void(std::string&, std::string)> add, 
        std::string regular, std::string thin
    );
};
#endif
