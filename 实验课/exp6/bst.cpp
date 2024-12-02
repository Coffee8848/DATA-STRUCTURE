#include <iostream>
#include <string>
#include "bst.h"


template<typename T>
BinSearchTree<T>::BinSearchTree() {
    root = nullptr;
    count = 0;
}

template <typename T>
int BinSearchTree<T>:: size() const {
    return count;
}

template<typename T>
int BinSearchTree<T>::height() const {
    // 定义一个局部的递归函数
    std::function<int(Node*)> heightHelper = [&](Node* node) -> int {
        if (node == nullptr) {
            return -1; // 空树的高度为 -1
        }
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    };

    // 调用递归函数，传入根节点
    return heightHelper(root);
}
template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insert(const T& item) {
    Node* newNode = new Node();
    newNode->item = item;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;

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

        newNode->parent = parent;
        if (item < parent->item) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    count++;
    return Iterator(newNode);
}
template<typename T>
BinSearchTree<T>::~BinSearchTree() {
    // 定义一个局部的递归函数来删除所有节点
    auto destroyTree = [](Node* node, auto& destroyTreeRef) -> void {
        if (node != nullptr) {
            destroyTreeRef(node->left, destroyTreeRef);
            destroyTreeRef(node->right, destroyTreeRef);
            delete node;
        }
    };

    // 调用递归函数，传入根节点
    destroyTree(root, destroyTree);
}