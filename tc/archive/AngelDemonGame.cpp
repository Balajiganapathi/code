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
constexpr int mx = -1;

typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 1000000000;

struct MaxFlow {
  int N;
  VVI cap, flow;
  VI dad, Q;

  MaxFlow(int N) :
    N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N) {}

  void AddEdge(int from, int to, int cap) {
    this->cap[from][to] += cap;
  }

  int BlockingFlow(int s, int t) {
    fill(dad.begin(), dad.end(), -1);
    dad[s] = -2;

    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < N; i++) {
        if (dad[i] == -1 && cap[x][i] - flow[x][i] > 0) {
          dad[i] = x;
          Q[tail++] = i;
        }
      }
    }

    if (dad[t] == -1) return 0;

    int totflow = 0;
    for (int i = 0; i < N; i++) {
      if (dad[i] == -1) continue;
      int amt = cap[i][t] - flow[i][t];
      for (int j = i; amt && j != s; j = dad[j])
        amt = min(amt, cap[dad[j]][j] - flow[dad[j]][j]);
      if (amt == 0) continue;
      flow[i][t] += amt;
      flow[t][i] -= amt;
      for (int j = i; j != s; j = dad[j]) {
        flow[dad[j]][j] += amt;
        flow[j][dad[j]] -= amt;
      }
      totflow += amt;
    }

    return totflow;
  }

  int GetMaxFlow(int source, int sink) {
    int totflow = 0;
    while (int flow = BlockingFlow(source, sink))
      totflow += flow;
    return totflow;
  }
};

class AngelDemonGame {
public:
    int n;
    vector<string> g;


    int min_increase(MaxFlow& mf) {
        vi par(n, -1);
        vi dist(n, oo);
        set<pi> q;
        dist[0] = 0;
        q.emplace(0, 0);
        while(!q.empty()) {
            auto cur = *q.begin(); q.erase(q.begin());
            int x = cur.se, d = cur.fi;
            if(dist[x] < d) continue;
            fo(i, n) {
                if(g[x][i] == 'Y' && mf.flow[x][i] == mf.cap[x][i] && dist[i] > d) {
                    dist[i] = d;
                    q.emplace(d, i);
                    par[i] = x;
                }
                if(g[x][i] == 'N' && dist[i] > d + 1) {
                    dist[i] = d + 1;
                    q.emplace(d + 1, i);
                    par[i] = x;
                }
            }
        }

        int x = n - 1;
        while(x != 0) {
            int y = par[x];
            g[x][y] = g[y][x] = 'Y';
            x = y;
        }
        trace(dist[n-1]);
        return dist[n-1];
    }

	string winner( vector <string> G, int A, int D ) {
		string ret;
        g = G; n = si(g);
        //trace(A, D, n);
        if(D >= n - 1) return "Demon";

        while(A > 0)  {
            MaxFlow mf(n);
            fo(i, n) fo(j, n) if(g[i][j] == 'Y') {
                mf.AddEdge(i, j, 1);
                mf.AddEdge(j, i, 1);
            }
            int f = mf.GetMaxFlow(0, n - 1);
            if(f > D) return "Angel";
            if(f == n - 1) break;
            A -= min_increase(mf);
        }
		
		return "Unknown";
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
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string G[]                = {"NYNY",
 "YNYY",
 "NYNN",
 "YYNN"};
			int A                     = 2;
			int D                     = 2;
			string expected__         = "Angel";

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string G[]                = {"NYNY",
 "YNYY",
 "NYNN",
 "YYNN"};
			int A                     = 6;
			int D                     = 6;
			string expected__         = "Demon";

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string G[]                = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"};
			int A                     = 2;
			int D                     = 2;
			string expected__         = "Unknown";

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string G[]                = {"NYNNNY",
 "YNNYNN",
 "NNNNYN",
 "NYNNNN",
 "NNYNNN",
 "YNNNNN"};
			int A                     = 4;
			int D                     = 4;
			string expected__         = "Unknown";

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string G[]                = {"NYNNNY",
 "YNNYNN",
 "NNNNYN",
 "NYNNNN",
 "NNYNNN",
 "YNNNNN"};
			int A                     = 8;
			int D                     = 4;
			string expected__         = "Angel";

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string G[]                = {"NYNNNY",
 "YNNYNN",
 "NNNNYN",
 "NYNNNN",
 "NNYNNN",
 "YNNNNN"};
			int A                     = 4;
			int D                     = 8;
			string expected__         = "Demon";

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string G[]                = ;
			int A                     = ;
			int D                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string G[]                = ;
			int A                     = ;
			int D                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string G[]                = ;
			int A                     = ;
			int D                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
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
