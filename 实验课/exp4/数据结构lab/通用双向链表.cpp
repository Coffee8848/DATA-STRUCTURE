#include <iostream>
using namespace std;

template <typename T>
class list {
private:
    struct Node {
        T data;
        Node *prev;
        Node *next;

        Node(const T& value = T(), Node *p = nullptr, Node *n = nullptr) : data(value), prev(p), next(n) {} // const T& value = T() T是调用默认构造函数
    };

    Node *head; //这是list里 一个指向头部的指针用以标记头部
    Node *tail; //指向链表尾部的指针用以标记尾部
    unsigned count; //计数

public:
    //构造函数
    list() : head(new Node()), tail(new Node()), count(0) {
        head->next = tail;
        tail->prev = head; //先创建两个节点然后交叉连起来
    }

    //析构函数
    ~list() {
        clear();
        delete head;
        delete tail;
    }

    //拷贝构造函数
    list(const list<T>& x) : list() {
        for (const T& item : x) {
            push_back(item);
        }
    }

    //赋值运算符
    list<T>& operator=(const list<T>& x) {
        if (this != &x) {
            clear();
            for (const T& item : x) {
                push_back(item);
            }
        }
        return *this;
    }

    //内部迭代器类
    class iterator {
    private:
        Node* current;

    public:
        iterator(Node* node = nullptr) : current(node) {} //构造函数

        iterator& operator++() { //++迭代器  iterator&是因为返回值是引用(iterator&)
            current = current->next; // current->next ->返回的是current里的next成员 而next成员是一个指向下一个的指针 就实现了迭代器下一个的功能
            return *this;
        }

        iterator operator++(int) { //后置++ 指先返回本迭代器在++ 这个int只是和前置作区分  没有&是因为返回值是一个iterator
            iterator temp = *this; //这是默认拷贝构造/赋值初始化
            current = current->next;
            return temp;
        }

        iterator& operator--() {
            current = current->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            current = current->prev;
            return temp;
        }

        T& operator*() { // 解引用
            return current->data; //this是这个iterator   current是这个iterator的node类成员
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

        Node* getNode() const {
            return current;
        }
    };

    void push_front(const T& x) {
        insert(begin(), x);
    }

    void push_back(const T& x) {
        insert(end(), x);
    }

    iterator insert(iterator position, const T& x) {
        Node* posNode = position.getNode();
        Node* newNode = new Node(x, posNode->prev, posNode);
        posNode->prev->next = newNode;
        posNode->prev = newNode;
        ++count;
        return iterator(newNode);
    }

    void pop_front() {
        if (!empty()) {
            erase(begin());
        }
    }

    void pop_back() {
        if (!empty()) {
            erase(--end());
        }
    }

    iterator erase(iterator position) {
        Node* node = position.getNode();
        Node* nextNode = node->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        --count;
        return iterator(nextNode);
    }

    iterator erase(iterator first, iterator last) {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    void splice(iterator position, list<T>& x) {
        if (!x.empty()) {
            Node* posNode = position.getNode();
            Node* xFirst = x.head->next;
            Node* xLast = x.tail->prev;

            posNode->prev->next = xFirst;
            xFirst->prev = posNode->prev;

            xLast->next = posNode;
            posNode->prev = xLast;

            count += x.count;

            x.head->next = x.tail;
            x.tail->prev = x.head;
            x.count = 0;
        }
    }

    unsigned size() const { return count; }

    bool empty() const { return count == 0; }

    iterator begin() { return iterator(head->next); }

    iterator end() { return iterator(tail); }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
};

// 测试代码
int main() {
    list<int> myList;

    // 测试 push_back 和 push_front
    myList.push_back(10);
    myList.push_back(20);
    myList.push_front(5);

    // 打印链表
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 pop_back 和 pop_front
    myList.pop_back();
    myList.pop_front();

    // 打印链表
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}