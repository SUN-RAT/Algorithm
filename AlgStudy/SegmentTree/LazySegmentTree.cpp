#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

struct LazyNode
{
    int delta = 0;
    LazyNode() = default;
    inline bool has_update(void) const
    { return delta != 0; }
    inline void combine(const LazyNode &p)
    { this->delta += p.delta; }
    inline void combine(const int data)
    { this->delta += data; }
    inline void reset(void)
    { this->delta = 0; }
};
struct Segment
{
    ll sum = 0;
    int range = 1;
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
        this->range = L.range + R.range;
    }
    void apply(const LazyNode &lazy)
    {
        this->sum += 1LL * lazy.delta * range;
        this->min_data += lazy.delta;
        this->max_data += lazy.delta;
    }
    void apply(const int data)
    {
        this->sum += 1LL * data * range;
        this->min_data += data;
        this->max_data += data;
    }
};

template<typename SegmentType, typename LazyNode>
class LazySegmentTree
{
private:
    vector<SegmentType> m_Tree;
    vector<LazyNode> m_Lazy;
    int m_SZ;
    int m_Height;

    inline void lazy_propagate(const int i)
    {
        m_Tree[i].apply(m_Lazy[i >> 1]);
        if (i < m_SZ)
            m_Lazy[i].combine(m_Lazy[i >> 1]);
    }

    inline void instinct_apply(const int i, const int data)
    {
        m_Tree[i].apply(data);
        if (i < m_SZ)
            m_Lazy[i].combine(data);
    }

public:
    LazySegmentTree() = default;
    ~LazySegmentTree() = default;

    explicit LazySegmentTree(const int sz) : m_Height(sizeof(int) * 8 - __builtin_clz(sz)), m_SZ(sz), m_Lazy(sz), m_Tree(2 * sz)
    {
        // build
    }

    void update_element(int i, const int data)
    {
        i += m_SZ;
        m_Tree[i].update_segment(data);
        for (int p = i >> 1; p > 0; p >>= 1)
            m_Tree[p].merge(m_Tree[p << 1], m_Tree[(p << 1) | 1]);
    }

    void push_update(const int leaf)
    {
        for (int p = leaf >> 1; p > 0; p >>= 1)
        {
            m_Tree[p].merge(m_Tree[p << 1], m_Tree[(p << 1) | 1]);
            m_Tree[p].apply(m_Lazy[p]);
        }
    }

    void range_update(int l, int r, const int data)
    {
        l += m_SZ, r += m_SZ;
        int left = l, right = r - 1;
        while(l < r)
        {
            if (l & 1) instinct_apply(l++, data);
            if (r & 1) instinct_apply(--r, data);
            l >>= 1;
            r >>= 1;
        }
        push_update(left);
        push_update(right);
    }

    void pull_update(const int leaf)
    {
        for (int h = m_Height; h > 0; --h)
        {
            int p = leaf >> h;
            if (m_Lazy[p].has_update())
            {
                lazy_propagate(p << 1);
                lazy_propagate((p << 1) | 1);
                m_Lazy[p].reset();
            }
        }
    }

    SegmentType range_query(int l, int r)
    {
        l += m_SZ, r += m_SZ;
        pull_update(l);
        pull_update(r - 1);

        SegmentType res;
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