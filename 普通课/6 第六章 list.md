# STD:: 链表

### 复习双向链表

在双向链表（或一般的链表）中，`insert` 方法通常会在指定迭代器所指向的位置之前插入新元素。这是因为插入操作需要保持链表的顺序，并且在链表中插入元素时，最常见的操作是将新元素插入到现有元素之前。

> 注意 插入操作 insert约定是往前插入代码   使用的时候  例如`words.insert(itr, "good");` 而不更新 `itr`，那么 `itr` 仍然指向原来的位置，只是它之前多了一个新插入的元素。

> itr = words .insert (itr,good)  这样才会添加完元素把迭代器指向插入的新元素的位置
> 以下是示例

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class CircularDoublyLinkedList {
public:
    CircularDoublyLinkedList() : head(nullptr) {}

    // 在链表末尾添加节点（即在头节点之前插入节点）
    void append(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    // 在指定位置之前插入节点
    void insert(Node* pos, int val) {
        Node* newNode = new Node(val);
        Node* prevNode = pos->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = pos;
        pos->prev = newNode;
    }

    void printForward() {
        if (!head) return;
        Node* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    void printBackward() {
        if (!head) return;
        Node* current = head->prev;
        do {
            std::cout << current->data << " ";
            current = current->prev;
        } while (current != head->prev);
        std::cout << std::endl;
    }

    Node* getHead() {
        return head;
    }

private:
    Node* head;
};

int main() {
    CircularDoublyLinkedList cdll;
    cdll.append(1);
    cdll.append(2);
    cdll.append(3);

    std::cout << "Forward: ";
    cdll.printForward();

    std::cout << "Backward: ";
    cdll.printBackward();

    // 在头节点之前插入新节点（即在链表末尾添加节点）
    Node* head = cdll.getHead();
    cdll.insert(head, 4);

    std::cout << "After inserting 4 before head (at the end):" << std::endl;
    std::cout << "Forward: ";
    cdll.printForward();

    std::cout << "Backward: ";
    cdll.printBackward();

    return 0;
}
```

### list实现

STL 中的 `list` 类基于 **双向链表** 实现

## 1. 双向链表的结构

### 节点定义

链表的每个节点是一个结构体，包含三个部分：

- 数据字段（data）：存储链表节点的值。
- 前向指针（prev）：指向前一个节点。
- 后向指针（next）：指向下一个节点。

代码定义：

```cpp
struct list_node {
    list_node* next;  // 指向下一个节点
    list_node* prev;  // 指向前一个节点
    T data;           // 节点存储的数据
};
```

### 链表的基本组织

链表是由多个节点串联组成的，每个节点通过指针 `prev` 和 `next` 连接起来。链表的头节点是一个哨兵节点（Header Node）。

结构示意图：

```
[Header Node]
  prev <----> data <----> data <----> next
          (双向链表的其他节点)
```

#### 空链表：

哨兵节点的 `next` 和 `prev` 均指向自身。

```
[Header Node]
 prev -> Header Node <- next
```

#### 非空链表：

哨兵节点的 `next` 指向第一个节点，`prev` 指向最后一个节点。

```
[Header Node] <-----> [Node 1] <-----> [Node 2] <-----> [Node 3]
```

## 2. 头节点的作用

### 定义

头节点是一个特殊的哨兵节点，用来简化链表的操作。它不存储有效数据，仅作为链表的入口和标记。

### 特点

- 哨兵节点的 `data` 字段为空。
- 哨兵节点的 `prev` 指针指向链表的尾节点，`next` 指针指向链表的头节点。

### 好处

- **简化操作**：无需对空链表和边界情况（如首节点和尾节点）进行额外处理。
- **实现循环链表**：哨兵节点使链表形成环状，每个节点都有前驱和后继节点。

## 3. 插入与删除操作

### 插入操作

在双向链表中插入一个新节点的流程如下：

1. 分配内存并创建新节点。
2. 设置新节点的 `data` 字段。
3. 调整前后指针以链接新节点。

代码实现：

```cpp
iterator insert(iterator position, const T& x) {
    list_node* tmp = new list_node;    // 分配新节点
    tmp->data = x;                     // 设置数据
    tmp->next = position.node;         // 新节点的 next 指向当前节点
    tmp->prev = position.node->prev;   // 新节点的 prev 指向当前节点的前驱

    position.node->prev->next = tmp;   // 前驱节点的 next 指向新节点
    position.node->prev = tmp;         // 当前节点的 prev 指向新节点

    ++length;                          // 更新链表长度
    return iterator(tmp);              // 返回指向新节点的迭代器
}
```

时间复杂度：O(1)

### 删除操作

在双向链表中删除一个节点的流程如下：

1. 调整前后指针以绕过待删除节点。
2. 释放待删除节点的内存。

时间复杂度：O(1)

# 使用

```cpp
#include <list>
#include <string>
#include <iostream>

int main() {
    // 1. 声明 list 对象
    // list 是一个模板类，需要指定元素的类型。
    // 可以存储任意类型的元素，如基本数据类型、字符串，甚至用户自定义的类对象。
    std::list<int> intList;               // 存储整数的 list
    std::list<std::string> strList;       // 存储字符串的 list

    // 2. 插入操作
    // 使用 push_back 在链表末尾插入元素。
    intList.push_back(10);                // 在尾部插入 10
    intList.push_back(20);                // 在尾部插入 20

    // 使用 push_front 在链表头部插入元素。
    intList.push_front(5);                // 在头部插入 5

    // 使用 insert 在指定位置插入元素。
    auto it = intList.begin();
    std::advance(it, 1);                  // 将迭代器移动到第 2 个位置
    intList.insert(it, 15);               // 在第 2 个位置插入 15

    // 3. 删除操作
    // 使用 pop_back 删除链表尾部元素。
    intList.pop_back();                   // 删除最后一个元素

    // 使用 pop_front 删除链表头部元素。
    intList.pop_front();                  // 删除第一个元素

    // 使用 erase 删除指定位置的元素。
    it = intList.begin();
    intList.erase(it);                    // 删除第一个元素

    // 4. 遍历操作
    // 使用范围循环访问元素。
    for (int num : intList) {
        std::cout << num << " ";          // 输出链表的每个元素
    }
    std::cout << std::endl;

    // 5. 查询操作
    // 使用 size() 获取链表的大小。
    std::cout << "Size: " << intList.size() << std::endl;

    // 使用 empty() 检查链表是否为空。
    if (intList.empty()) {
        std::cout << "List is empty!" << std::endl;
    }

    return 0;
}

```

## 应用

```cpp
#include <iostream>
#include <list>
#include <string>

class Editor {
private:
    std::list<std::string> text;             // 使用 list 容器存储文本的每一行
    std::list<std::string>::iterator current; // 当前行的迭代器
    int currentLineNumber;                   // 当前行号
    bool inserting;                          // 表示是否处于插入模式

public:
    // 构造函数：初始化编辑器的字段
    Editor() : current(text.begin()), currentLineNumber(-1), inserting(false) {}

    // 解析输入，判断是命令还是普通文本
    std::string parse(const std::string& line) {
        if (line.substr(0, 1) != "$") { // 如果不是命令，尝试作为插入文本
            if (inserting)
                return insert_command(line);
            else
                return "$Error: Command must start with '$'.";
        }
        return command_check(line); // 解析命令行
    }

    // 检查并处理命令行
    std::string command_check(const std::string& line) {
        if (line == "$Insert") { // 开启插入模式
            inserting = true;
            return "";
        } else if (line.substr(0, 7) == "$Delete") { // 删除命令
            size_t pos1 = line.find(' ', 7);        // 找到第一个空格位置
            size_t pos2 = line.find(' ', pos1 + 1); // 找到第二个空格位置
            if (pos1 == std::string::npos || pos2 == std::string::npos)
                return "$Error: Missing line numbers."; // 错误：缺少行号
            int k = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1)); // 第一个行号
            int m = std::stoi(line.substr(pos2 + 1));                  // 第二个行号
            return delete_command(k, m);
        } else if (line.substr(0, 5) == "$Line") { // 行定位命令
            int m = std::stoi(line.substr(6));    // 获取目标行号
            return line_command(m);
        } else if (line == "$Done") { // 完成命令
            return done_command();
        } else {
            return "$Error: Unknown command."; // 未知命令
        }
    }

    // 插入命令：在当前行后插入一行文本
    std::string insert_command(const std::string& line) {
        if (line.empty()) return "$Error: Line is empty."; // 错误：空行
        current = text.insert(++current, line);           // 在当前行后插入新行
        currentLineNumber++;
        return "";
    }

    // 删除命令：删除从第 k 行到第 m 行的所有行
    std::string delete_command(int k, int m) {
        if (k < 0 || m >= text.size() || k > m)
            return "$Error: Invalid line range."; // 错误：无效的行范围
        auto itStart = text.begin();             // 起始迭代器
        auto itEnd = text.begin();               // 结束迭代器
        std::advance(itStart, k);                // 移动到第 k 行
        std::advance(itEnd, m + 1);              // 移动到第 m+1 行
        text.erase(itStart, itEnd);              // 删除范围内的行

        if (currentLineNumber >= k && currentLineNumber <= m) { // 当前行在删除范围内
            currentLineNumber = k - 1;                          // 更新当前行号
            current = (k > 0) ? std::prev(itStart) : text.begin();
        } else if (currentLineNumber > m) { // 当前行在删除范围之后
            currentLineNumber -= (m - k + 1); // 更新行号
        }
        return "";
    }

    // 行定位命令：将第 m 行设置为当前行
    std::string line_command(int m) {
        if (m < -1 || m >= text.size())
            return "$Error: Invalid line number."; // 错误：无效的行号
        auto it = text.begin();
        std::advance(it, m + 1); // 移动迭代器到目标行
        current = it;
        currentLineNumber = m;
        return "";
    }

    // 完成命令：打印最终文本并退出
    std::string done_command() {
        std::string result = "Final Text:\n"; // 初始化输出结果
        int lineNum = 0;
        for (auto it = text.begin(); it != text.end(); ++it) { // 遍历每一行
            if (it == current)
                result += "> "; // 当前行标记
            else
                result += "  ";
            result += std::to_string(lineNum++) + ": " + *it + "\n"; // 加上行号和内容
        }
        return result;
    }
};

int main() {
    Editor editor;
    std::string input;

    while (true) {
        std::cout << "Enter command or text: ";
        std::getline(std::cin, input);
        std::string result = editor.parse(input); // 解析用户输入
        if (!result.empty()) std::cout << result << std::endl;
        if (input == "$Done") break; // 完成命令退出循环
    }
    return 0;
}

```
