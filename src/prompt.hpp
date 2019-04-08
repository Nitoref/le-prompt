#ifndef PROMPT_H
#define PROMPT_H

#include <unordered_map> 
#include <vector>
#include <string>

#include "colorutils.hpp"
#include "segments.hpp"

using segment_constructor_t = std::function<MultiSegment(PromptConfig)>;


class Prompt
{
public:
    Prompt(int argc, char const *argv[]);
    void make_segments();
    
    std::string format_left_segments();
    std::string format_right_segments();

    size_t left_length();
    size_t right_length();

    PromptConfig options;
    Printer   printer;
    int prev_color_  = -1;


    segment_constructor_t* get_segment_by_name(std::string str);
    std::unordered_map<std::string, segment_constructor_t>
    segments_map_ {
        {"user",  SegmentUser},
        {"root",  SegmentRoot},
        {"pwd",   SegmentPwd},
        {"exit",  SegmentExit},
        {"host",  SegmentHost},
        {"jobs",  SegmentJobs},
        {"git",   SegmentGit},
        {"time",  SegmentTime},
        {"perms", SegmentPerms},
        {"ssh",   SegmentSsh},
        {"aws",   SegmentAws},
        {"virtualenv", SegmentVirtualEnv}
    };

private:

    std::vector<Segment> left_segments_;
    std::vector<Segment> right_segments_;
    
    std::string format_segment(Segment s);
    
    std::string make_separator(Segment s,
        std::string regular, std::string thin);
    
    std::string end_prompt(std::string separator);
    
    std::string format_left_segment(Segment s);
    
    std::string format_right_segment(Segment s);
    
    size_t length(std::vector<Segment> segments);
    
    std::string format_segments(
        std::vector<Segment> segments,
        std::function<void(std::string&, std::string)> add, 
        std::string regular, std::string thin
    );
};
#endif
