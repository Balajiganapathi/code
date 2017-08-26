/* string coder = "Balajiganapathi S"; // Never give up!  */


// BEGIN CUT HERE
//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#else
#   define NDEBUG
//#   define FAST
#endif
// END CUT HERE

#include<bits/stdc++.h>

using namespace std;

/* aliases */
using vi  = vector<int>;
using ll  = long long int;
using pi  = pair<ll, ll>;

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

// BEGIN CUT HERE
/* trace macro */
#ifdef TRACE
#   define trace(v...)  {cerr << __func__ << ":" << __LINE__ << ": " ;_dt(#v, v);}
#else
#   define trace(...)
#endif

#ifdef TRACE
pi _gp(string s) {
    pi r(0, si(s) - 1);
    int p = 0, s1 = 0, s2 = 0, start = 1;
    fo(i, si(s)) {
        int x = (s1 | s2);
        if(s[i] == ' ' && start) {
            ++r.fi;
        } else {
            start = 0;
            if(s[i] == ',' && !p && !x) {
                r.se = i - 1;
                return r;
            }
            if(x && s[i] == '\\') ++i;
            else if(!x && s[i] == '(') ++p;
            else if(!x && s[i] == ')') --p;
            else if(!s2 && s[i] == '\'') s1 ^= 1;
            else if(!s1 && s[i] == '"') s2 ^= 1;
        }
    }
    return r;
}

template<typename H> void _dt(string u, H&& v) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " |" << endl;
}

template<typename H, typename ...T> void _dt(string u, H&& v, T&&... r) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " | ";
    _dt(u.substr(p.se + 2), forward<T>(r)...);
}

template<typename T> 
ostream &operator <<(ostream &o, vector<T> v) { // print a vector
    o << "[";
    fo(i, si(v) - 1) o << v[i] << ", ";
    if(si(v)) o << v.back();
    o << "]";
    return o;
}

template<typename T1, typename T2> 
ostream &operator <<(ostream &o, map<T1, T2> m) { // print a map
    o << "{";
    for(auto &p: m) {
        o << " (" << p.fi << " -> " << p.se << ")";
    }
    o << " }";
    return o;
}

template<typename T> 
ostream &operator <<(ostream &o, set<T> s) { // print a set
    o << "{";
    bool first = true;
    for(auto &entry: s) {
        if(!first) o << ", ";
         
        o << entry;
        first = false;
    }
    o << "}";
    return o;
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
    print_tuple(ostream&, const tuple<T...>&) {} 

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
    print_tuple(ostream& os, const tuple<T...>& tup) {
    if (n != 0)
        os << ", ";
    os << get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
ostream& operator<<(ostream& os, const tuple<T...>& tup) { // print a tuple
    os << "("; print_tuple<0>(os, tup); return os << ")"; } template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { // print a pair
    return os << "(" << p.fi << ", " << p.se << ")";
}
#endif
// END CUT HERE
    
#define x1 _asdfzx1
#define y1 _ysfdzy1

/* constants */
constexpr int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dy[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = 1000000000000L;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 12;

ll dist[(1 << mx_n) + 10][mx_n];

class State {
public:
    int mask, cur;
    ll d;

    State(): mask(0), cur(-1), d(oo) {};
    State(int m, int c, ll d): mask(m), cur(c), d(d) {}

    bool operator <(const State &s) const {
        return d < s.d;
    }
};



class AliceInWanderland {
public:
    vi rx, ry;
    vector<string> mv;
    vector<vector<pi>> acc;
    int n;

    void pre() {
        for(string m: mv) {
            ll dx = 0, dy = 0;
            vector<pi> v;
            v.emplace_back(0, 0);
            for(char c: m) {
                if(c == 'R') ++dx;
                if(c == 'L') --dx;
                if(c == 'U') ++dy;
                if(c == 'D') --dy;
                v.emplace_back(dx, dy);
            }
            acc.push_back(v);
        }
    }

    pi getAt(int i, ll d) {
        if(i == n) return {0, 0};
        pi ans(rx[i], ry[i]);

        ll times = d / si(mv[i]);
        ans.fi += acc[i].back().fi * times;
        ans.se += acc[i].back().se * times;

        ans.fi += acc[i][d%si(mv[i])].fi;
        ans.se += acc[i][d%si(mv[i])].se;

        return ans;
    }

    ll getDist(pi cur, pi nxt) {
        ll df = abs(cur.fi - nxt.fi);
        ll ds = abs(cur.se - nxt.se);

        return max(df, ds);
    }

    ll getDist(int ci, int ni, ll d) {
        pi cur = getAt(ci, d);
        ll lo = d, hi = oo;
        while(lo < hi) {
            ll m = (lo + hi) / 2;
            pi nxt = getAt(ni, m);
            if(getDist(cur, nxt) <= m - d) hi = m;
            else lo = m + 1;
        }


        ll nd = lo;
        if(lo < oo) assert(getDist(cur, getAt(ni, lo)) <= lo - d);
        //trace(ci, ni, d, nd);
        return nd;
    }

	long long getMinimum( vector <int> rabbitX, vector <int> rabbitY, vector <string> _moves ) {
		long long ret = -1;
        rx = rabbitX; ry = rabbitY; mv = _moves;
        n = si(rx);
        pre();

        fo(i, (1 << n)) fo(j, n+1) dist[i][j] = oo;

        set<State> pq;
        dist[0][n] = 0;
        pq.insert(State(0, n, 0));

        while(!pq.empty()) {
            auto state = *pq.begin();
            pq.erase(pq.begin());
            int mask = state.mask, cur = state.cur;
            ll d = state.d;
            assert(d == dist[mask][cur]);
            if(d >= oo) continue;

            fo(nxt, n) if(!is1(mask, nxt)) {
                ll nd = getDist(cur, nxt, d);
                assert(nd >= d);
                if(nd >= oo  || nd == -1) continue;
                State nstate((mask|(1 << nxt)), nxt, nd);
                if(nd < dist[nstate.mask][nstate.cur]) {
                    State pstate(nstate.mask, nstate.cur, dist[nstate.mask][nstate.cur]);
                    pq.erase(pstate);
                    dist[nstate.mask][nstate.cur] = nd;
                    pq.insert(nstate);
                }
            }
        }

        ret = oo;
        fo(i, n) ret = min(ret, dist[(1 << n) - 1][i]);
        if(ret >= oo) ret = -1;
		
		return ret;
	}
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int rabbitX[]             = { 4 };
			int rabbitY[]             = { 2 };
			string moves[]            = { "ULDR" };
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int rabbitX[]             = { 10, -20 };
			int rabbitY[]             = { 0, 0 };
			string moves[]            = { "RL", "LULD" };
			long long expected__      = 80;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int rabbitX[]             = { 30, -40 };
			int rabbitY[]             = { 0, 0 };
			string moves[]            = { "RL", "DLUL" };
			long long expected__      = 188;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int rabbitX[]             = { 0 };
			int rabbitY[]             = { 1 };
			string moves[]            = { "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" };
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int rabbitX[]             = { 1000000000, 1000000000, -1000000000, -1000000000, 1000000000, 1000000000, -1000000000, -1000000000, 0, 0, 0};
			int rabbitY[]             = { 0, 0, 0, 0, 0, 0, 0, 0, 1000000000, 1000000000, -1000000000};
			string moves[]            = { "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRU", 
  "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRD", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLU", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLD", 
  "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRUU", 
  "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDD", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLUU", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLDD", 
  "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUR", 
  "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUL", 
  "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDR" }
;
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int rabbitX[]             = { 1, 1 };
			int rabbitY[]             = { 0, 0 };
			string moves[]            = { "L", "U" };
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			int rabbitX[]             = {5, 1, 5, 0, 2, 2, -4, -8, 1, -3};
			int rabbitY[]             = {-3, 3, 2, 8, -7, -1, -2, 4, 4, -3};
			string moves[]            = {"RDDDDR", "RRRLLRLLRLL", "DDDRRLDDDDUUR", "RRRRRDLURRRRL", "LUUUUD", "RLRLRUUURDRUUR", "LULLU", "UD", "DDULL", "RUUUDLLULU"};
			long long expected__      = 166;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int rabbitX[]             = ;
			int rabbitY[]             = ;
			string moves[]            = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int rabbitX[]             = ;
			int rabbitY[]             = ;
			string moves[]            = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = AliceInWanderland().getMinimum(vector <int>(rabbitX, rabbitX + (sizeof rabbitX / sizeof rabbitX[0])), vector <int>(rabbitY, rabbitY + (sizeof rabbitY / sizeof rabbitY[0])), vector <string>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}
 

#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
