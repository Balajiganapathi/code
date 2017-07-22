/* string coder = "Balajiganapathi"; */


#include<bits/stdc++.h>

using namespace std;

/* aliases */
using vi=vector<int>;
using pi=pair<int,int>;
using vs=vector<string>;

/* shortcut macros */
#define fi          first
#define se          second
#define all(x)      (x).begin(), (x).end()
#define ini(a, v)   memset(a, v, sizeof(a))
#define re(i,s,n)  	for(auto i=s;i<(n);++i)
#define rep(i,s,n)  for(auto i=s;i<=(n);++i)
#define fo(i,n)     re(i,0,n)
#define pu          push_back
#define mp          make_pair
#define si(x)       (int)(x.size())
#define is1(mask,i) ((mask >> i) & 1)

/* trace macro */
#ifdef TRACE
#   define trace(v...)   {cerr<<__FUNCTION__<<":"<<__LINE__<<": ";_dt(#v,v);}
#else
#   define trace(...)
#endif



/* constants */
constexpr auto oo = numeric_limits<int>::max() / 2 - 10;
constexpr auto eps = 1e-6;
constexpr int mod = 1000000007;
constexpr int lim = 1000000000;

/* code */
constexpr int mx = -1;

class LCMGCD {
public:

    set<int> g;
    void gen(int a, int b, int num) {
        g.insert(num);
        trace(a, b, num);
        if(2ll * num <= lim) gen(a + 1, b , 2 * num);
        if(3ll * num <= lim) gen(a, b + 1 , 3 * num);
    }

    pi get(int x) {
        pi ret(0, 0);
        for(; x % 2 == 0; x /= 2) ++ret.fi;
        for(; x % 3 == 0; x /= 3) ++ret.se;

        return ret;
    }

    pi gmin(pi a, pi b) {
        return mp(min(a.fi, b.fi), min(a.se, b.se));
    }

    pi gmax(pi a, pi b) {
        return mp(max(a.fi, b.fi), max(a.se, b.se));
    }

	string isPossible( vector <int> x, int tt ) {
		string ret = "Impossible";
		string pos = "Possible";
		int n = si(x);
		vector<pi> v;
		fo(i, n) v.pu(get(x[i]));
        sort(all(v));
		pi t = get(tt);

        bool hasBefore = false, hasAfter = false, hasAt = false;
        int minBefore, maxBefore, minAfter, maxAfter, minAt, maxAt;
        minBefore = minAfter = minAt = oo;
        maxBefore = maxAfter = maxAt = -oo;

        fo(i, n) {
            if(v[i].fi < t.fi) {
                minBefore = min(minBefore, v[i].se);
                maxBefore = max(maxBefore, v[i].se);
                if(v[i].se == t.se) hasBefore = true;
            } else if(v[i].fi > t.fi) {
                minAfter = min(minAfter, v[i].se);
                maxAfter = max(maxAfter, v[i].se);
                if(v[i].se == t.se) hasAfter = true;
            } else if(v[i].fi == t.fi) {
                minAt = min(minAt, v[i].se);
                maxAt = max(maxAt, v[i].se);
                if(v[i].se == t.se) hasAt = true;
            }
        }

        if(minAt == oo) return ret;

        fo(i, n) trace(v[i].fi, v[i].se);
        trace(t.fi, t.se);
        trace(hasBefore, hasAt, hasAfter);
        // 0 0 0
        if(!hasAt && !hasBefore && !hasAfter) return ret;
        // 1 0 1
        // 1 1 1
        if(hasAfter && hasBefore) return pos;
        // 0 0 1
        // 0 1 1
        if(!hasBefore &&  hasAfter) {
            if(max(maxBefore, maxAt) >= t.se) return pos;
        }
        // 1 0 0
        // 1 1 0
        if(hasBefore &&  !hasAfter) {
            if(min(minAfter, minAt) <= t.se) return pos;
        }
        // 0 1 0
        if(!hasBefore && hasAt && !hasAfter) {
            if(count(all(v), t) >= 3) return pos;
            if(minBefore <= t.se && maxAfter >= t.se) return pos;
            if(minBefore != oo && min(minAfter, minBefore) <= t.se) return pos;
            if(minAfter != oo && max(maxAfter, maxBefore) >= t.se) return pos;
            if(minAfter == oo && minBefore == oo) return pos;
        }
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.17 [modified TZTester]
// Powered by CodeProcessor
