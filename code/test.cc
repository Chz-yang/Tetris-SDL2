#include <iostream>
#include <vector>
using namespace std;

void output(const vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    vector <int> a;
    for (int i = 0; i < 5; i++) {
        a.push_back(i);
    }

    for (int i = 0; i < 5; i++) {
        int x = a.back();
        a.pop_back();
        cout << x << endl;
        a.insert(a.begin(), (10 - i));
        output(a);
    }
}