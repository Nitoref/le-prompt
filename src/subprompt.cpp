// #include "arguments.hpp"
// #include "symbols.hpp"
// #include "prompt.hpp"
// #include "theme.hpp"
// #include "shell.hpp"
// #include "utils.hpp"

// #include <string>
// #include <iostream>
// #include <algorithm>
// #include <functional>
// #include <unordered_map>


// std::string
// SubPrompt::format_with_ignored(std::vector<module::id>& ignored)
// {
//     std::string output;
//     for (auto& segment : segments)
//     {
//         auto found = ignored.find(segment.id);
//         if (found != ignored.end())
//             continue;
        
//         append(output, make_separator(segment));
//         append(output, format_segment(segment));
//     }
//     if (!output.empty())
//     {
//         append(output, final_separator());
//         output += printer.reset();
//     }
//     return output;
// }


// std::string
// SubPrompt::format_segment(Segment s) 
// {
//     std::string output;
//     output += printer.bg(s.style.bg);
//     output += printer.fg(s.style.fg);
//     output += std::string(padding_left, ' ');
//     output += s.content;
//     output += std::string(padding_right, ' ');
//     return output;
// }

// std::string
// SubPrompt::make_separator(Segment s)
// {
//     std::string output;
//     if (s.style.bg == prev_color)
//     {
//         output += printer.fg(10); // options.theme.separator.fg !!! TODO
//         output += separator2;
//     }
//     else
//     if (prev_color == -1)
//     {
//         output += printer.fg(s.style.bg);
//         output += printer.bg(prev_color);
//         output += printer.font("reversed");
//         output += separator;
//         output += printer.reset();
//     }
//     else
//     if (prev_color != -2)
//     {
//         output += printer.fg(prev_color);
//         output += printer.bg(s.style.bg);
//         output += separator;
//     }
//     prev_color = s.style.bg;
//     return output;
// }

// std::string
// SubPrompt::final_separator()
// {
//     std::string output;
//     output += printer.reset();
//     output += printer.fg(prev_color);
//     output += prev_color == -1 ? "" : separator;
//     prev_color = -2;
//     return output;
// }


// void
// SubPrompt::preformat()
// {
//     size_t subtotal = 0;
//     size_t div  = utils::strlen(separator);
//     size_t div2 = utils::strlen(separator2);

//     this->lengths.reserve(segments.size());
//     this->id_lookup.resize((int)module::id::__count);

//     size_t index = 0;
//     for (auto& segment: this->segments)
//     {
//         size_t id = (int)segment.id;
//         this->id_lookup.at(id).push_back(index++);

//         if (segment.style.bg == prev_color) {
//             subtotal += div2;
//             length += subtotal;
//             this->lengths.push_back(subtotal);
//         }
//         else if (prev_color != -2) {
//             subtotal += div;
//             length += subtotal;
//             this->lengths.push_back(subtotal);
//         }
//         subtotal = 0;
//         subtotal += utils::strlen(segment.content);
//         subtotal += padding_left;
//         subtotal += padding_right;
        
//         prev_color = segment.style.bg;
//     }

//     subtotal += prev_color == -1 ? 0 : div;
//     length += subtotal;
//     this->lengths.push_back(subtotal);

//     prev_color = -2;
//     length += 1;
//     length  += utils::strlen(prefix);
// }
