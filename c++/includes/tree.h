#ifndef TREE_H
#define TREE_H

#include <initializer_list>
#include <queue>

template <typename T, typename Node>
class _Node {
   public:
    _Node(void *ptr) : ptr{nullptr} {}
    _Node(const T &val) : ptr{new Node(val)} {}
    Node *ptr;
};

template <typename T>
class TreeNode {
   public:
    TreeNode() : val{} {}
    TreeNode(const T &val) : val{val} {}
    TreeNode(const T &val, TreeNode *left, TreeNode *right)
        : val{val}, left{left}, right{right} {}
    T val;
    TreeNode<T> *left{nullptr};
    TreeNode<T> *right{nullptr};
};

template <typename T>
TreeNode<T> *build_tree(std::initializer_list<_Node<T, TreeNode<T>>> il) {
    TreeNode<T> *root{};
    std::queue<TreeNode<T> **> q;
    q.push(&root);
    for (auto &node : il) {
        auto **cur = q.front();
        q.pop();
        *cur = node.ptr;
        if (*cur) {
            q.push(&(*cur)->left);
            q.push(&(*cur)->right);
        }
    }
    return root;
}

template <typename T>
class GeneralTreeNode {
   public:
    GeneralTreeNode() : val{} {}
    GeneralTreeNode(const T &val) : val{val} {}
    GeneralTreeNode(const T &val,
                    const std::vector<GeneralTreeNode<T> *> &children)
        : val{val}, children{children} {}

    T val{};
    std::vector<GeneralTreeNode<T> *> children;
};

template <typename T>
GeneralTreeNode<T> *build_general_tree(
    std::initializer_list<std::initializer_list<_Node<T, GeneralTreeNode<T>>>>
        ill) {
    GeneralTreeNode<T> *dummy{new GeneralTreeNode<T>()};
    std::queue<GeneralTreeNode<T> *> q;
    q.push(dummy);
    for (auto &il : ill) {
        auto *cur = q.front();
        q.pop();
        for (auto node : il) {
            cur->children.push_back(node.ptr);
            q.push(node.ptr);
        }
    }
    GeneralTreeNode<T> *root = dummy->children[0];
    delete dummy;
    return root;
}

#endif  // TREE_H
