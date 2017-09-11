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

class BearBall {
public:
    int till(int n) {
        return n * (n + 1) / 2;
    }
	int countThrows( vector <int> x, vector <int> y ) {
        int ret = 0;
        vector<pi> v;
        int n = si(x);
        fo(i, n) v.emplace_back(x[i], y[i]);
        sort(all(v));
        
        fo(i, n) {
            map<pi, vi> has;
            fo(j, n) if(i != j) {
                int dx = (v[j].fi - v[i].fi);
                int dy = (v[j].se - v[i].se);
                int g = __gcd(dx, dy);
                //trace(i, j, dx, dy, v[i], v[j], g);
                dx /= g; dy /= g;
                has[mp(dx, dy)].push_back(j);
            }
            //trace(i, has);
            int ci = 0;
            for(auto cur: has) {
                if(si(cur.se) <= 1) {
                    ++ret;
                    continue;
                }
                vi sm, bg;
                for(int x: cur.se) {
                    if(x < i) sm.push_back(x);
                    else bg.push_back(x);
                }

                if(si(has) > 1) {
                    ci += 2 * si(sm) + 2 * si(bg);
                    if(!sm.empty()) --ci;
                    if(!bg.empty()) --ci;
                } else {
                    ci += till(si(sm)) + till(si(bg)); 
                }

            }
            //trace(i, ci);
            ret += ci;
        }

		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
