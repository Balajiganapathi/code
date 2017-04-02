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
constexpr int mx_n = 10;

int n;

class State {
public:
    int stones[mx_n];
    State() {
    }
    State(const State &s) {
        fo(i, n) stones[i] = s.stones[i];
    }
    State(const vi& v) {
        fo(i, n) stones[i] = v[i];
    }

    bool operator <(const State &s) const {
        fo(i, n) if(s.stones[i] != stones[i]) return stones[i] < s.stones[i];
        return false;
    }

    bool operator ==(const vi &v) const {
        fo(i, n) if(stones[i] != v[i]) return false;
        return true;
    }

    bool operator ==(const State &s) const {
        fo(i, n) if(stones[i] != s.stones[i]) return false;
        return true;
    }
};
namespace std {

  template <>
  struct hash<State> {
    std::size_t operator()(const State& s) const {
        size_t h = 0;
        fo(i, n) h = h ^ (s.stones[i]);
        return h;
    }
  };

}

unordered_map<State, int> last;
unordered_map<State, State> lastState;

class ReverseMancala {
public:
    void bfs(vi s, vi t) {
        last.clear();
        lastState.clear();
        last[s] = -1;
        queue<State> q;
        q.push(State(s));
        while(!q.empty()) {
            State cur = q.front(); q.pop();
            //fo(i, n) cerr << cur.stones[i] << " "; cerr << endl;
            if(cur == t) return;

            fo(i, n) {
                State nxt = cur;
                int val = nxt.stones[i];
                nxt.stones[i] = 0;
                fo(j, n) nxt.stones[j] += val / n;
                int ci = i;
                fo(j, val % n) {
                    if(++ci == n) ci = 0;
                    ++nxt.stones[ci];
                }

                if(last.find(nxt) == last.end() && *max_element(nxt.stones, nxt.stones + n) <= 10) {
                    //trace(i);
                    //fo(i, n) cerr << nxt.stones[i] << " "; cerr << endl;
                    last[nxt] = i;
                    lastState[nxt] = cur;
                    q.push(nxt);
                }
            }

            fo(i, n) {
                State nxt = cur;
                int midx = i;
                int ci = i;
                fo(j, n) {
                    if(nxt.stones[ci] < nxt.stones[midx]) midx = ci;
                    if(--ci == -1) ci = n - 1;
                }
                int add = 0;
                int sub = nxt.stones[midx];
                fo(j, n) nxt.stones[j] -= sub;
                add = sub * n;
                
                ci = i;
                fo(j, n) {
                    if(ci == midx) break;
                    --nxt.stones[ci];
                    ++add;
                    if(--ci == -1) ci = n - 1;
                }
                nxt.stones[midx] = add;

                if(last.find(nxt) == last.end() && *max_element(nxt.stones, nxt.stones + n) <= 10) {
                    last[nxt] = i + n;
                    lastState[nxt] = cur;
                    q.push(nxt);
                }
            }
        }
    }

	vector <int> findMoves( vector <int> start, vector <int> target ) {
        n = si(start);
		vector <int> ret;
        bfs(start, target);
        State cur(target);
        while(last[cur] != -1) {
            ret.push_back(last[cur]);
            cur = lastState[cur];
        }
        reverse(all(ret));
		
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
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, std::clock_t elapsed) { 
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
			int start[]               = {6, 3, 4, 0};
			int target[]              = {1, 5, 6, 1};
			int expected__[]          = {0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int start[]               = {1, 5, 6, 1};
			int target[]              = {6, 3, 4, 0};
			int expected__[]          = {6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int start[]               = {10, 0, 1, 2, 3};
			int target[]              = {10, 0, 0, 2, 4};
			int expected__[]          = {2, 4, 8 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int start[]               = {2, 0, 1, 7};
			int target[]              = {0, 2, 1, 7};
			int expected__[]          = {2, 0, 1, 7 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int start[]               = {3, 2, 4, 5};
			int target[]              = {0, 1, 6, 7};
			int expected__[]          = {7, 1, 0, 7, 1, 0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int start[]               = {2, 1, 6, 4, 5, 2, 4, 5, 3, 0};
			int target[]              = {6, 4, 8, 0, 2, 6, 0, 1, 3, 2};
			int expected__[]          = {10, 8, 2, 16, 19, 2, 4, 11, 7, 6, 12, 19, 14, 14, 15, 3, 4, 17, 11, 3, 9, 16, 4, 8, 13, 12, 11, 9, 17, 12, 19, 4, 9, 8, 10, 2, 0, 17, 10, 3, 4, 8, 16, 0, 19, 15, 7, 6, 17, 6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 6: {
			int start[]               = {3, 4, 6, 7, 2, 2, 3, 9, 4, 6};
			int target[]              = {6, 0, 5, 10, 10, 3, 1, 2, 8, 1};
			int expected__[]          = {8, 14, 1, 12, 11, 4, 9, 10, 15, 16, 2, 19, 2, 16, 17, 11, 16, 0, 12, 7, 4, 5, 17, 14, 0, 5, 13, 3, 7, 10, 12, 1, 16, 14, 1, 9, 1, 8, 7, 5, 5, 11, 19, 16, 18, 1, 15, 10, 16, 1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int start[]               = ;
			int target[]              = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			int start[]               = ;
			int target[]              = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 9: {
			int start[]               = ;
			int target[]              = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = ReverseMancala().findMoves(vector <int>(start, start + (sizeof start / sizeof start[0])), vector <int>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
