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

class BearGridRect {
public:
    typedef vector<int> VI;
    typedef vector<VI> VVI;

    bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
        for (int j = 0; j < w[i].size(); j++) {
            if (w[i][j] && !seen[j]) {
                seen[j] = true;
                if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
                    mr[i] = j;
                    mc[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

    int BipartiteMatching(const VVI &w, VI &mr, VI &mc) {
        mr = VI(w.size(), -1);
        mc = VI(w[0].size(), -1);

        int ct = 0;
        for (int i = 0; i < w.size(); i++) {
            VI seen(w[0].size());
            if (FindMatch(i, w, mr, mc, seen)) ct++;
        }
        trace(ct);
        return ct;
    }
    vector<pi> solve(int n, vi r, vi c, vi r1, vi r2, vi c1, vi c2) {
        VVI w(n, VI(n));
        for(int i: r) for(int j: c) {
            bool ok = true;
            fo(k, si(r1)) if(r1[k] <= i && i <= r2[k] && c1[k] <= j && j <= c2[k]) ok = false;
            if(ok) w[i][j] = 1;
        }
        VI mr, mc;

        BipartiteMatching(w, mr, mc);
        vector<pi> ret;
        for(int i: r) if(mr[i] != -1) ret.emplace_back(i, mr[i]);

        return ret;
    }

    vector<vi> solve(int n, vi r1, vi r2, vi c) {
        int m = si(r1);
        vector<vi> ret(m+1);

        fo(r, n) {
            int to = m;
            fo(i, m) if(r1[i] <= r && r <= r2[i] && c[i] > 0) {
                if(to == m || r2[to] > r2[i]) to = i;
            }
            --c[to];
            ret[to].push_back(r);
        }

        fo(i, m) if(c[i] > 0) return vector<vi>();
        return ret;
    }

	vector <int> findPermutation( int N, vector <int> r1, vector <int> r2, vector <int> c1, vector <int> c2, vector <int> cnt ) {
		vector <int> ret;
        vector<vi> r = solve(N, r1, r2, cnt);
        vector<vi> c = solve(N, c1, c2, cnt);
        trace(r1, r2) trace(c1, c2); trace(cnt); trace(r, c);

        if(si(r) == 0 || si(c) == 0) return vi(1, -1);
        vector<pi> restmatch = solve(N, r.back(), c.back(), r1, r2, c1, c2);

        trace(restmatch);
        if(si(restmatch) != si(r.back())) return vi(1, -1);

        ret = vi(N);
        fo(i, si(r) - 1) {
            //trace(i, r[i], c[i]);
            fo(j, si(r[i])) ret[r[i][j]] = c[i][j];
        }

        for(auto p: restmatch) ret[p.fi] = p.se;
		
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
			int N                     = 5;
			int r1[]                  = {4, 0};
			int r2[]                  = {4, 1};
			int c1[]                  = {2, 1};
			int c2[]                  = {4, 2};
			int cnt[]                 = {0, 2};
			int expected__[]          = {1, 2, 4, 3, 0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			int r1[]                  = {4, 0, 2};
			int r2[]                  = {4, 1, 2};
			int c1[]                  = {2, 1, 2};
			int c2[]                  = {4, 2, 2};
			int cnt[]                 = {0, 2, 1};
			int expected__[]          = {-1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int r1[]                  = {0};
			int r2[]                  = {2};
			int c1[]                  = {0};
			int c2[]                  = {2};
			int cnt[]                 = {0};
			int expected__[]          = {-1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int N                     = 4;
			int r1[]                  = {0};
			int r2[]                  = {0};
			int c1[]                  = {0};
			int c2[]                  = {0};
			int cnt[]                 = {0};
			int expected__[]          = {1, 0, 2, 3 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int N                     = 2;
			int r1[]                  = {0, 0, 1, 1};
			int r2[]                  = {0, 0, 1, 1};
			int c1[]                  = {0, 1, 0, 1};
			int c2[]                  = {0, 1, 0, 1};
			int cnt[]                 = {0, 1, 1, 0};
			int expected__[]          = {1, 0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int N                     = 2;
			int r1[]                  = {0, 0, 1, 1};
			int r2[]                  = {0, 0, 1, 1};
			int c1[]                  = {0, 1, 0, 1};
			int c2[]                  = {0, 1, 0, 1};
			int cnt[]                 = {0, 1, 0, 1};
			int expected__[]          = {-1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 6: {
			int N                     = 2;
			int r1[]                  = {0, 0, 1, 1};
			int r2[]                  = {0, 0, 1, 1};
			int c1[]                  = {0, 1, 0, 1};
			int c2[]                  = {0, 1, 0, 1};
			int cnt[]                 = {1, 1, 1, 1};
			int expected__[]          = {-1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 7: {
			int N                     = 6;
			int r1[]                  = {0, 0, 4};
			int r2[]                  = {2, 3, 5};
			int c1[]                  = {0, 5, 1};
			int c2[]                  = {4, 5, 5};
			int cnt[]                 = {3, 1, 1};
			int expected__[]          = {1, 2, 4, 5, 3, 0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 8: {
			int N                     = 3;
			int r1[]                  = {0};
			int r2[]                  = {0};
			int c1[]                  = {0};
			int c2[]                  = {0};
			int cnt[]                 = {2};
			int expected__[]          = {-1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 9: {
			int N                     = ;
			int r1[]                  = ;
			int r2[]                  = ;
			int c1[]                  = ;
			int c2[]                  = ;
			int cnt[]                 = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 10: {
			int N                     = ;
			int r1[]                  = ;
			int r2[]                  = ;
			int c1[]                  = ;
			int c2[]                  = ;
			int cnt[]                 = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 11: {
			int N                     = ;
			int r1[]                  = ;
			int r2[]                  = ;
			int c1[]                  = ;
			int c2[]                  = ;
			int cnt[]                 = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = BearGridRect().findPermutation(N, vector <int>(r1, r1 + (sizeof r1 / sizeof r1[0])), vector <int>(r2, r2 + (sizeof r2 / sizeof r2[0])), vector <int>(c1, c1 + (sizeof c1 / sizeof c1[0])), vector <int>(c2, c2 + (sizeof c2 / sizeof c2[0])), vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
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
