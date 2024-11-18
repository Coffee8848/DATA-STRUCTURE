#ifndef APPLICATION_H
#define APPLICATION_H

#include "position.h"

class Application
{
public:
    void initialize(); // 初始化

    Position getStartPosition(); // 获取起始位置  position是返回类型 返回的是position

    bool isValid(const Position& p); // 检查位置 p 是否有效

    void progress(const Position& p); // 通过包含位置 p 来扩展

    bool success(const Position& p); // 检查在位置 p 是否获得成功的解决方案

    void goBack(const Position& p); // 从位置 p 回退一步

    void print(); // 打印应用程序的配置

    class Iterator // 内部类
    {
    public:
        Iterator(); // 默认构造函数
        Iterator(const Position& currP); // 带输入位置的构造函数
        ~Iterator();

        Position getNextPosition(); // 获取下一个可能的位置
        bool noNextPosition(); // 检查是否所有可能的位置都已尝试

    private:
        void *currItrPosPtr; // 查找下一个位置的附加信息
    };
};

#endif