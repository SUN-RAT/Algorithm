#include <vector>

using namespace std;

int binary_search(const vector<int> &vec, const int x)
{
    int n = vec.size();
    int l = -1, r = n;
    
    while(l + 1 < r)
    {
        int mid = l + (r - l) / 2;
        if (vec[mid] < x)
            l = mid;
        else
            r = mid;
    }

    return r;
}