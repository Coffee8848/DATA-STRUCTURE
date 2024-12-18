# 数据结构的概念

程序 = 数据结构+算法

软件 = 数据结构+算法+文件

#### **数据结构的定义**

* 数据结构是指数据元素的集合及其相互关系，包括：
  1. **数据的*逻辑结构***：
     * 集合
     * 线性结构
     * 树形结构
     * 图形结构
  2. **数据的*存储结构***：
     * 数据在内存中的表示，如指针、数组等。
  3. **数据的*操作***：
     * 操作目的是实现算法（算法是数据操作的具体实现）。

# cpp基础

---

# 1.编程基础

**输入输出**：`cin`，`cout`，格式化输入输出。

```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    std::cout << "You entered: " << number << std::endl;
    return 0;
}
```

**控制流**：条件语句（`if-else`，`switch-case`）、循环语句（`for`，`while`，`do-while`）。

```cpp
//if
if(条件) {}
else if(另一个条件){}
else{}

///////
//switch case

switch (a){
    case 1;
    ///一些代码
    break;
    case 2;
   ////
    break;
    default:
//////
    break;
}

```

~~~cpp
//循环
for (初始化;条件 ;增长) {
}
//while
初始化 i = 0
while(条件)
{
      函数和增长
}
/// do while
do {
    // 循环体
} while (condition);
~~~

#### **函数**：函数声明、定义与调用，默认参数

##### 默认函数

**默认参数必须从右向左依次指定**，即不能在中间参数指定默认值而不指定右边参数的默认值

```cpp
// 正确
void example(int a, int b = 5, int c = 10);

// 错误
void example(int a = 1, int b, int c = 10);
```

## 函数的 传值 引用 指针传递

### C++ 参数传递方式总结

C++函数调用中参数的传递方式主要有三种：**值传递（Pass by Value）**、**引用传递（Pass by Reference）**、以及**指针传递（Pass by Pointer）**。

### 1. 值传递（Pass by Value）

**定义**：当函数以值传递参数时，函数接收到的是实参的一个副本，函数内部对参数变量的修改不会影响到函数外的原始变量。

#### 示例代码

```cpp
#include <iostream>
using namespace std;

void incrementByValue(int x) {
    x = x + 1;    // 这里只修改了 x 的副本
}

int main() {
    int a = 10;
    incrementByValue(a);
    cout << "a = " << a << endl; // 输出结果仍为10
    return 0;
}
```

#### 2. 引用传递（Pass by Reference）

**定义**：引用传递是通过函数参数的引用类型来实现的，函数对参数的更改将会直接影响到调用者的实参。 加了个&

#### 示例代码

```cpp
#include <iostream>
using namespace std;

void incrementByReference(int &x) {
    x = x + 1;    // 直接修改外部实参
}

int main() {
    int a = 10;
    incrementByReference(a);
    cout << "a = " << a << endl; // 输出结果为11
    return 0;
}
```

---

### 3. 指针传递（Pass by Pointer）

**定义**：传入函数的是一个指针变量的值（即内存地址）。函数可以通过指针间接访问或修改指针所指向的实参对象。

##### 示例代码

```cpp
#include <iostream>
using namespace std;

void incrementByPointer(int *p) {
    if (p != nullptr) {
        *p = *p + 1; // 修改 p 指向的值
    }
}

int main() {
    int a = 10;
    incrementByPointer(&a);
    cout << "a = " << a << endl; // 输出结果为11
    return 0;
}
```

##### 4. 参数传递方式对比总结


| 项目         | 值传递                 | 引用传递                       | 指针传递                           |
| ------------ | ---------------------- | ------------------------------ | ---------------------------------- |
| 内存开销     | 需要拷贝参数           | 无需拷贝，直接使用原对象       | 无需拷贝，传递地址                 |
| 能否修改实参 | 否                     | 是                             | 是                                 |
| 使用难度     | 最简单                 | 简单                           | 稍复杂（需解引用与空指针检查）     |
| 适用场景     | 小数据类型，不需改实参 | 大对象参数或需改实参，安全可控 | 动态内存、复杂数据结构、可为空指向 |

# 2. **面向对象编程（OOP）**

**继承和派生

```cpp
class Base {
public:
    void baseMethod() {
        std::cout << "Base method" << std::endl;
    }
};

class Derived : public Base {
public:
    void derivedMethod() {
        std::cout << "Derived method" << std::endl;
    }
};
```

### 单继承和多继承

#### 单继承

单继承是指一个派生类只能有一个基类。

```cpp
class Base {
    // 基类内容
};

class Derived : public Base {
    // 派生类内容
};
```

#### 多继承

多继承是指一个派生类可以有多个基类。

```cpp
class Base1 {
    // 基类1内容
};

class Base2 {
    // 基类2内容
};

class Derived : public Base1, public Base2 {
    // 派生类内容
};
```

### 虚函数和多态

#### 虚函数

虚函数是基类中声明为 `virtual` 的成员函数，允许在派生类中重写。虚函数实现了运行时多态。

**示例：**

```cpp
class Base {
public:
    virtual void show() {
        std::cout << "Base show" << std::endl;
    }
};

class Derived : public Base {
public:
    void show() override {
        std::cout << "Derived show" << std::endl;
    }
};
```

#### 多态

多态是指通过基类指针或引用调用虚函数时，根据实际对象类型调用相应的派生类函数。

**示例：**

```cpp
void display(Base* obj) {
    obj->show();
}

int main() {
    Base base;
    Derived derived;
    display(&base);    // 输出 "Base show"
    display(&derived); // 输出 "Derived show"
    return 0;
}
```

> 注意cpp的重载和java概念不同

### 运算符重载

```cpp
 //#include <iostream>

class Point {
private:
    int x;
    int y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // 重载 + 运算符
    Point operator+(const Point& other) const {//operator+ 是函数   +后面的是参数  这样就实现了运算符重载
        return Point(x + other.x, y + other.y);
    }

    void display() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2; // 使用重载的 + 运算符
    p3.display(); // 输出 (4, 6)
    return 0;
}
```

### 访问权限

C++ 提供了三种访问权限：`public`、`protected` 和 `private`。

- `public`：公有成员可以被任何类访问。
- `protected`：保护成员只能被本类和派生类访问。
- `private`：私有成员只能被本类访问。

**友元

友元（friend）是指可以访问类的私有和保护成员的非成员函数或其他类。

**友元函数：**

```cpp
class MyClass {
private:
    int privateVar;
public:
    MyClass() : privateVar(0) {}
    friend void showPrivateVar(MyClass& obj);
};

void showPrivateVar(MyClass& obj) {
    std::cout << "Private variable: " << obj.privateVar << std::endl;
}
```

**友元类：**

```cpp
class MyClass {
private:
    int privateVar;
public:
    MyClass() : privateVar(0) {}
    friend class FriendClass;
};

class FriendClass {
public:
    void showPrivateVar(MyClass& obj) {
        std::cout << "Private variable: " << obj.privateVar << std::endl;
    }
};
```

### 动态内存分配

#### `new` 和 `delete`

**语法**：

```cpp
Type* ptr = new Type;          // 分配单个对象
Type* arr = new Type[size];    // 分配数组
delete ptr;       // 释放单个对象
delete[] arr;     // 释放数组
```

```#### `malloc` 和 `free`

`malloc` 和 `free` 是 C 标准库中的函数，用于动态内存分配和释放。C++ 也支持这两个函数，但推荐使用 `new` 和 `delete`。

**`malloc` 函数**：

- 用于在堆上分配内存，并返回指向新分配内存的指针。
- 需要指定分配的字节数。

**语法**：

```cpp
void* ptr = malloc(size_t size);
```

**示例**：

```cpp
int* p = (int*)malloc(sizeof(int));  // 分配一个 int
*p = 10;
int* arr = (int*)malloc(5 * sizeof(int));  // 分配一个 int 数组
for (int i = 0; i < 5; ++i) {
    arr[i] = i;
}
```

**`free` 函数**：

- 用于释放由 `malloc` 分配的内存。

```**示例**：

```cpp
free(p);   // 释放单个 int
free(arr); // 释放 int 数组
```

### 引用与指针的区别

#### 引用与指针的区别

1. **初始化**：

   - 引用必须在声明时初始化。
   - 指针可以在声明后初始化。
2. **重新赋值**：

   - 引用一旦初始化，不能改变引用的对象。
   - 指针可以在任何时候被重新赋值。
3. **空值**：

   - 引用不能为 `null`。
   - 指针可以为 `nullptr`。
4. **语法**：

   - 引用使用 `&` 符号。
   - 指针使用 `*` 符号。

#### 什么时候用指针，什么时候用引用

1. **使用引用**：

   - 当你确定引用的对象不会改变时。
   - 当你希望避免空指针错误时。
   - 当你希望函数参数传递时避免拷贝，但不希望修改原始对象时（使用 `const` 引用）。
2. **使用指针**：

   - 当你需要动态分配内存时。
   - 当你需要指向不同对象时。
   - 当你需要表示空值时（使用 `nullptr`）。

---

### 4. **模板与泛型编程**

**函数模板**：`template<typename T>`。

```cpp

#include <iostream>

// 定义一个函数模板，用于交换两个变量的值
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swap(x, y); // 使用模板函数交换整数
    std::cout << "x = " << x << ", y = " << y << std::endl;

    double a = 1.1, b = 2.2;
    swap(a, b); // 使用模板函数交换双精度浮点数
    std::cout << "a = " << a << ", b = " << b << std::endl;

    return 0;
}
```

类模板

```cpp
#include <iostream>

template <typename T>
class MyClass {
private:
    T data;
public:
    MyClass(T data) : data(data) {}

    void display() const;
    T getData() const;
};

// 成员函数的定义
template <typename T>
void MyClass<T>::display() const {
    std::cout << "Data: " << data << std::endl;
}

template <typename T>
T MyClass<T>::getData() const {
    return data;
}

int main() {
    MyClass<int> obj(42);
    obj.display(); // 输出: Data: 42
    std::cout << "Data: " << obj.getData() << std::endl; // 输出: Data: 42
    return 0;
}
```

`T MyClass<T>::getData() const {` 成员函数每个函数前都要写`template <typename T>`  并且函数类型前面要有

返回类型- 类名`<T>` :: 函数名() {}

---

### 5. **STL（Standard Template Library）**

**容器**：

顺序容器：`vector`，`deque`，`list`。

关联容器：`map`，`set`，`multimap`，`multiset`。

无序容器：`unordered_map`，`unordered_set`。

**迭代器**：迭代器的种类、基本操作。

**算法**：`sort`，`find`，`count`，`for_each` 等常用算法。
