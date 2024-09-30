# 编译器
CXX := g++

# 编译器标志
CXXFLAGS := -Wall -g

# 源文件
SRCS := $(wildcard *.cpp)

# 目标文件
OBJS := $(SRCS:.cpp=.o)

# 可执行文件
TARGET := my_program

# 生成目标文件
all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 生成 .o 文件的规则
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
clean:
    rm -f $(OBJS) $(TARGET)

.PHONY: all clean