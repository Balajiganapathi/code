/* string coder = "Balajiganapathi S"; // Never give up!  */



#include<bits/stdc++.h>

using namespace std;

/* aliases */
using vi  = vector<int>;
using pi  = pair<int, int>;
using ll  = long long int;

/* shortcut macros */
#define mp              make_pair
#define fi              first
#define se              second
#define mt              make_tuple
#define gt(t, i)        get<i>(t)
#define all(x)          (x).begin(), (x).end()
#define ini(a, v)       memset(a, v, sizeof(a))
#define rep(i, s, n)    for(int i = (s), _##i = (n); i <= _##i; ++i)
#define re(i, s, n)     rep(i, (s), (n) - 1)
#define fo(i, n)        re(i, 0, n)
#define si(x)           (int((x).size()))
#define is1(mask,i)     (((mask) >> i) & 1)

    
#define x1 _asdfzx1
#define y1 _ysfdzy1

/* constants */
constexpr int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dy[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1;

class GameOfInterval {
public:
    string ans;

    string enc(int x) {
        if(x < 10) return string(1, x + '0');
        return string(1, 'A' + (x - 10));
    }

    string encode(int x) {
        int f = x / 36, s = x % 36;
        return enc(f) + enc(s);
    }

    set<pi> ints;
    string encode(int a, int b) {
        ints.emplace(a, b);
        return encode(a) + encode(b);
    }

    void solve(int n) {
        int b = sqrt(n);
        int nb = (n + b - 1) / b;
        //trace(b, nb);

        fo(bi, nb) {
            int s = b * bi, e = min(n, b * (bi+1));
            //trace(bi, s, e);
            re(i, s + 1, e) {
                ans += encode(s, i);
            }
            for(int i = e - 2; i >= s; --i) {
                ans += encode(i, e-1);
            }
        }

        fo(bi, nb) {
            int s = bi * b;
            re(bj, bi + 1, nb) {
                int e = min(n, b * (bj + 1));
                ans += encode(s, e-1);
            }
        }
    }

    void check(int n, string ans) {
        fo(i, n) ints.insert(mp(i, i));
        fo(i, n) re(j, i + 1, n) {
            int bi = i / b, bj = j / b;
        }
    }

	string construct( int n ) {
        solve(n);
        cerr << si(ans)/4 + 3 * n << endl;
        check(n, ans);
        return ans;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
