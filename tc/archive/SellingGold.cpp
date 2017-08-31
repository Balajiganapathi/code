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
constexpr int mx_n = 55, mx_g = 55 * 501;

int dp[2][mx_n/2][mx_g];

class SellingGold {
public:
    vi go, pr;
    int n;

    int solve(int i, int rem, int g) {
        if(g < 0 || rem < 0) return oo;
        if(i == n) return (rem == 0 && g == 0? 0: oo);
        return dp[i&1][rem][g];
    }

	double minimalSum( vector <int> gold, vector <int> price ) {
		double ret = 1e100;
        go = gold; pr = price;
        n = si(go);
        int Gc = 0, G = 0;
        fo(i, n) {
            G += go[i];
            Gc += pr[i];
        }

        for(int i = n-1; i >= 0; --i) {
            rep(rem, 0, n/2) rep(g, 0, G) {
                dp[i&1][rem][g] = min(solve(i+1, rem, g), solve(i+1, rem-1, g-go[i]) + pr[i]);
            }
        }
        //trace(G, Gc);

        rep(g, 0, G) {
            int gc = dp[0][n/2][g];
            if(gc < oo) {
                //trace(g, gc, (G-g), (Gc-gc));
                double cur = 1.0L * gc / g + 1.0L * (Gc - gc) / (G - g);
                ret = min(ret, cur);
            }
        }

		
		return ret;
	}
};

// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}
	
	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int gold[]                = {2,4};
			int price[]               = {3,4};
			double expected__         = 2.5;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int gold[]                = {1,1,2,2};
			int price[]               = {1,1,1,1};
			double expected__         = 1.3333333333333333;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int gold[]                = {2,1,1,1};
			int price[]               = {300,300,300,300};
			double expected__         = 500.0;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int gold[]                = {500,500,500,500,500,500};
			int price[]               = {1,2,4,4,2,2};
			double expected__         = 0.01;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int gold[]                = {1,2,3,4,5,6,7,8};
			int price[]               = {2,3,4,5,6,7,8,10};
			double expected__         = 2.498452012383901;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int gold[]                = ;
			int price[]               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int gold[]                = ;
			int price[]               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int gold[]                = ;
			int price[]               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = SellingGold().minimalSum(vector <int>(gold, gold + (sizeof gold / sizeof gold[0])), vector <int>(price, price + (sizeof price / sizeof price[0])));
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
