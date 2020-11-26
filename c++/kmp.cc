#include <deque>
#include <iostream>
#include <string>

#include "test.h"

using std::cout;
using std::deque;
using std::endl;
using std::string;

deque<int> kmp(const string& s, const string& t) {
    deque<int> ans;
    int n = s.size();
    int m = t.size();
    int ps[m]{0};

    for (int i{1}, j{0}; i < m; ++i) {
        while (j != 0 && t[j] != t[i]) j = ps[j - 1];
        if (t[j] == t[i]) ps[i] = ++j;
    }

    for (int i{0}, j{0}; i < n; ++i) {
        while (j != 0 && s[i] != t[j]) j = ps[j - 1];
        if (s[i] == t[j]) {
            ++j;
            if (j == m) {
                ans.push_back(i - m + 1);
                j = ps[m - 1];
            }
        }
    }
    return ans;
}

int main() {
    test(kmp("aabaabaaa", "aa"), {0, 3, 6, 7});
    test(kmp("aabaabaaa", "aab"), {0, 3});
    test(kmp("aabaabaaa", "aaa"), {6});
    test(kmp("asaabaabaaaggdsaabaabaaaabaabaaaa", "aabaabaaa"), {2, 15, 23});
    test(kmp("adsgwadsgcdsgwadsgz", "dsgwadsgz"), {10});
}