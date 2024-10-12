#include <iostream>
#include "linked-todo.h"

int main() {
    Linked<int> linkobj;
    for (int i = 1; i <= 100; ++i) {
        linkobj.push_front(i);
    }
    // 使用迭代器逆序输出该链表所有的元素
    for (Linked<int>::Iterator it = linkobj.begin(); it != linkobj.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
    return 0;
}