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
#include<iostream>
using namespace std;

int ackermannRecursive(int m, int n){
    if(m == 0){
        return n+1;
    }
    else if(n == 0){
        return ackermannRecursive(m-1, 1);
    }
    else{
        return ackermannRecursive(m-1, ackermannRecursive(m, n-1));
    }
}

int ackermannIterative(int m,int n){
    const int maxSize = 10000;
    int pending[maxSize];
    int top = 0;

    pending[top++] = m;
    while(top>0){
        int currentM = pending[--top];

        if(currentM == 0) n++;
        else if(n==0){
            if(top >= maxSize) return -1;
            pending[top++] = currentM - 1;
            n = 1;
        }else{
            if(top + 2 > maxSize) return -1;
            pending[top++] = currentM - 1;
            pending[top++] = currentM;
            n--;
        }
    }
    return n;
}

int main(){
    cout << ackermannRecursive(1,1) << " :Recursive\n";
    cout << ackermannIterative(1,1) << " :Iterative";    
}
```

## 效能分析

1. 時間複雜度：兩種方法都需要依照 Ackermann 函數的規則反覆計算。當 m ≥ 2 且固定時，時間複雜度為 $\Theta(A(m,n)^2)$。
2. 空間複雜度：遞迴版會使用函式呼叫堆疊，當 m ≥ 1 且固定時，空間複雜度為 $\Theta(A(m,n))$。非遞迴版使用固定長度為 10000 的陣列，因此陣列占用的空間是固定的。

* $A(m,n)$ 表示 Ackermann 函數的回傳值。

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
$ g++ -std=c++17 hw1_problem1.cpp -o hw1_problem1.exe
$ .\hw1_problem1.exe
3 :Recursive
3 :Iterative
```

執行結果：

```text
3 :Recursive
3 :Iterative
```

### 結論

我先依照 Ackermann 函數的三條規則寫出遞迴版，因為遞迴的寫法能直接對應題目中的定義，方便檢查每一種情況。
非遞迴版需要記住尚未完成的計算。我使用陣列 `pending` 保存待處理的 `m`，並用 `top` 控制放入和取出的順序。這樣可以先處理後放入的數字，模擬原本的遞迴過程。由於陣列容量固定為 10000，我也加入容量檢查，避免超出陣列範圍。
測試時，我比較兩個版本在相同輸入下的結果，確認非遞迴版的處理順序正確。


##



作業一 Problem 2

## 解題說明

本題要求列出集合的所有子集合，也就是冪集合。程式會對集合中的每個元素做兩種選擇：不選或選入。當所有元素都處理完，就印出目前選到的子集合。

本題使用 `string S = "ab"` 作為範例，結果共有 $2^2 = 4$ 個子集合。

### 解題策略

宣告 `powerSet` 函式，使用三個參數：

1. `S`：原本的集合。
2. `index`：目前處理到第幾個元素。
3. `current`：目前已選入的元素。

每次呼叫函式時，先處理「不選 `S[index]`」，再處理「選 `S[index]`」。如果 `index` 已經等於 `S.size()`，表示所有元素都處理完，就印出 `current`。

`current` 以值傳遞，因此選入元素時可以直接使用 `current + S[index]` 產生新的字串，不需要在函式返回後移除元素。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <string>
using namespace std;

void powerSet(const string S, size_t index, string current) {
    if (index == S.size()){                    // 停止條件：所有元素都處理完了
        cout << "{";
        for(size_t i = 0;i < current.size();i++){
            if(i>0) cout << ",";
            cout << current[i];
        }
        cout << "}" << '\n';
        return;
    }
    powerSet(S, index + 1, current);
    powerSet(S, index + 1, current + S[index]);

}

int main() {
    string S = "ab";
    string current;
    powerSet(S, 0, current);
}
```

## 效能分析

設集合有 $n$ 個元素。

1. **時間複雜度**：每個元素都有「選」和「不選」兩種情況，因此共有 $2^n$ 個子集合。印出一個子集合最多需要處理 $n$ 個字元，時間複雜度為 $O(n2^n)$。
2. **空間複雜度**：遞迴最深會有 $n$ 層。目前的程式在呼叫函式時會複製 `S` 和 `current`，因此額外空間最多為 $O(n^2)$。

## 測試與驗證

### 測試案例

測試時修改 `main` 中 `S` 的內容，檢查輸出的子集合數量及順序：

| 測試案例 | 輸入集合 `S` | 預期子集合數 | 實際子集合數 |
| ---- | ---- | ---: | ---: |
| 測試一 | `""` | 1 | 1 |
| 測試二 | `"a"` | 2 | 2 |
| 測試三 | `"ab"` | 4 | 4 |
| 測試四 | `"abc"` | 8 | 8 |

### 編譯與執行指令

```powershell
g++ -std=c++17 -o hw1_problem2.exe hw1_problem2.cpp
.\hw1_problem2.exe
```

當 `S = "ab"` 時，執行結果為：

```text
{}
{b}
{a}
{a,b}
```

### 結論

冪集合需要考慮每個元素「選」與「不選」兩種情況，因此使用遞迴處理。每處理一個元素，就分別呼叫函式處理這兩種選擇；當所有元素都處理完，再印出目前的子集合。
我使用 `string` 保存原集合和目前選到的字元。`current` 以值傳遞，選入元素時可以把新字元接在字串後面，原本的 `current` 不會改變，所以不需要另外寫還原步驟。這種寫法較容易看出每次遞迴分成兩條路，但呼叫函式時會複製字串，是目前程式在空間使用上的限制。
