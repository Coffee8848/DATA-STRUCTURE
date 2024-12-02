#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <numeric>

// 模拟的二叉搜索树类
template<typename T>
class BinSearchTree {
private:
    struct Node {
        T item;
        Node* left;
        Node* right;
        Node(T val) : item(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int count;

    int heightHelper(Node* node) const {
        if (node == nullptr) {
            return -1; // 空树的高度为 -1
        }
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinSearchTree() : root(nullptr), count(0) {}

    ~BinSearchTree() {
        destroyTree(root);
    }

    void insert(const T& item) {
        Node* newNode = new Node(item);
        if (root == nullptr) {
            root = newNode;
        } else {
            Node* current = root;
            Node* parent = nullptr;
            while (current != nullptr) {
                parent = current;
                if (item < current->item) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            if (item < parent->item) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
        count++;
    }

    int height() const {
        return heightHelper(root);
    }

    int size() const {
        return count;
    }
};

// 模拟插入和计算树高的函数
template<typename T>
void simulateBST(int numNodes, int numExperiments) {
    std::vector<int> heights;

    for (int i = 0; i < numExperiments; ++i) {
        BinSearchTree<T> bst;
        std::vector<T> values(numNodes);

        // 生成随机数
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10000);

        for (int j = 0; j < numNodes; ++j) {
            values[j] = dis(gen);
        }

        // 插入随机数到BST
        for (const auto& value : values) {
            bst.insert(value);
        }

        // 计算树高
        int height = bst.height();
        heights.push_back(height);
    }

    // 计算平均树高
    double averageHeight = std::accumulate(heights.begin(), heights.end(), 0.0) / heights.size();

    // 输出结果
    std::cout << "Number of nodes: " << numNodes << ", Average height: " << averageHeight << std::endl;
}

int main() {
    int numExperiments = 100; // 实验次数

    // 变换节点数目，进行多次实验
    for (int numNodes = 10; numNodes <= 1000; numNodes += 10) {
        simulateBST<int>(numNodes, numExperiments);
    }

    return 0;
}