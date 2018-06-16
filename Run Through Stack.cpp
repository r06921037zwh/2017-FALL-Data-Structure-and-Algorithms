#include<iostream>
#include<stack>
using namespace std;
void print(stack<int> a){ //reverse output
    stack<int> b;
    while (!a.empty()){
        b.push(a.top());
        a.pop();
    }
    while (!b.empty()){
        cout << b.top() << " ";
        b.pop();
    }
    cout << '\n';
}
 
void arrange(int n, stack<int> in, stack<int> transfer, stack<int> out){
    if (in.empty() && transfer.empty()){
        print(out);
    }
 
    if (!in.empty()){
        int temp = in.top();
        transfer.push(temp); //pop from in and push into transfer
        in.pop();
        arrange(n, in, transfer, out); // recursive call
        transfer.pop(); //pop from transfer
        in.push(temp);
    }
 
    if (!transfer.empty()){
        out.push(transfer.top()); //pop from transfer and push into out
        transfer.pop();
        arrange(n, in, transfer, out); //recursive call
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    stack<int> in, transfer, out;
    int n;
    cin >> n;
    for (int i = 0; i<n; i++) //初始序列
        in.push(n - i);
    arrange(n, in, transfer, out);
    system("pause");
    return 0;
}