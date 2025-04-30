# B. Binary Typewriter

- Time limit : 1.5 seconds
- Memory limit : 256 megabytes

## Problem Statement

You are given a binary string $s$ of length $n$ and a typewriter with two buttons: 0 and 1 . Initially, your finger is on the button 0 . You can do the following two operations:

- Press the button your finger is currently on. This will type out the character that is on the button.

- Move your finger to the other button. If your finger is on button 0 , move it to button 1 , and vice versa.

The cost of a binary string is defined as the minimum number of operations needed to type the entire string.

Before typing, you may reverse at most one substring-  of $s$. More formally, you can choose two indices $1\le l\le r\le n$, and reverse the substring $s_{l\ldots r}$, resulting in the new string $s_1s_2\ldots s_{l-1}s_rs_{r-1}\ldots s_ls_{r+1}\ldots s_n$.

Your task is to find the minimum possible cost among all strings obtainable by performing at most one substring reversal on $s$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains a single integer $n$ ($1\le n\le 2\cdot 10^5$) — the length of the binary string $s$.
- The second line of each test case contains a binary string $s_1s_2\ldots s_n$ ($s_i = \mathtt{0}$ or $s_i = \mathtt{1}$) — the characters of the binary string $s$.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## Output

- For each test case, output the minimum cost of string $s$ after performing at most one substring reversal.

## Solution

문제에서 제시한 두 가지의 `Operation` 과 `Cost` 간의 관계를 살펴보자.  

손가락이 놓여진 button 의 글자를 $pointer$ , 현재 작성할려는 문자가 $S[i]$ 라 하자.  

$$
\begin{aligned}
\text{if pointer == S[i] } \rightarrow \Delta Cost = 1 \\
\text{if pointer != S[i] } \rightarrow \Delta Cost = 2 \\
\end{aligned}
$$

위의 관계가 있음을 알 수 있다.  

$pointer != S[i]$ 인 지점을 $reverse$ 동작을 이용하면 최대 $2$ 까지 비용을 줄일 수 있다.  

초기의 $pointer = 0$ 이므로, 처음으로 $1$ 이 등장 한 인덱스를 $l$  
이후, 두 번째로 $1$ 이 등장 한 인덱스를 $r + 1$ 로 지정한  
구간 $[l, r]$ 을 $reverse$ 한 $S_{prod}$ 에서의 $Cost_{prod}$ 가 가능한 최소 비용이다.  

이는 $O(N)$ 선형 복잡도로 작동하기에, 문제의 시간조건 이내에 풀이가 가능하다.

```cpp
void solve(void)
{
    int N;
    cin >> N;

    string s;
    cin >> s;

    bool first = true;
    bool searching = true;
    int l = 0, r = N;
    for (int i = 0; i < N; ++i)
    {
        if (searching && s[i] == '1')
        {
            if (first)
            {
                l = i;
                first = false;
                searching = false;
            }
            else
            {
                r = i;
                break;
            }
        }
        if (!searching && s[i] == '0')
            searching = true;
    }

    string prod_s;
    prod_s.append(s.begin(), s.begin() + l);
    string mid;
    mid.append(s.begin() + l, s.begin() + r);
    reverse(mid.begin(), mid.end());
    prod_s.append(mid);
    prod_s.append(s.begin() + r, s.end());

    int ans = 0;
    char ptr = '0';
    for (int i = 0; i < N; ++i)
        if (prod_s[i] == ptr)
            ans++;
        else
        {
            ans += 2;
            ptr = (ptr == '0') ? '1' : '0';
        }
    
    cout << ans << ENDL;
}
```
