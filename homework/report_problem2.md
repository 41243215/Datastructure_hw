# 41243215

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

本題使用遞迴列出集合的所有子集合。每個元素都分別嘗試「不選」與「選入」，所以有 $n$ 個元素時，總共會產生 $2^n$ 個子集合。測試空集合、1 個、2 個和 3 個元素時，輸出的子集合數量都符合預期。