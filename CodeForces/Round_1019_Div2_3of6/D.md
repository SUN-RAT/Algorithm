# D. Local Construction

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

An element $b_i$ ($1\le i\le m$) in an array $b_1, b_2, \ldots, b_m$ is a local minimum if at least one of the following holds:

- $2\le i\le m - 1$ and $b_i < b_{i - 1}$ and $b_i < b_{i + 1}$, or

- $i = 1$ and $b_1 < b_2$, or

- $i = m$ and $b_m < b_{m - 1}$.

Similarly, an element $b_i$ ($1\le i\le m$) in an array $b_1, b_2, \ldots, b_m$ is a local maximum if at least one of the following holds:

- $2\le i\le m - 1$ and $b_i > b_{i - 1}$ and $b_i > b_{i + 1}$, or

- $i = 1$ and $b_1 > b_2$, or

- $i = m$ and $b_m > b_{m - 1}$.

Note that local minima and maxima are not defined for arrays with only one element.

There is a hidden permutation-  $p$ of length $n$. The following two operations are applied to permutation $p$ alternately, starting from operation 1, until there is only one element left in $p$:

- Operation 1 — remove all elements of $p$ which are not local minima.

- Operation 2 — remove all elements of $p$ which are not local maxima.

More specifically, operation 1 is applied during every odd iteration, and operation 2 is applied during every even iteration, until there is only one element left in $p$.

For each index $i$ ($1\le i\le n$), let $a_i$ be the iteration number that element $p_i$ is removed, or $-1$ if it was never removed.

It can be proven that there will be only one element left in $p$ after at most $\lceil \log_2 n\rceil$ iterations (in other words, $a_i \le \lceil \log_2 n\rceil$).

You are given the array $a_1, a_2, \ldots, a_n$. Your task is to construct any permutation $p$ of $n$ elements that satisfies array $a$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains a single integer $n$ ($2 \le n \le 2 \cdot 10^5$) — the number of elements in permutation $p$.
- The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le \lceil\log_2 n\rceil$ or $a_i = -1$) — the iteration number that element $p_i$ is removed.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
- It is guaranteed that there exists at least one permutation $p$ that satisfies array $a$.

## Output

- For each test case, output $n$ integers representing the elements of the permutation satisfying array $a$.
- If there are multiple solutions, you may output any of them.

## Upsolving

2가지 연산에 대해 살펴보자.  
요소가 제거된 $Stamp$ 값이 홀수 인 경우 $1$ 번 연산에 의해, 짝수 인 경우 $2$ 번 연산에 의해 제거 된다.  
연산의 명칭을 $Stamp$ 값의 `parity` 에 따라 아래와 같이 재정의 할 수 있다.  

- `Odd-OP` : $\text{local min}$ 이 아닌 요소를 전부 제거
- `Even-OP` : $\text{local max}$ 가 아닌 요소를 전부 제거

임의의 연산 순번에서, 제거된 요소의 개수를 $Cnt_{i}$ 라 하고, 제거 직전 요소의 개수가 $N_{i}$ 라 할때,  

- `Odd-OP` 인 경우 : 상위 $Cnt_{i}$ 개의 요소가 제거
- `Even-OP` 인 경우 : 하위 $Cnt_{i}$ 개의 요소가 제거

위와 같이 분류해도 잔여 요소들은 전부 $\text{local min / max}$ 를 만족 한다.  

그렇다면, 이제 어떻게 $Cnt_{i}$ 개의 요소를 추가할 것인지 고려해보자.  
문제에서 정의된 $\text{local min / max}$ 의 정의를 보면 3가지 Case 로 분류되어 있다.  
($\text{1 - based index}$ 에서 $\text{0 - based index}$ 로 변경)

- $0 < i < N - 1$ 인 경우
  - $\text{local min}$ : $P_{i - 1} > P_{i} < P_{i + 1}$
  - $\text{local max}$ : $P_{i - 1} < P_{i} > P_{i + 1}$
- $i = 0$ 인 경우
  - $\text{local min}$ : $P_{0} < P_{1}$
    - `Odd-OP` : $Cnt$ 개의 요소를 채울 때, 왼쪽 edge 에 해당되는 구간은 오름차순으로 채울 시, 연산 순서를 위반한다.
      - 따라서, `Odd-OP` 복구 과정에서, 왼쪽 edge 구간은 내림차순으로 복구 한다.
  - $\text{local max}$ : $P_{0} > P_{1}$
    - `Even-OP` : $Cnt$ 개의 요소를 채울 때, 왼쪽 edge 에 해당되는 구간은 내림차순으로 채울 시, 연산 순서를 위반한다.
      - 따라서, `Even-OP` 복구 과정에서, 왼쪽 edge 구간은 오름차순으로 복구 한다.
- $i = N - 1$ 인 경우
  - $\text{local min}$ : $P_{N - 2} > P_{N - 1}$
    - `Odd-OP` : $Cnt$ 개의 요소를 채울 때, 오른쪽 edge 에 해당되는 구간은 내림차순으로 채울 시, 연산 순서를 위반한다.
      - 따라서, `Odd-OP` 복구 과정에서, 오른쪽 edge 구간은 오름차순으로 복구 한다.
  - $\text{local max}$ : $P_{N - 2} < P_{N - 1}$
    - `Even-OP` : $Cnt$ 개의 요소를 채울 때, 왼쪽 edge 에 해당되는 구간은 오름차순으로 채울 시, 연산 순서를 위반한다.
      - 따라서, `Even-OP` 복구 과정에서, 오른쪽 edge 구간은 내림차순으로 복구 한다.

위의 관찰을 토대로 복구하면 연산 $Stamp$ 를 만족하는 순열 $P$ 를 얻을 수 있다.  
$N$ 개의 인덱스에 대해서 한번의 순회로 삽입 위치 조정과 한번의 순회로 복구가 이루어지므로, $O(N)$ 의 선형 복잡도로 복구할 수 있다.  

```cpp
constexpr int N_MAX = 2e5;
constexpr int LOG_MAX = 18;
constexpr int LAST = -1;

int Stamp[N_MAX];
int P[N_MAX];
vector<int> Index[LOG_MAX + 1];

void solve(void)
{
    int N;
    cin >> N;

    fill(begin(Index), end(Index), vector<int> {});
    int last_index;
    for (int i = 0; i < N; ++i)
    {
        cin >> Stamp[i];
        if (Stamp[i] != LAST)
            Index[Stamp[i]].push_back(i);
        else
            last_index = i;
    }
    
    int s = 1, e = N;
    for (int i = 1; i <= LOG_MAX && !Index[i].empty(); ++i)
    {
        int l, r;
        if (i & 1)
        {
            l = e - Index[i].size() + 1;
            r = e;
            e = l - 1;

            for (const int id : Index[i])
                P[id] = (id < last_index) ? r-- : l++;
        }
        else
        {
            l = s;
            r = s + Index[i].size() - 1;
            s = r + 1;

            for (const int id : Index[i])
                P[id] = (id < last_index) ? l++ : r--;
        }
    }
    P[last_index] = s;

    for (int i = 0; i < N; ++i)
        cout << P[i] << ' ';
    cout << ENDL;
}
```
