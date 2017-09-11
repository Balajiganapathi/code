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
constexpr auto eps = 1e-8L;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1;
using ld = long double;
ld mat[2][2] = {
    {0, 0},
    {0, 1}
};
ld ans[2][2];

void matmul(ld ans[2][2], ld mat1[2][2], ld mat2[2][2]) {
    ld tmp[2][2];
    fo(i, 2) fo(j, 2) {
        tmp[i][j] = 0;
        fo(k, 2) {
            tmp[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
    fo(i, 2) fo(j, 2) ans[i][j] = tmp[i][j];
}

void matpow(ld ans[2][2], ld mymat[2][2], int p) {
    ld cur[2][2];
    fo(i, 2) fo(j, 2) {
        ans[i][j] = (i==j? 1: 0);
        cur[i][j] = mymat[i][j];
    }

    for(; p; p /= 2) {
        if(p % 2 == 1) matmul(ans, ans, cur);
        matmul(cur, cur, cur);
    }
}

class ArmorUp {
public:

    bool ok(ld d, ld H, ld C, int k) {
        //trace(d, H, C, k, C);
        /*
        ld bc = C;
        fo(i, k) {
            //C = (H - 50 * d) * C / H + 49 * d;
            //C = C - (1 - (H-C) / (H+H)) * d;
            bc = bc * (1 - d / (2 * H)) - d / 2;
            //trace(i, C);
        }
        */

        mat[0][0] = 1 - d / (H+H);
        mat[0][1] = -d / 2;
        //trace(mat[0][0], mat[0][1]);
        matpow(ans, mat, k);
        //trace(ans[0][0], ans[0][1]);
        ld nc = ans[0][0] * C + ans[0][1];

        //trace(nc, bc);
        //trace(d, H, C, k, nc);
        return nc <= 0;
    }

	double minimalDamage( int H, int C, int k ) {
		double ret;

        ld lo = 0, hi = 2.0L * H;
        fo(iter, 10000) {
            double mid = (lo + hi) / 2;
            bool o = ok(mid, H, C, k);

            //trace(lo, hi, mid, o);

            if(o) hi = mid;
            else lo = mid;
        }
		
        ret = lo;
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
