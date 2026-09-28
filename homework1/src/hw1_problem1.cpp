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
