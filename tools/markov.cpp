#include <bits/stdc++.h>
using namespace std;
#define int long long

map<string, int> getResult(const string& s, const int len) {
    map<string, int> m;
    for (int i = 0; i < s.length() - len; i++) {
        string prev = "";
        for (int j = 0; j < len; j++) {
            prev += s[i + j];
        }
        m[prev] ++;
    }
    return m;
}

void enumerate(map<string, int>& m, const int len, const int s_len) {
    int p = 1;
    for (int i = 0; i < len; i++) {
        p *= 4;
    }
    double sum = 0.0;
    for (int i = 0; i < p; i++) {
        vector<int> a;
        int n = i;
        for (int j = 0; j < len; j++) {
            a.push_back( n % 4 );
            n /= 4;
        }
        string s = "";
        reverse(a.begin(), a.end());
        for (int j: a) {
            s.push_back('a' + j);
        }
        double c = (double)m[s] / (s_len - len);
        sum += c;
        cout << s << " " << (double)m[s] / p << endl;
    }
    cout << sum << endl;
}

signed main(signed argc, char* argv[]) {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string s;
    cin >> s;

    int len = 7;
    if (argc >= 2) {
        len = atoi(argv[1]);
    }
    auto m = getResult(s, len);
    enumerate(m, len, s.length());
    return 0;
}
