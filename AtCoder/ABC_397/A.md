# A - Thermometer

- Time Limit : 2sec
- Memory Limit : 1024MB

## Problem Statement

Takahashi measured his body temperature and found it to be $X^{\circ}C$.
Body temperature is classified into the following:

- Higher than or equal to 38.0 : "High fever”
- Higher than or equal to 37.5 and lower than 38.0 : “Fever”
- Lower than 37.5 : “Normal”

Which classification does Takahashi's body temperature fall into ?
Present the answer as an integer according to the Output section.

## Constraints

- 30 $\leq$ X $\leq$ 50
- X is given to one decimal place.
- Print an integer specified below corresponding to Takahashi's body temperature classification.
  - High fever : 1
  - Fever : 2
  - Normal : 3

## Solution

 입력으로 주어지는 X (double) 에 대해 주어진 조건에 따라, 상태에 맞는 정수를 출력하면 된다.

```cpp
#include <iostream>

using namespace std;

constexpr int HIGH_FEVER = 1;
constexpr int FEVER = 2;
constexpr int NORMAL = 3;

constexpr double HIGH_FEVER_LOW = 38.0;
constexpr double FEVER_LOW = 37.5;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double X;
    cin >> X;

    if (HIGH_FEVER_LOW <= X)
        cout << HIGH_FEVER;
    else if (FEVER_LOW <= X)
        cout << FEVER;
    else
        cout << NORMAL;

    return 0;
} ```
