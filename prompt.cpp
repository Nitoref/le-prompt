#include "prompt.hpp"
#include "utils.hpp"

#include <iostream>
#include <string>
#include <sstream>


Prompt::Prompt(PromptOpt options):
    options(options),
    printer(options.shell)
{
    segments = {
        {"user", new SegmentUser(this->options)},
        {"root", new SegmentRoot(this->options)},
        {"pwd",  new SegmentPwd(this->options)},
        {"exit", new SegmentExit(this->options)},
        {"git",  new SegmentGit(this->options)},
        {"host", new SegmentHost(this->options)},
    };
    threads.reserve(segments.size());
}


ThreadedSegment*
Prompt::getSegmentByName(std::string str)
{
    auto& s = segments[str];
    return s ? : NULL;
}


void
Prompt::parseLeftSegments(std::vector<std::string> segments)
{
    for (auto& segment: segments)
    {
        if (ThreadedSegment *s = getSegmentByName(segment)){
            s->init();
            threads.push_back(s);
        }
    }
}

void
Prompt::parseRightSegments(std::vector<std::string> segments)
{
    for (auto& segment: segments)
    {
        if (ThreadedSegment *s = getSegmentByName(segment)){
            s->init();
            rightThreads.push_back(s);
        }
    }
}

void
Prompt::parseLeftSegments()
{
    parseLeftSegments(options.args.LeftSegments);
}
void
Prompt::parseRightSegments()
{
    parseRightSegments(options.args.RightSegments);
}


void
Prompt::printLeft()
{
    for (auto &thread : threads)
    {
        thread->join();
        if (!thread->segment.content)
        {
            continue;
        }
        printSegment(thread->segment);
    }
    reset();
}

void
Prompt::printRight()
{
    for (auto &thread : rightThreads)
    {
        thread->join();
        if (!thread->segment.content)
        {
            continue;
        }
        printRSegment(thread->segment);
    }
    printer.resetStyle();
}


void
Prompt::printSegment(Segment s)
{
    if (s.style.bg == prevColor)
    {
        length += strlen_utf8(options.symbols.SeparatorThin);
        printer.setFg(s.style.fg);
        printf("%s", options.symbols.SeparatorThin);
    }
    else
    if (prevColor != -1)
    {
        length += strlen_utf8(options.symbols.Separator);
        printer.setBg(s.style.bg);
        printer.setFg(prevColor);
        printf("%s", options.symbols.Separator);
    }
    printer.setBg(s.style.bg);
    printer.setFg(s.style.fg);
    printf(" %s ",s.content);
    length += strlen_utf8(s.content) + 2;
    prevColor = s.style.bg;
}

void
Prompt::printRSegment(Segment s)
{
    if (s.style.bg == prevColor)
    {
        length += strlen_utf8(options.symbols.RSeparatorThin);
        printer.setBg(s.style.fg);
        printf("%s", options.symbols.RSeparatorThin);
    }
    else
    {
        length += strlen_utf8(options.symbols.RSeparator);
        if (prevColor != -1)
            printer.setBg(prevColor);
        printer.setFg(s.style.bg);
        printf("%s", options.symbols.RSeparator);
    }
    printer.setBg(s.style.bg);
    printer.setFg(s.style.fg);
    printf(" %s ",s.content);
    length += strlen_utf8(s.content) + 2;
    prevColor = s.style.bg;
}


void
Prompt::reset(){
    printer.resetStyle();
    printer.setFg(prevColor);
    printf("%s  ", options.symbols.Separator);
    printer.resetStyle();
}



// g++ -Oz -o build/powerline -std=c++17 *.cpp ./*/*.cpp -lgit2 -Iinclude
// clang++ -std=c++2a -Wall -Werror -D_LIBCPP_DISABLE_AVAILABILITY test.cpp -I/Users/nitoref/Desktop/powerless/C++/include/