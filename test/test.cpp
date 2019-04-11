#include <functional>
#include <iostream>
#include <list>

int main() 
{
    // std::list<std::reference_wrapper<int>> lst;
    // lst.front().get() = 10;     // we update the list
    std::list<int> lst;

    lst.push_front(1);
    auto l1 = lst.front();
    lst.push_front(2);
    auto l2 = lst.front();
    lst.push_front(3);
    auto l3 = lst.front();
    lst.push_front(4);
    auto l4 = lst.front();
    lst.erase(l2);
    std::cout << l1 << "\n";
    std::cout << l3 << "\n";
    std::cout << l2 << "\n";
    std::cout << l4 << "\n";
}