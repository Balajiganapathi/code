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
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 33;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
    int N;
    VVL cap, flow, cost;
    VI found;
    VL dist, pi, width;
    VPII dad;
    MinCostMaxFlow(int N) :
        N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)),
        found(N), dist(N), pi(N), width(N), dad(N) {}
    void AddEdge(int from, int to, L cap, L cost) {
        //trace(from, to, cap, cost);
        this->cap[from][to] = cap;
        this->cost[from][to] = cost;
    }
    void Relax(int s, int k, L cap, L cost, int dir) {
        L val = dist[s] + pi[s] - pi[k] + cost;
        if (cap && val < dist[k]) {
            dist[k] = val;
            dad[k] = make_pair(s, dir);
            width[k] = min(cap, width[s]);
        }
    }
    L Dijkstra(int s, int t) {
        fill(found.begin(), found.end(), false);
        fill(dist.begin(), dist.end(), INF);
        fill(width.begin(), width.end(), 0);
        dist[s] = 0;
        width[s] = INF;
        while (s != -1) {
            int best = -1;
            found[s] = true;
            for (int k = 0; k < N; k++) {
                if (found[k]) continue;
                Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
                Relax(s, k, flow[k][s], -cost[k][s], -1);
                if (best == -1 || dist[k] < dist[best]) best = k;
            }
            s = best;
        }
        for (int k = 0; k < N; k++)
            pi[k] = min(pi[k] + dist[k], INF);
        return width[t];
    }
    pair<L, L> GetMaxFlow(int s, int t) {
        L totflow = 0, totcost = 0;
        while (L amt = Dijkstra(s, t)) {
            totflow += amt;
            for (int x = t; x != s; x = dad[x].first) {
                if (dad[x].second == 1) {
                    flow[dad[x].first][x] += amt;
                    totcost += amt * cost[dad[x].first][x];
                } else {
                    flow[x][dad[x].first] -= amt;
                    totcost -= amt * cost[x][dad[x].first];
                }
            }
        }
        return make_pair(totflow, totcost);
    }
};




int dp[mx_n][mx_n];
class GoodCompanyDivOne {
public:
    vi tr;
    vi ch[mx_n];
    int n, m;

    int solve(int i, int p) {
        int &ret = dp[i][p];
        if(ret != -1) return ret;
        ret = 0;

        ret += tr[p];

        int cc = si(ch[i]);
        int s = 1 + cc + m;
        int t = s + 1;
        MinCostMaxFlow mcmf(t+1);

        if(cc+1 > m) return ret = oo;
        fo(j, si(ch[i])) {
            mcmf.AddEdge(s, j, 1, 0);
            fo(k, m) {
                mcmf.AddEdge(j, k + cc + 1, 1, solve(ch[i][j], k));
            }
        }

        mcmf.AddEdge(s, cc+1, 1, 0);
        fo(k, m) if(k != p) mcmf.AddEdge(cc+1, k + cc+1, 1, tr[k]);
        fo(k, m) mcmf.AddEdge(k+cc+1, t, 1, 0);

        auto res = mcmf.GetMaxFlow(s, t);
        if(res.fi < cc+1) return ret = oo;
        ret += res.se;

        if(si(ch[i]) == 0) ret += tr[(p == 0? 1: 0)];

        if(ret >= oo) ret = oo;

        return ret;
    }

	int minimumCost( vector <int> superior, vector <int> training ) {
		int ret = oo;
        n = si(superior);
        m = si(training); tr = training;
        sort(all(tr));
        fo(i, n) if(superior[i] != -1) ch[superior[i]].push_back(i);

        ini(dp, -1);
        fo(i, m) ret = min(ret, solve(0, i));
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
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
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
			int superior[]            = {-1};
			int training[]            = {1, 2};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int superior[]            = {-1, 0, 0};
			int training[]            = {1, 2, 3};
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int superior[]            = {-1, 0, 0, 0};
			int training[]            = {1, 2, 3};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int superior[]            = {-1, 0, 0, 2, 2, 2, 1, 1, 6, 0, 5, 4, 11, 10, 3, 6, 11, 7, 0, 2, 13, 14, 2, 10, 9, 11, 22, 10, 3};
			int training[]            = {4, 2, 6, 6, 8, 3, 3, 1, 1, 5, 8, 6, 8, 2, 4};
			int expected__            = 71;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int superior[]            = ;
			int training[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int superior[]            = ;
			int training[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int superior[]            = ;
			int training[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
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
