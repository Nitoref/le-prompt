#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <map>
#include <future>




struct X {
    int* a;
    int  b;
    int  c;
};


typedef int (*functionPointer)(char);

// int main(int argc, char const *argv[])
// {
//     int *j;
//     // if (int *j = NULL)
//     if (int *j = new int(0))
//         printf("HELLO\n");
//     std::exit(0);
// }
