#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "test.h"

using std::cout;
using std::vector;
using std::endl;
using std::min;
using std::string;


vector<int> manacher(const string &s)
{
    vector<int> ans;
    int n = s.size();
    ans.resize(n * 2 + 1, 0);
    int r{};
    int c{};
    for (int i{}; i < n; ++i)
    {
        for (int j{}; j < 2; ++j)
        {
            int a_i{i * 2 + 1 + j};
            if (a_i < r)
                ans[a_i] = min(ans[(c * 2) - a_i], r - a_i);
            --ans[a_i];
            int s_r;
            int s_l;
            do
            {
                ++ans[a_i];
                s_r = i + ans[a_i] / 2 + 1;
                s_l = i - ans[a_i] / 2 - 1 + j;
            } while ((ans[a_i] + j) % 2 == 0 ||
                     s_l >= 0 && s_r < n && s[s_r] == s[s_l]);
            int a_r{a_i + ans[a_i]};
            if (a_r > r)
            {
                r = a_r;
                c = a_i;
            }
        }
    }
    return ans;
}

int main()
{
    test(manacher(""), {0});
    test(manacher("aba"), {0, 1, 0, 3, 0, 1, 0});
    test(manacher("aaa"), {0, 1, 2, 3, 2, 1, 0});
    test(manacher("abba"), {0, 1, 0, 1, 4, 1, 0, 1, 0});
    test(manacher("aaaa"), {0, 1, 2, 3, 4, 3, 2, 1, 0});
    test(manacher("dabadabad"), {0, 1, 0, 1, 0, 5, 0, 1, 0, 9, 0, 1, 0, 5, 0, 1, 0, 1, 0});
}