# C. Maximum Subarray Sum

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

You are given an array $a_1,a_2,\ldots,a_n$ of length $n$ and a positive integer $k$, but some parts of the array $a$ are missing. Your task is to fill the missing part so that the maximum subarray sum -  of $a$ is exactly $k$, or report that no solution exists.

Formally, you are given a binary string $s$ and a partially filled array $a$, where:

- If you remember the value of $a_i$, $s_i = 1$ to indicate that, and you are given the real value of $a_i$.

- If you don't remember the value of $a_i$, $s_i = 0$ to indicate that, and you are given $a_i = 0$.

All the values that you remember satisfy $|a_i| \le 10^6$. However, you may use values up to $10^{18}$ to fill in the values that you do not remember. It can be proven that if a solution exists, a solution also exists satisfying $|a_i| \le 10^{18}$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two numbers $n,k$ ($1 \le n \le 2 \cdot 10^5,1 \le k \le 10^{12}$).
- The second line of each test case contains a binary ($\texttt{01}$) string $s$ of length $n$.
- The third line of each test case contains $n$ numbers $a_1,a_2,\ldots,a_n$ ($|a_i| \le 10^6$). If $s_i = \texttt{0}$, then it's guaranteed that $a_i = 0$.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## Output

- For each test case, first output $\texttt{Yes}$ if a solution exists or $\texttt{No}$ if no solution exists. You may print each character in either case, for example $\texttt{YES}$ and $\texttt{yEs}$ will also be accepted.
- If there's at least one solution, print $n$ numbers $a_1,a_2,\ldots,a_n$ on the second line. $|a_i| \le 10^{18}$ must hold.

## Solution

입력으로 주어진 배열 $A$ 에 $S_i = 0$ 인 경우의 요소를 수정하여 `maximum subarray sum` $= K$ 가 되도록 구성하면 된다.  

$S_i = 1$ 인 경우, 수정하지 못하는 고정된 요소이기 때문에 고정된 요소들만을 고려했을 시, `maximum subarray sum` $> K$ 인 경우, 이미 조건을 위반하기 때문에 solution 이 존재하지 않는다.  
또한, 입력 당시 `maximum subarray sum` $< K$ 이더라도, 수정할 수 있는 $S_i = 0$ 인 요소가 없다면, solution 이 존재할 수 없다.  

위의 두 경우를 배제한 상황을 고려해보자.  

### 입력 당시 `maximum subarray sum` $= K$ 인 경우

문제의 조건에서 $a_i \in [-10^{18}, 10^{18}]$ 이고, $K \in [1, 10^{12}]$ 이므로, 수정 가능한 요소의 값을 전부 $-10^{18}$ 로 채워도 `maximum subarray sum` $= K$ 를 만족 한다.  

### 입력 당시 `maximum subarray sum` $\leq 0$ 이고, $S_i = 0$ 인 요소가 하나 이상 존재하는 경우

`maximum subarray sum` 값이 0 이하 이므로, 반드시 모든 $S_i = 1$ 인 요소의 값은 $0$ 이하 이다.  
따라서 $S_i = 0$ 인 임의의 요소 하나만을 $K$ 값을 가진 상태라고 가정하면, 위의 경우에 속하게 되므로 나머지 $S_i = 0$ 요소에 $-10^{18}$ 로 채운다.

### 입력 당시 `maximum subarray sum` $\in (0, K)$ 이고, $S_i = 0$ 인 요소가 하나 이상 존재하는 경우

똑같이 임의의 $S_i = 0$ 인 요소 하나에 적절한 값을 추가하여, `maximum subarray sum` $= K$ 를 만족하게 한뒤,  
나머지 $S_i = 0$ 요소에 전부 $-10^{18}$ 로 채우면 만족할 수 있다.  

임의의 인덱스 $i$ 가 $S_i = 0$ 을 만족한다고 하자.  
$S_{i - 1} = 1$ 이고, $i - 1$ 을 끝으로 갖는 $Suffix$ 의 최대 합을 $sum$ 이라 하면, 오로지 $sum > 0$ 인 경우에 $A_i$ 에 넣을 값을 고려하여 감소해야 한다.  
$S_{i + 1} = 1$ 이고, $i + 1$ 을 시작으로 갖는 $Prefix$ 의 최대 합을 $sum$ 이라 하면, 위와 마찬가지로 $sum > 0$ 인 경우에 $A_i$ 에 넣을 값을 고려하여 감소해야 한다.

위의 두 경우 모두 고려하지 않아도 된다면, $A_i = K$ 로, 그외 공백은 $-10^{18}$ 로 채우면 문제의 조건을 만족하는 배열을 구성할 수 있다.  

```cpp
constexpr int N_MAX = 2e5;
constexpr int NIL = -1;
constexpr ll MIN = -1e18;

array<ll, N_MAX> A;
array<ll, N_MAX> Suffix;
string S;

pair<ll, int> check(const int N)
{
    ll mx = MIN;
    int fixed_cnt = 0;
    for (int i = 0; i < N; ++i)
        if (S[i] == '1')
        {
            ++fixed_cnt;
            if (i > 0 && S[i - 1] == '1' && Suffix[i - 1] > 0)
                Suffix[i] = Suffix[i - 1] + A[i];
            else
                Suffix[i] = A[i];
            mx = max(mx, Suffix[i]);
        }

    return make_pair(mx, fixed_cnt);
}

void solve(void)
{
    int N; ll K;
    cin >> N >> K >> S;

    for (int i = 0; i < N; ++i) cin >> A[i];

    auto [fixed_mx, fixed_cnt] = check(N);

    bool possible = (fixed_mx < K && fixed_cnt < N) || (fixed_mx == K);
    
    cout << (possible ? "Yes" : "No") << ENDL;

    if (possible)
    {
        if (fixed_mx == K)
        {
            for (int i = 0; i < N; ++i)
                if (S[i] == '0') A[i] = MIN;
        }
        else if (fixed_mx <= 0)
        {
            bool applied = false;
            for (int i = 0; i < N; ++i)
                if (S[i] == '0')
                {
                    if (!applied)
                    {
                        A[i] = K;
                        applied = true;
                    }
                    else A[i] = MIN;
                }
        }
        else
        {
            ll req = K;
            int pos = 0;
            while (S[pos] != '0') ++pos;

            if (0 < pos && S[pos - 1] == '1' && Suffix[pos - 1] > 0)
                req -= Suffix[pos - 1];
            if (pos < N - 1 && S[pos + 1] == '1')
            {
                ll mx_sum = 0;
                ll prefix = 0;
                for (int i = pos + 1; i < N; ++i)
                    if (S[i] == '1')
                    {
                        prefix += A[i];
                        mx_sum = max(mx_sum, prefix);
                    }
                    else break;
                
                req -= mx_sum;
            }

            A[pos] = req;
            S[pos] = '1';
            for (int i = 0; i < N; ++i) 
                if (S[i] == '0') A[i] = MIN;
        }

        for (int i = 0; i < N; ++i) cout << A[i] << ' ';
        cout << ENDL;
    }
}
```
