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
constexpr int mx_b = 6;
constexpr int mx_sum = (1 << mx_b) + 10;
constexpr int mx_full = (1 << mx_b) - 1;
constexpr int mx_n = 15;
int dp[mx_sum][(1 << mx_n) + 10];


class Xscoregame {
public:
    vi a;
    int n;

    int solve(int sum, int mask) {
        int rem = n - __builtin_popcount(mask);
        if(rem == 0) return sum;
        int &ret = dp[sum][mask];
        if(ret != -1) return ret;
        ret = 0;
        fo(i, n) if(!is1(mask, i)) {
            int nxt_sum = (sum + (sum ^ a[i]));
            int tmp = solve((nxt_sum & mx_full), (mask | (1 << i)));
            int higher = ((nxt_sum >> mx_b) << mx_b);
            //trace(i, sum, mask, nxt_sum, tmp, higher);
            ret = max(ret, (higher << (rem-1)) + tmp);
        }
        //trace(sum, mask, ret);

        return ret;
    }

	int getscore( vector <int> A ) {
        ini(dp, -1);
        a = A;
        n = si(a);

        return solve(0, 0);
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
