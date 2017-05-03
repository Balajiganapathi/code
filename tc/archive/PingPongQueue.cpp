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

class PingPongQueue {
public:
	vector <int> whoPlaysNext( vector <int> skills, int N, int K ) {
		set <int> ret;
        queue<int> q;
        map<int, int> wins;
        re(i, 2, si(skills)) q.push(skills[i]);
        ret.insert(skills[0]);
        ret.insert(skills[1]);

        fo(k, K - 1) {
            int l = *ret.begin();
            q.push(l);
            ret.erase(l);
            wins[l] = 0;
            int w = *ret.begin();
            if(++wins[w] >= N) {
                wins[w] = 0;
                q.push(w);
                ret.erase(w);
            }
            while(si(ret) < 2) {
                ret.insert(q.front()); q.pop();
            }
        }
		
		return vi(all(ret));
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
