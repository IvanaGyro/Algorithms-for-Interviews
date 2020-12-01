
#include <vector>

#include "test.h"
#include "tree.h"

using namespace std;

class LCA {
   public:
    LCA(GeneralTreeNode<int>* root, int n) {
        level.resize(n);
        table.resize(n);
        table[root->val].push_back(root->val);
        level[root->val] = 0;
        build_table(root);
    }

    void build_table(GeneralTreeNode<int>* root) {
        int lev = level[root->val];
        for (auto* child : root->children) {
            level[child->val] = lev + 1;
            table[child->val].push_back(root->val);
            for (int i{0}, mask{1}; mask <= lev; ++i, mask <<= 1) {
                table[child->val].push_back(table[table[child->val][i]][i]);
            }
            build_table(child);
        }
    }

    int lca(int a, int b) {
        if (level[a] > level[b]) swap(a, b);
        int diff = level[b] - level[a];
        int i{};
        while (diff) {
            if (diff & 1) {
                b = table[b][i];
            }
            diff >>= 1;
            ++i;
        }
        if (a != b) {
            int i = table[a].size() - 1;
            while (i >= 0) {
                if (table[a][i] != table[b][i]) {
                    a = table[a][i];
                    b = table[b][i];
                }
                --i;
            }
            a = table[a][0];
        }
        return a;
    }

   private:
    vector<int> level;
    vector<vector<int>> table;
};

int main() {
    // Number of nodes
    int n = 9;

    GeneralTreeNode<int>* root =
        build_general_tree<int>({{1}, {2, 3, 4}, {5}, {6, 7, 8}, {9}});
    LCA lca(root, n + 1);
    test(lca.lca(6, 9), 1);
    test(lca.lca(5, 9), 1);
    test(lca.lca(6, 8), 3);
    test(lca.lca(6, 1), 1);
}
