#ifndef COLORUTILS_H
#define COLORUTILS_H


#define DEFAULT '9'
#define BG_STD_ '4'
#define FG_STD_ '3'
#define BG_256_ "48;5;"
#define FG_256_ "38;5;"
#define    ESC_ "\\[\\e["
#define    CSE_ "m\\]"



inline void setBg(int value){
    printf("%s%s%d%s",ESC_, BG_256_, value, CSE_);
}

inline void setFg(int value){
    printf("%s%s%d%s",ESC_, FG_256_, value, CSE_);
}

inline void resetBg(){
    printf("%s%c%d%s",ESC_, BG_STD_, DEFAULT, CSE_);
}

inline void resetFg(){
    printf("%s%c%d%s",ESC_, FG_STD_, DEFAULT, CSE_);
}

inline void resetStyle(){
    printf("%s%c%s",ESC_, '0', CSE_);
}


inline void setFontStyle(const char* str){
    static
    std::unordered_map<std::string, int> y =
    {
        {"bold",         1},
        {"faint",        2},
        {"italic",       3},
        {"underline",    4},
        {"blink_slow",   5},
        {"blink_fast",   6},
        {"crossed_out",  9},
        {"framed",      51},
        {"encircled",   52},
        {"overlined",   53}
    };
    try
    {
        int style = y.at(str);
        printf("%s%dm%s",ESC_, style, CSE_);
    }
    catch(...)
    {
        return;
    }
}


#endif
