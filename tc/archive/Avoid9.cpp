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

class Avoid9 {
public:
    int cnt[10];
    int calc(int mask) {
        int ccnt[10];
        fo(i, 10) ccnt[i] = cnt[i];
        fo(i, 9) if(!is1(mask, i)) ccnt[i] = 0;
        //fo(i, 9) if(is1(mask, i) && ccnt[i] == 0) return -1;

        fo(i, 9) if(is1(mask, i)) {
            if((3 * i) % 9 == 0) {
                ccnt[i] = min(ccnt[i], 2);
            }
            fo(j, 9) if(is1(mask, j)) {
                if(i != j && (2 * i + j) % 9 == 0) {
                    ccnt[i] = min(ccnt[i], 1);
                }
                fo(k, 9) if(is1(mask, k)) {
                    if(i != j && i != k && j != k && (i+j+k) % 9 == 0) {
                        //trace(i, j, k);
                        ccnt[i] = min(ccnt[i], 0);
                    }
                }
            }
        }

        int ret = 0;
        fo(i, 9) ret += ccnt[i];

        //if(ret != 0) {fo(i, 9) if(is1(mask, i)) cerr << i << "(" << ccnt[i] << ")"; cerr << " " << ret << endl;}
        if(ret < 3) ret = -1;

        return ret;
    }
	int maxSizeOf9Free( vector <int> A ) {
		int ret = -1;
        ini(cnt, 0);
        for(int x: A) ++cnt[x % 9];
        //fo(i, 10) trace(i, cnt[i]);
        for(int i = 0; i < 9; i += 3) cnt[i] = min(cnt[i], 2);

        fo(mask, (1 << 9))	{
            ret = max(ret, calc(mask));
        }
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
