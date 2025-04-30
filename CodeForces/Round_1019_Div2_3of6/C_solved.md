# C. Median Splits

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

The median of an array $b_1, b_2, \ldots b_m$, written as $\operatorname{med}(b_1, b_2, \ldots, b_m)$, is the $\left\lceil \frac{m}{2} \right\rceil$-th-  smallest element of array $b$.

You are given an array of integers $a_1, a_2, \ldots, a_n$ and an integer $k$. You need to determine whether there exists a pair of indices $1 \le l < r < n$ such that:

$$\operatorname{med}(\operatorname{med}(a_1, a_2, \ldots, a_l), \operatorname{med}(a_{l+1}, a_{l+2}, \ldots, a_r), \operatorname{med}(a_{r+1}, a_{r+2}, \ldots, a_n)) \le k.$$

In other words, determine whether it is possible to split the array into three contiguous subarrays-  such that the median of the three subarray medians is less than or equal to $k$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two integers $n$ and $k$ ($3 \le n \le 2 \cdot 10^5$, $1 \le k \le 10^9$) — the length of the array $a$ and the constant $k$.
- The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^9$) — the elements of the array $a$.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## Output

- For each testcase, output " YES " if such a split exists, and " NO " otherwise.
- You can output the answer in any case (upper or lower). For example, the strings " yEs ", " yes ", " Yes ", and " YES " will be recognized as positive responses.

## Solution

길이가 $len$ 인 배열 $Arr[len]$ 의 $median$ 값이 $K$ 이하 일 경우를 생각 해보자.  

배열 $Arr$ 의 모든 요소들 중, 값의 크기가 $K$ 이하인 요소의 개수가 $\left\lceil \frac{len}{2} \right\rceil$ 이상이면 된다.  

따라서, $A$ 를 3개의 구간으로 분할 시, 3개 중 2개의 배열의 $median$ 값이 $K$ 이하이면, 조건을 만족하는 $l$ 과 $r$ 이 존재한다.  

요소 $A[i]$ 에 대해,  

- $A[i] <= K$ 이면, $+1$
- $K < A[i]$ 이면, $-1$

위 연산을 순차적으로 수행한 배열을 $Prefix$ 라 하면, $0 <= Prefix[i]$ 인 인덱스 $i$ 에 대해 구간 $[0, i]$ 는 $median$ 이 $K$ 이하 이다.

$i < j$ 이고, $Prefix[i] <= Prefix[j]$ 일 때,  
$[0, i]$ 에서 $K$ 이하인 요소의 개수를 $low_{i}$ , 초과인 요소의 개수를 $high_{i}$ 라 하고,  
$[0, j]$ 에서 $K$ 이하인 요소의 개수를 $low_{j}$ , 초과인 요소의 개수를 $high_{j}$ 라 하면, 아래의 관계를 관찰할 수 있다.  

```math
i < j \rightarrow low_i + high_i < low_j + high_j \\
Prefix[i] <= Prefix[j] \rightarrow high_i - low_i <= high_j - low_j \\
low_j - low_i <= high_j - high_i \\
```

따라서, 구간 $[i + 1, j]$ 또한 $median$ 값이 $K$ 이하 이다.  

- 3 분할 시, 왼쪽 배열과 중간 배열의 $median <= K$ 인 경우는 $i < j$ 이고 $Prefix[i] < Prefix[j]$ 를 만족하는 경우 이다.

반대로, 중간 배열과 오른쪽 배열이 $median$ 값이 $K$ 이하인 경우 또한 같은 맥락이다.  
단, $Prefix$ 와 달리 $Suffix[i]$ 는 구간 $[i, N - 1]$ 에 대한 정보값 이기에, 구성 시 역순으로, 구성 이후 유효 관계 검사 또한 역순으로 해야 한다.  

또한, 문제의 조건에 따라 $0 \leq l < r < N - 1$ 이므로, 탐색 대상의 범위는  
$Prefix$ 의 경우 $[0, N - 2]$  
$Suffix$ 의 경우 $[1, N - 1]$ 로 해야 한다.  

위의 두 가지 경우에 대해 탐색 과정은 $O(N)$ 으로 선형적 이다.  
마지막으로 왼쪽과 오른쪽이 $median \leq K$ 인 경우는, 단순 선형 탐색으로 가능 판별이 가능하므로,  
전체 시간 복잡도는 $O(N)$ 으로 문제의 시간 제한을 만족한다.  

```cpp
constexpr int N_MAX = 2e5;
constexpr int NIL = -1;

int Prefix[N_MAX];
int Suffix[N_MAX];
int A[N_MAX];

void solve(void)
{
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> A[i];

    memset(Prefix, 0x00, N * sizeof(Prefix[0]));
    memset(Suffix, 0x00, N * sizeof(Suffix[0]));
    for (int i = 0; i < N; ++i)
        Prefix[i] = ((i > 0) ? Prefix[i - 1] : 0) + ((A[i] <= K) ? 1 : -1);
    for (int i = N - 1; i > -1; --i)
        Suffix[i] = ((i < N - 1) ? Suffix[i + 1] : 0) + ((A[i] <= K) ? 1 : -1);
    
    vector<int> prefix;
    for (int i = 0; i < N - 1; ++i)
        if (0 <= Prefix[i])
            prefix.push_back(Prefix[i]);
    if (prefix.size() > 0)
    {
        int min_pre = prefix[0];
        for (int i = 1; i < prefix.size(); ++i)
        {
            if (min_pre <= prefix[i])
            {
                cout << "YES" << ENDL;
                return;
            }
            min_pre = min(min_pre, prefix[i]);
        }
    }

    vector<int> suffix;
    for (int i = N - 1; i > 0; --i)
        if (0 <= Suffix[i])
            suffix.push_back(Suffix[i]);
    if (suffix.size() > 0)
    {
        int min_suf = suffix[0];
        for (int i = 1; i < suffix.size(); ++i)
        {
            if (min_suf <= suffix[i])
            {
                cout << "YES" << ENDL;
                return;
            }
            min_suf = min(min_suf, suffix[i]);
        }   
    }
    
    int l = NIL, r = NIL;
    for (int i = 0; i < N - 2; ++i)
        if (0 <= Prefix[i])
        {
            l = i;
            break;
        }
    for (int i = N - 2; i > 0; --i)
        if (0 <= Suffix[i])
        {
            r = i;
            break;
        }
    if (l != NIL && r != NIL && l < r)
        cout << "YES" << ENDL;
    else
        cout << "NO" << ENDL;
}
```
