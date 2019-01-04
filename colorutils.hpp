#ifndef COLORUTILS_H
#define COLORUTILS_H


#define DEFAULT '9'
#define _STD_BG '4'
#define _STD_FG '3'
#define _256_BG "48;5;"
#define _256_FG "38;5;"
#define    _ESC "\\[\\e["
#define    _CSE "m\\]"



inline void setBg(int value){
    printf("%s%s%d%s",_ESC, _256_BG, value, _CSE);
}

inline void setFg(int value){
    printf("%s%s%d%s",_ESC, _256_FG, value, _CSE);
}

inline void resetBg(){
    printf("%s%c%d%s",_ESC, _STD_BG, DEFAULT, _CSE);
}

inline void resetFg(){
    printf("%s%c%d%s",_ESC, _STD_FG, DEFAULT, _CSE);
}

inline void resetStyle(){
    printf("%s%c%s",_ESC, '0', _CSE);
}


#endif
