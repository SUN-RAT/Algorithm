# G. Chimpanzini Bananini

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Chimpanzini Bananini stands on the brink of a momentous battle—one destined to bring finality.

For an arbitrary array $b$ of length $m$, let's denote the rizziness of the array to be $\sum_{i=1}^mb_i\cdot i=b_1\cdot 1+b_2\cdot 2+b_3\cdot 3+\ldots + b_m\cdot m$.

Chimpanzini Bananini gifts you an empty array. There are three types of operations you can perform on it.

1. Perform a cyclic shift on the array. That is, the array $[a_1, a_2, \ldots, a_n]$ becomes $[a_n, a_1, a_2, \ldots, a_{n-1}].$

2. Reverse the entire array. That is, the array $[a_1, a_2, \ldots, a_n]$ becomes $[a_n, a_{n-1}, \ldots, a_1].$

3. Append an element to the end of the array. The array $[a_1, a_2, \ldots, a_n]$ becomes $[a_1, a_2, \ldots, a_n, k]$ after appending $k$ to the end of the array.

After each operation, you are interested in calculating the rizziness of your array.

Note that all operations are persistent . This means that each operation modifies the array, and subsequent operations should be applied to the current state of the array after the previous operations.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
- The first line of the input contains an integer $q$ ($1 \leq q \leq 2\cdot 10^5$) — the number of operations you perform on your array.
- The following $q$ lines first contain a single integer $s$ ($1 \leq s \leq 3$) — the operation type.
- It is guaranteed that the sum of $q$ will not exceed $2\cdot 10^5$ over all test cases. Additionally, it is guaranteed that the first operation on each test case will be one with $s=3$.

## Output

- For each test case, output $q$ lines, outputting the rizziness of your array after each operation.

## Upsolving

`F` 문제에서 남은 시간을 다 쏟아버려 펼치지도 않았는데, `F` 보다도 더 쉬운 문제였다.  

문제에서 주어진 3개의 연산을 관찰하자.  
연산 수행 하기 전의 $rizziness$ 를 $Rizzi_{before}$, 수행 한 후의 $rizziness$ 를 $Rizzi_{after}$ 라 하자.  

### 1. Perform a cyclic shift on the array. That is, the array $[a_1, a_2, \ldots, a_n]$ becomes $[a_n, a_1, a_2, \ldots, a_{n-1}]$

단순히 마지막 요소를 `cyclic shift` 한다.  
$$
\begin{align}
Rizzi_{before} &= b_1\cdot 1+b_2\cdot 2+b_3\cdot 3+\ldots + b_m\cdot m \\
Rizzi_{after} &= b_1\cdot 2+b_2\cdot 3+b_3\cdot 4+\ldots + b_m\cdot 1 \\
Rizzi_{after} - Rizzi_{before} &= -b_m \cdot (m - 1) + \sum\limits_{i = 1}^{i = m - 1}b_i \\
\therefore Rizzi_{after} &= Rizzi_{before} - b_m \cdot m + \sum\limits_{i = 1}^{i = m}b_i
\end{align}
$$

### 2. Reverse the entire array. That is, the array $[a_1, a_2, \ldots, a_n]$ becomes $[a_n, a_{n-1}, \ldots, a_1]$

모든 요소의 위치를 반전시킨다.
$$
\begin{align}
Rizzi_{before} &= b_1\cdot 1+b_2\cdot 2+b_3\cdot 3+\ldots + b_m\cdot m \\
Rizzi_{after} &= b_m\cdot 1+b_{m - 1}\cdot 2+b_{m - 2}\cdot 3+\ldots + b_2\cdot (m-1) + b_1\cdot m \\
Rizzi_{before} + Rizzi_{after} &= b_1\cdot(m+1)+b_2\cdot(m+1)+b_3\cdot(m+1)+\ldots + b_m\cdot(m+1) \\
Rizzi_{before} + Rizzi_{after} &= (m+1)\cdot \sum\limits_{i = 1}^{i = m}b_i \\
\therefore Rizzi_{after} &= -Rizzi_{before} + (m+1)\cdot \sum\limits_{i = 1}^{i = m}b_i \\
\end{align}
$$

### 3. Append an element to the end of the array. The array $[a_1, a_2, \ldots, a_n]$ becomes $[a_1, a_2, \ldots, a_n, k]$ after appending $k$ to the end of the array

가장 마지막 요소 다음으로 $K$ 를 추가한다.
$$
\begin{align}
Rizzi_{before} &= b_1\cdot 1+b_2\cdot 2+b_3\cdot 3+\ldots + b_m\cdot m \\
Rizzi_{after} &= b_1\cdot 1+b_2\cdot 2+b_3\cdot 3+\ldots + b_m\cdot m + K \cdot (m + 1)\\
\therefore Rizzi_{after} &= Rizzi_{before} + K \cdot (m + 1)\\
\end{align}
$$

위의 3가지 연산에 대해 $Rizzi$ 는 $Sum(B)$ 를 안다면, $O(1)$ 으로 계산할 수 있다.  
다만, 반전연산으로 인해, 마지막에 추가하는 위치, 첫 번째 요소의 위치를 계속 추적해야 한다.

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

constexpr int Q_MAX = 2e5;
constexpr int CYCLIC_SHIFT = 1;
constexpr int REVERSE = 2;
constexpr int APPEND = 3;

void solve(void)
{
    int Q, s, data;
    cin >> Q;

    deque<int> deq;
    ll rizzi = 0, sum = 0;
    bool reversed = false;
    while (Q-- > 0)
    {
        cin >> s;
        switch (s)
        {
        case CYCLIC_SHIFT:
            if (!deq.empty())
                if (reversed)
                    deq.push_back(deq.front()), deq.pop_front();
                else
                    deq.push_front(deq.back()), deq.pop_back();

            rizzi = rizzi + sum - 1LL * deq.size() * (deq.empty() ? 0 : (reversed ? deq.back() : deq.front()));
            break;
        case REVERSE:
            rizzi = (deq.size() + 1) * sum - rizzi;
            reversed = !reversed;
            break;
        case APPEND:
            cin >> data;
            if (reversed)
                deq.push_front(data);
            else
                deq.push_back(data);
            rizzi += 1LL * deq.size() * data;
            sum += 1LL * data;
            break;
        }
        cout << rizzi << ENDL;
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

`switch`문 대신, `function 배열` 을 사용해본 코드

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

constexpr int Q_MAX = 2e5;
constexpr int CYCLIC_SHIFT = 1;
constexpr int REVERSE = 2;
constexpr int APPEND = 3;

function<void(deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)> Operation[4];
static bool init_Operation = []()
{
    Operation[CYCLIC_SHIFT] = [](deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)
    {
        if (!deq.empty())
                if (reversed)
                    deq.push_back(deq.front()), deq.pop_front();
                else
                    deq.push_front(deq.back()), deq.pop_back();
        rizzi = rizzi + sum - 1LL * deq.size() * (deq.empty() ? 0 : (reversed ? deq.back() : deq.front()));
    };
    Operation[REVERSE] = [](deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)
    {
        rizzi = (deq.size() + 1) * sum - rizzi;
        reversed = !reversed;
    };
    Operation[APPEND] = [](deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)
    {
        int data;
        cin >> data;
        if (reversed)
            deq.push_front(data);
        else
            deq.push_back(data);
        rizzi += 1LL * deq.size() * data;
        sum += 1LL * data;
    };
    return true;
}();


void solve(void)
{
    int Q, s, data;
    cin >> Q;

    deque<int> deq;
    ll rizzi = 0, sum = 0;
    bool reversed = false;
    while (Q-- > 0)
    {
        cin >> s;
        Operation[s](deq, rizzi, sum, reversed);
        cout << rizzi << ENDL;
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

`function 배열` 대신 `함수 포인터 배열` 사용해본 코드

- `function 배열` 보다 `함수 포인터 배열` 이 더 오버헤드가 적다.
  - **타입 제거(Type Erasure) 부재** , **동적 할당 가능성**
  - **가상 호출(Virtual Dispatch) vs. 직접 호출(Direct Call)**
    - `function::operator()` 는 가상 호출의 형태로, 내부적으로 간접 호출과 가상 테이블 참조로 비용이 더 크다.

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

constexpr int Q_MAX = 2e5;
constexpr int CYCLIC_SHIFT = 1;
constexpr int REVERSE = 2;
constexpr int APPEND = 3;

void cyclic_shift(deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)
{
    if (!deq.empty())
    if (reversed)
        deq.push_back(deq.front()), deq.pop_front();
    else
        deq.push_front(deq.back()), deq.pop_back();
    rizzi = rizzi + sum - 1LL * deq.size() * (deq.empty() ? 0 : (reversed ? deq.back() : deq.front()));
}
void reverse(deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)
{
    rizzi = (deq.size() + 1) * sum - rizzi;
    reversed = !reversed;
}
void append(deque<int> &deq, ll &rizzi, ll &sum, bool &reversed)
{
    int data;
    cin >> data;
    if (reversed)
        deq.push_front(data);
    else
        deq.push_back(data);
    rizzi += 1LL * deq.size() * data;
    sum += 1LL * data;
}

void(*Operation[4])(deque<int>&, ll&, ll&, bool&) = {nullptr, cyclic_shift, reverse, append};

void solve(void)
{
    int Q, s, data;
    cin >> Q;

    deque<int> deq;
    ll rizzi = 0, sum = 0;
    bool reversed = false;
    while (Q-- > 0)
    {
        cin >> s;
        Operation[s](deq, rizzi, sum, reversed);
        cout << rizzi << ENDL;
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
