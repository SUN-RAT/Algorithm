# F. Trulimero Trulicina

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Trulicina gives you integers $n$, $m$, and $k$. It is guaranteed that $k\geq 2$ and $n\cdot m\equiv 0 \pmod{k}$.

Output a $n$ by $m$ grid of integers such that each of the following criteria hold:

- Each integer in the grid is between $1$ and $k$, inclusive.

- Each integer from $1$ to $k$ appears an equal number of times.

- No two cells that share an edge have the same integer.

It can be shown that such a grid always exists. If there are multiple solutions, output any.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
- The first line of each test case contains three integers $n$, $m$, and $k$ ($2 \leq n\cdot m\leq 2\cdot 10^5, 2\leq k\leq n\cdot m, n\cdot m\equiv 0 \pmod{k})$.
- It is guaranteed that the sum of $n\cdot m$ over all test cases does not exceed $2\cdot 10^5$.

## Output

- For each test case, output $n$ lines, each containing $m$ integers that satisfy the criteria. If there are multiple solutions, output any.

## WA

한눈에 `constructive algorithms` 유형의 문제임을 알고도, 괜히 `Greedy` 로 풀어볼려고 고집을 부리다가 남은 시간을 전부 허비하고도 `AC` 를 못받았다.  

모든 자연수 $[1, k]$ 는 전부 동일한 횟수로 등장하니, $freq$ 가 작은 숫자부터 기록하는 방식으로 접근해볼려고 했다.  
문제의 조건에 맞춰 $(0, \; 0)$ 에서 부터 채워가며, $(r, \; c)$ 에서 $(r - 1, \;c),\;(r,\; c-1)$ 와 다른 숫자들 중 가장 작은 $freq$ 인 숫자를 선택하는 방식으로 접근 했다.  

**문제는 위 조건에서 유효한 숫자가 2개 이상일 때, `tie breaking` 을 하여 하나의 숫자를 선택해야 하는데, 적절한 방법이 떠올리지 않았다.**

## Upsolving

문제의 요구사항에 대해 관찰 부터 한다.

- `Each integer in the grid is between $1$ and $k$, inclusive.`
- Each integer from $1$ to $k$ appears an equal number of times.
  - 모든 자연수 $[1, k]$ 는 동일한 횟수로 등장해야 한다.
  - 위 두 조건은 문제의 입력 조건으로 $(N*M) \; mod \; k \; = \; 0$ 이므로, $k$ 길이의 `permutation` 을 적절하게 $(0, 0)$ 부터 $(N - 1, M - 1)$ 까지 `permutation` 을 기록하면 만족 한다.

- `No two cells that share an edge have the same integer.`

문제의 요구사항인 `No two cells that share an edge have the same integer.` 를 위반 하는 경우를 생각해보면 아래와 같다.  
($(0, 0)$ 부터 $(N - 1, M - 1)$ 까지 행 방향으로 순차적으로 숫자를 기입하는 상황이라 가정)  
$$ Grid(r - 1, c) = Grid(r, c) \quad or  \quad Grid(r, c-1) = Grid(r, c)$$
현재 작성중인 `permutaion` 의 $i$ 번째 요소, $p_i$ 가 $Grid(r, c)$ 에 삽입할려는 요소라면,  

- $Grid(r, c-1) = Grid(r, c)$
  - $Grid(r, c-1) = p_{i - 1}$ 또는 $Grid(r, c-1) = p_{N - 1}$ 이다.
  - 첫 번째 경우는 `permutation` 의 특성 때문에 일어날 수 없다.
  - 두 번째 경우는 $2 \leq K$ 이고, 이전의 `permutation` 을 유지하면 일어날 수 없다.
- $Grid(r - 1, c) = Grid(r, c)$
  - 이 상황은 이전의 `permutation` 을 유지할 시, 한 행 바로 위의 요소가 $p_i$ 인 것이다. 따라서 $Mmodk = 0$ 인 경우만 발생한다.
  - 또한, 반드시 $i = 1$ 이다.
  - `permutation` 을 수정해야 하는데, 변경 시 위반 할 수 있는 $Grid(r, c-1) = Grid(r, c)$, 즉 $p(prev)_N = p(cur)_1$ 이 일어나지 않게 해야 한다.
    - 간단히, `premutation` 의 첫번째 요소를 `cyclic shift` 를 수행하여 새로운 `permutation` 을 생성하면, 문제의 조건들을 위반하지 않는다.

```cpp
#include <bits/stdc++.h>

// clang-format off
#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'
// clang-format on

using namespace std;
using u_int = unsigned int;
using ll = long long int;
using u_ll = unsigned long long int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void solve(void)
{
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> grid(N, vector<int> (M));
    auto in_range = [&](const int r, const int c)
    { return r > -1 && r < N && c > -1 && c < M; };

    int p = 1;
    for (int r = 0; r < N; ++r, cout << ENDL)
        for (int c = 0; c < M; ++c)
        {
            int adj_r = r - 1, adj_c = c;
            if (in_range(adj_r, adj_c) && grid[adj_r][adj_c] == p)
                p = (p % K) + 1;
            
            grid[r][c] = p;
            cout << grid[r][c] << ' ';
            p = (p % K) + 1;
        }
}

int main(void)
{
    FAST_IO;
#ifdef SUN_RAT_LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int TC;
    cin >> TC;

    while (TC-- > 0)
        solve();

    return 0;
}
```
