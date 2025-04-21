#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

struct Segment
{
    ll sum = 0;
    int min_data = numeric_limits<int>::max();
    int max_data = numeric_limits<int>::min();
    Segment() = default;
    void update_segment(const int data)
    {
        this->sum = data;
        this->max_data = data;
        this->min_data = data;
    }
    void merge(const Segment &L, const Segment &R)
    {
        this->sum = L.sum + R.sum;
        this->min_data = min(L.min_data, R.min_data);
        this->max_data = max(L.max_data, R.max_data);
    }
};

template<typename SegmentType>
class SegmentTree
{
private:
    vector<SegmentType> m_Tree;
    int m_SZ;

public:
    SegmentTree() = default;
    ~SegmentTree() = default;

    explicit SegmentTree(const int sz) : m_SZ(sz), m_Tree(2 * sz) {}

    void update(int i, const int data)
    {
        m_Tree[i += m_SZ].update_segment(data);
        for (int p = i >> 1; p > 0; p >>= 1)
            m_Tree[p].merge(m_Tree[p << 1], m_Tree[(p << 1) | 1]);
    }

    Segment range(int l, int r)
    {
        SegmentType res;
        l += m_SZ, r += m_SZ;
        while (l < r)
        {
            if (l & 1) res.merge(res, m_Tree[l++]);
            if (r & 1) res.merge(res, m_Tree[--r]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};