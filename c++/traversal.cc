#include <queue>
#include <stack>
#include <vector>

#include "test.h"
#include "tree.h"

using namespace std;

vector<int> bfs(TreeNode<int>* root) {
    if (!root) return {};
    vector<int> ans;
    queue<TreeNode<int>*> q;
    q.push(root);
    while (!q.empty()) {
        auto* cur = q.front();
        q.pop();
        ans.push_back(cur->val);
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return ans;
}

void in_order_recursion(TreeNode<int>* root, vector<int>& ans) {
    if (!root) return;
    in_order_recursion(root->left, ans);
    ans.push_back(root->val);
    in_order_recursion(root->right, ans);
}
vector<int> in_order_recursion(TreeNode<int>* root) {
    vector<int> ans;
    in_order_recursion(root, ans);
    return ans;
}

void pre_order_recursion(TreeNode<int>* root, vector<int>& ans) {
    if (!root) return;
    ans.push_back(root->val);
    pre_order_recursion(root->left, ans);
    pre_order_recursion(root->right, ans);
}
vector<int> pre_order_recursion(TreeNode<int>* root) {
    vector<int> ans;
    pre_order_recursion(root, ans);
    return ans;
}

void post_order_recursion(TreeNode<int>* root, vector<int>& ans) {
    if (!root) return;
    post_order_recursion(root->left, ans);
    post_order_recursion(root->right, ans);
    ans.push_back(root->val);
}
vector<int> post_order_recursion(TreeNode<int>* root) {
    vector<int> ans;
    post_order_recursion(root, ans);
    return ans;
}

vector<int> in_order_stack(TreeNode<int>* root) {
    vector<int> ans;
    stack<TreeNode<int>*> s;
    TreeNode<int>* next{root};
    while (next || !s.empty()) {
        if (next) {
            s.push(next);
            next = next->left;
        } else {
            next = s.top();
            s.pop();
            ans.push_back(next->val);
            next = next->right;
        }
    }
    return ans;
}

vector<int> pre_order_stack(TreeNode<int>* root) {
    if (!root) return {};
    vector<int> ans;
    stack<TreeNode<int>*> s;
    s.push(root);
    while (s.size()) {
        auto* cur{s.top()};
        s.pop();
        if (cur) {
            ans.push_back(cur->val);
            s.push(cur->right);
            s.push(cur->left);
        }
    }
    return ans;
}

vector<int> post_order_stack(TreeNode<int>* root) {
    vector<int> ans;
    stack<TreeNode<int>*> s;
    TreeNode<int>* next{root};
    while (next || s.size()) {
        if (next) {
            s.push(next);
            s.push(next);
            next = next->left;
        } else {
            next = s.top();
            s.pop();
            if (s.size() && s.top() == next) {
                next = next->right;
            } else {
                ans.push_back(next->val);
                next = nullptr;
            }
        }
    }
    return ans;
}

vector<int> in_order_morris(TreeNode<int>* root) {
    vector<int> ans;
    TreeNode<int>* ptr;
    while (root) {
        ptr = root->left;
        if (ptr) {
            while (ptr->right && ptr->right != root) ptr = ptr->right;
            if (!ptr->right) {
                ptr->right = root;
                root = root->left;
            } else {
                ans.push_back(root->val);
                root = root->right;
                ptr->right = nullptr;
            }
        } else {
            ans.push_back(root->val);
            root = root->right;
        }
    }
    return ans;
}

vector<int> pre_order_morris(TreeNode<int>* root) {
    vector<int> ans;
    TreeNode<int>* ptr;
    while (root) {
        ptr = root->left;
        if (ptr) {
            while (ptr->right && ptr->right != root) ptr = ptr->right;
            if (!ptr->right) {
                ptr->right = root;
                ans.push_back(root->val);
                root = root->left;
            } else {
                root = root->right;
                ptr->right = nullptr;
            }
        } else {
            ans.push_back(root->val);
            root = root->right;
        }
    }
    return ans;
}

vector<int> post_order_morris(TreeNode<int>* root) {
    vector<int> ans;
    TreeNode<int>* dummy = new TreeNode<int>();
    dummy->left = root;
    root = dummy;
    TreeNode<int>* ptr;
    while (root) {
        ptr = root->left;
        if (ptr) {
            while (ptr->right && ptr->right != root) {
                ptr = ptr->right;
            }
            if (!ptr->right) {
                ptr->right = root;
                root = root->left;
            } else {
                TreeNode<int>* cur = root->left;
                TreeNode<int>* next = cur->right;
                TreeNode<int>* tmp;
                while (cur != ptr) {
                    tmp = next->right;
                    next->right = cur;
                    cur = next;
                    next = tmp;
                }
                next = cur->right;
                ans.push_back(cur->val);
                while (cur != root->left) {
                    tmp = next->right;
                    next->right = cur;
                    cur = next;
                    next = tmp;
                    ans.push_back(cur->val);
                }
                ptr->right = nullptr;
                root = root->right;
            }
        } else {
            root = root->right;
        }
    }
    delete dummy;
    return ans;
}

int main() {
    auto* root = build_tree<int>({1, 2, 3, nullptr, 5, 6, nullptr, 7});
    test(bfs(root), {1, 2, 3, 5, 6, 7});

    test(in_order_recursion(root), {2, 7, 5, 1, 6, 3});
    test(pre_order_recursion(root), {1, 2, 5, 7, 3, 6});
    test(post_order_recursion(root), {7, 5, 2, 6, 3, 1});

    test(in_order_stack(root), {2, 7, 5, 1, 6, 3});
    test(pre_order_stack(root), {1, 2, 5, 7, 3, 6});
    test(post_order_stack(root), {7, 5, 2, 6, 3, 1});

    test(in_order_morris(root), {2, 7, 5, 1, 6, 3});
    test(pre_order_morris(root), {1, 2, 5, 7, 3, 6});
    test(post_order_morris(root), {7, 5, 2, 6, 3, 1});
}
