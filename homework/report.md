# 41243215

作業一 Problem 1

## 解題說明

本題要求實作 Ackermann 函數
寫兩種計算同一個函數的方法：
1. 遞迴函式：按照圖片中的三條規則：m = 0 時回傳 n + 1；n = 0 時算 A(m−1, 1)；其他情況算 A(m−1, A(m, n−1))。
2. 非遞迴演算法：不讓函式自己呼叫自己，使用陣列保存還沒處理的數字，模擬遞迴的計算順序。

### 解題策略

宣告一個接收兩個整數、回傳整數的函式：int ackermann(int m, int n)。接著使用if/else判斷下列三個情況：
1. m == 0：回傳 n + 1，為停止遞迴的條件。是停止遞迴的條件之一。
2. n == 0：呼叫 ackermann，但傳入的參數會改變。
3. 其他情況：呼叫兩層。先算 ackermann(m, n - 1)，再把它的結果當成另一個 ackermann 的參數

非遞迴版 ackermannIterative(int m, int n)。用 pending 陣列存放還沒處理的 m，用 top 記錄陣列中目前有幾個數字。每次從最後放入的位置取出一個數字，再依照 Ackermann 函數的規則處理，直到 pending 中沒有數字為止。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

int ackermannRecursive(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    }
    return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
}

int ackermannIterative(int m, int n) {
    const int maxSize = 10000;
    int pending[maxSize];
    int top = 0;

    pending[top++] = m;

    while (top > 0) {
        int currentM = pending[--top];

        if (currentM == 0) {
            n++;
        } else if (n == 0) {
            if (top >= maxSize) return -1;
            pending[top++] = currentM - 1;
            n = 1;
        } else {
            if (top + 2 > maxSize) return -1;
            pending[top++] = currentM - 1;
            pending[top++] = currentM;
            n--;
        }
    }

    return n;
}

int main() {
    cout << ackermannRecursive(1, 1) << " :Recursive\n";
    cout << ackermannIterative(1, 1) << " :Iterative\n";
}
```

## 效能分析

1. 時間複雜度：兩種方法都需要依照 Ackermann 函數的規則反覆計算。當 m ≥ 2 且固定時，時間複雜度為 $\Theta(A(m,n)^2)$。
2. 空間複雜度：遞迴版會使用函式呼叫堆疊，當 m ≥ 1 且固定時，空間複雜度為 $\Theta(A(m,n))$。非遞迴版使用固定長度為 10000 的陣列，因此陣列占用的空間是固定的。

*$A(m,n)$ 表示 Ackermann 函數的回傳值。

## 測試與驗證

| 測試案例 | 輸入參數 $(m,n)$ | 預期輸出 | 遞迴實際輸出 | 非遞迴實際輸出 |
| --- | --- | ---: | ---: | ---: |
| 測試一 | $(0,0)$ | 1 | 1 | 1 |
| 測試二 | $(0,3)$ | 4 | 4 | 4 |
| 測試三 | $(1,1)$ | 3 | 3 | 3 |
| 測試四 | $(2,2)$ | 7 | 7 | 7 |
| 測試五 | $(3,1)$ | 13 | 13 | 13 |

### 編譯與執行指令

```powershell
g++ -std=c++17 -o hw1_problem1.exe hw1_problem1.cpp
.\hw1_problem1.exe
```

執行結果：

```text
3 :Recursive
3 :Iterative
```

### 結論

本題以遞迴和陣列模擬兩種方式實作 Ackermann 函數。五組非負整數測試中，兩個版本的結果一致且符合預期。
由於函數計算量成長很快，測試以小數值為主。非遞迴版另外設定了陣列容量上限，避免寫入超出陣列範圍的位置。
