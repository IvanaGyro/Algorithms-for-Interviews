#include <vector>

#include "test.h"

using namespace std;

class FenwickTree
{
public:
    explicit FenwickTree(int n) : n{n}
    {
        bits.assign(n, 0);
    }

    int prefix_sum(int i)
    {
        int sum{};
        while (i >= 0)
        {
            sum += bits[i];
            i = (i & (i + 1)) - 1;
        }
        return sum;
    }

    void add(int i, int delta)
    {
        while (i < n)
        {
            bits[i] += delta;
            i = i | (i + 1);
        }
    }

    vector<int> bits;
    int n;
};

class FenwickTreeOneIndexed
{
public:
    explicit FenwickTreeOneIndexed(int n) : n{n}
    {
        bits.assign(n + 1, 0);
    }

    int prefix_sum(int i)
    {
        int sum{};
        ++i;
        while (i > 0)
        {
            sum += bits[i];
            i -= i & -i;
        }
        return sum;
    }

    void add(int i, int delta)
    {
        ++i;
        while (i <= n)
        {
            bits[i] += delta;
            i += i & -i;
        }
    }

    vector<int> bits;
    int n;
};

int main()
{
    FenwickTree tree0(10);
    FenwickTreeOneIndexed tree1(10);

    tree0.add(0, 1);
    tree0.add(5, 2);
    tree0.add(7, 3);
    tree1.add(0, 1);
    tree1.add(5, 2);
    tree1.add(7, 3);

    test(tree0.prefix_sum(5), 3);
    test(tree0.prefix_sum(8), 6);
    test(tree1.prefix_sum(5), 3);
    test(tree1.prefix_sum(8), 6);

    tree0.add(6, 5);
    tree1.add(6, 5);

    test(tree0.prefix_sum(5), 3);
    test(tree0.prefix_sum(8), 11);
    test(tree1.prefix_sum(5), 3);
    test(tree1.prefix_sum(8), 11);
}
