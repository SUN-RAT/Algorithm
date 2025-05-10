# A. LRC and VIP

- Time limit : 1 second
- Memory limit : 256 megabytes

## Problem Statement

You have an array $a$ of size $n$ — $a_1, a_2, \ldots a_n$.

You need to divide the $n$ elements into $2$ sequences $B$ and $C$, satisfying the following conditions:

- Each element belongs to exactly one sequence.

- Both sequences $B$ and $C$ contain at least one element.

- $\gcd$ $(B_1, B_2, \ldots, B_{|B|}) \ne \gcd(C_1, C_2, \ldots, C_{|C|})$  

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 500$). The description of the test cases follows.
- The first line of each test case contains an integer $n$ ($2 \le n \le 100$).
- The second line of each test case contains $n$ integers $a_1,a_2,\ldots,a_n$ ($1 \le a_i \le 10^4$).

## Output

- For each test case, first output $\texttt{Yes}$ if a solution exists or $\texttt{No}$ if no solution exists. You may print each character in either case, for example $\texttt{YES}$ and $\texttt{yEs}$ will also be accepted.
- Only when there is a solution, output $n$ integers on the second line. The $i$-th number should be either $1$ or $2$. $1$ represents that the element belongs to sequence $B$ and $2$ represents that the element belongs to sequence $C$.
- You should guarantee that $1$ and $2$ both appear at least once.

## Solution

입력으로 주어진 배열을 $A$ 라 하자.  
$B \cup C = A$ 이고, $B \cap C = \emptyset$ , $B \neq \emptyset$ , $C \neq \emptyset$ 이다.  

$gcd(B) \neq gcd(C)$ 가 성립하게 할려면, $A$ 의 모든 요소 중, 최대값에 해당 하는 모든 요소를 한쪽에 몰아 넣고, 나머지 요소를 다른 집합에 몰아 넣으면 만족 한다.  

단, 나머지 요소를 넣은 집합이 $\emptyset$ 인 경우, 조건을 만족하지 못하므로, 불가능 하다.  

```cpp
constexpr int N_MAX = 100;

array<int, N_MAX> A;
array<char, N_MAX> Pos;

void solve(void)
{
    int N;
    cin >> N;

    int mx = 0;
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
        mx = max(mx, A[i]);
    }

    int mx_cnt = 0;
    for (int i = 0; i < N; ++i)
        if (A[i] == mx)
        {
            ++mx_cnt;
            Pos[i] = '2';
        }
        else Pos[i] = '1';

    if (mx_cnt < N)
    {
        cout << "Yes" << ENDL;
        for (int i = 0; i < N; ++i) cout << Pos[i] << ' ';
        cout << ENDL;
    }
    else cout << "No" << ENDL;
}
```
