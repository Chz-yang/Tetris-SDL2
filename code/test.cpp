#include <iostream>
#include <map>
using std::map;
using namespace std;

void f(map<char, int (*)[4][2]> &d) {
    int S[][4][2] = {
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
    };
    d.insert(make_pair('S', S));
}

int main(int argc, char const* argv[]) {
    map<char, int (*)[4][2]> d;
    f(d);
    cout << d['S'][0][2][0] << endl;
    return 0;
}
