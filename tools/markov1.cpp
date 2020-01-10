#include <bits/stdc++.h>
using namespace std;
#define int long long

/**
 * このコードは実行に使用するマルコフ則データを生成するプログラムです.
 */

/**
 * 出力ファイルフォーマット
 * 
 * 4         // 一つあたりのパターンの長さ
 * 60         // 以降に続くパターン対応の数
 * aaax aaaa // 左のパターンが現れたら右のパターンに変換する.
 * aabx aabd
 * ~~~
 * xxax abac
 * 
 */

// 答えの文字列を解析して, どのようなパターンがどのくらい現れているかを調べて, 文字列パターンとそのパターンが出た数の辞書を返す.
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

// xを入れないすべてのパターン (4 ^ len)個の文字列をタダ列挙する.
vector<string> enumerate(const int len) {
    vector<string> v;
    int p = 1;
    for (int i = 0; i < len; i++) {
        p *= 4;
    }
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
        v.push_back(s);
    }
    return v;
}

// xを考慮したすべてのパターンの文字列を列挙する.setは集合型
set<string> enumerate_including_x(int len) {
    set<string> set;
    for (int bit = 1; bit < (1 << len); bit++) {
        int p = 1;
        for (int i = 0; i < len; i++) {
            p *= 4;
        }
        for (int i = 0; i < p; i++) {
            vector<int> a;
            int n = i;
            for (int j = 0; j < len; j++) {
                if ((bit >> j) & 1) {
                    a.push_back('x' - 'a');
                } else {
                    a.push_back( n % 4 );
                }
                n /= 4;
            }
            string s = "";
            reverse(a.begin(), a.end());
            for (int j: a) {
                s.push_back('a' + j);
            }
            set.insert(s);
        }
    }
    return set;
}

// 与えられた文字列s(xを含む)に対して, xを適当なabcdで埋めて最も確率の高いパターンを返す.
string dfs(string& s, map<string, int>& m, int len, int i) {
    if (i >= len) {
        return s;
    }
    if (s[i] == 'x') {
        int max = 0;
        string ret = "";
        for (int j = 0; j < 4; j++) {
            s[i] = 'a' + j;
            string t = dfs(s, m, len, i + 1);
            int p = m[t];
            if (p > max) {
                max = p;
                ret = t;
            }
        }
        s[i] = 'x';
        return ret;
    }
    return dfs(s, m, len, i + 1);
}

// 結局a埋めになりがちなので, a埋め以外の特徴がある者だけを出力する.
bool filled_with_a_all(const string& s, const string& t, int len) {
    bool fill_all_a = true;
    for (int i = 0; i < len; i++) {
        if (s[i] == 'x' && t[i] != 'a')  {
            fill_all_a = false;
        }
    }
    return fill_all_a;
}

signed main(signed argc, char* argv[]) {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string t;
    cin >> t;
    reverse(t.begin(), t.end());

    int len = 2;
    if (argc >= 2) {
        len = atoi(argv[1]);
    }
    bool exclude_filled_a_all = (argc >= 3 && string(argv[2]) == "1");
    cout << len << endl;
    auto m = getResult(t, len);
    for (auto& s: enumerate(len)) {
        cout << s << " " << (double)m[s] / (t.length() - len)  << endl;
    }
    
    return 0;
}
