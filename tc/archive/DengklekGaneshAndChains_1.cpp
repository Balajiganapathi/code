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

class DengklekGaneshAndChains {
public:
    string largest(string ch) {
        vector<string> v;
        fo(i, si(ch)) {
            string cur;
            fo(j, si(ch)) cur += ch[(i+j)%si(ch)];
            v.push_back(cur);
        }
        return *max_element(all(v));
    }

	string getBestChains( vector <string> chains, vector <int> lengths ) {
		string ret;
        fo(i, si(chains)) chains[i] = largest(chains[i]);
        sort(chains.rbegin(), chains.rend());
        //trace(chains);
        vi used(si(chains), 0);

        fo(k, si(lengths)) {
            int l = lengths[k];
            string best;
            fo(i, si(chains)) if(!used[i]) {
                best = chains[i].substr(0, l);
                break;
            }
            //trace(k, l, best, used);
            int idx = -1;
            fo(i, si(chains)) if(!used[i] && chains[i].substr(0, l) == best) idx = i;
            used[idx] = 1;
            ret += best;
        }
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
