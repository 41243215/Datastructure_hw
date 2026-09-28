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
