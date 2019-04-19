#define HOSTNAME_MAX 256

#include <string>
#include <cstdlib>
#include <unistd.h>
#include "../modules.hpp"


Module
SegmentContext(const config& c)
{
	Segment segment;

    char* hostname = (char*)malloc(HOSTNAME_MAX);
    gethostname(hostname, HOSTNAME_MAX);

    segment.content += std::string(hostname);
    segment.content.erase(segment.content.find('.'));
    segment.style = c.context.theme;
    segment.id = module::id::context;
	
	return Module {segment};
}

// Module
// SegmentHost(const config& c)
// {
//     char* host_c_str = (char*)malloc(HOSTNAME_MAX);
//     gethostname(host_c_str, HOSTNAME_MAX);

//     std::string host = utils::string(host_c_str);
//     std::string user = utils::string(getenv("USER"));
    
//     if (user == c.args.default_user) {
//         return Module {};
//     }

//     if (host == c.args.default_host)
//     {
//         return Module {};
//     }

//     if (host.empty() && user.empty())
//     {
//         return Module {};
//     }
    

//     bool root = (getuid() != 0);


//     bool escaped = false;
//     for (char ch: c.args.host_format)
//     {
//         switch(ch)
//         {
//             if (escaped)
//                 segment.content += ch;
//             escaped = false;

//             case 'u':
//                 segment.content += user;
//                 segment.id = module::id::host;
//                 segment.style = root ? c.theme.root
//                                      : c.theme.username
//             break;
//             case 'h':
//                 segment.content += host;
//             break;
//             case '>':
//                 module.push_back(segment);
//                 segment = Segment{};
//             break;
//             case 'H':
//                 std::string s = host.substr(host.find('.'));
//                 segment.content += s ? s : host;
//                 break;
//             case '\\':
//                 escaped = true;
//             break;
//             default:
//                 segment.content += ch;
//         }
//     }
// }
