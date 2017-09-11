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
constexpr int mx_n = 55;
using ld = long double;
ld dp[mx_n][mx_n], C[mx_n][mx_n];

class CalculationCards {
public:
    int n;
    int s,m;
    vi c, mul;

    ld comb(int n, int k) {
        if(n < 0 || k < 0 || k > n) return 0;
        return C[n][k];
    }

    ld prob(int s, int m, int cnt) {
        ld ret = 0;
        if(s == 0) return 1;
        ret += comb(s+m-cnt-1, m-cnt);
        ret += 1.0L * (s+m-cnt-1) * comb(s+m-cnt-2, m-cnt);
        ret /= 1.0L * (s+m) * comb(s+m-1, m);

        return ret;
    }

	double getExpected( vector <string> cards ) {
		double ret;
        n = si(cards);
        vi cnt(10);
        for(string s: cards) {
            if(s[0] == '+') c.push_back(s[1] - '0');
            else if(s[0] == '-') c.push_back('0' - s[1]);
            else mul.push_back(s[1]-'0');
        }

        int s = si(c), m = si(mul);

        rep(i, 0, n) {
            C[i][0] = 1;
            rep(j, 1, i) C[i][j] = C[i-1][j-1] + C[i-1][j];
        }

        ini(dp, 0);

        //trace(c, mul);
        dp[m][0] = 1;
        for(int i = m-1; i >= 0; --i) {
            dp[i][0] = 1;
            rep(j, 1, m) {
                dp[i][j] = dp[i+1][j] + mul[i] * dp[i+1][j-1];
                ////trace(i, j, dp[i+1][j], dp[i+1][j-1], mul[i], dp[i][j]);
            }
        }

        ld ef = 0;

        rep(cnt, 0, m) {
            //trace(cnt, prob(s, m, cnt), dp[0][cnt], C[m][cnt]);
            ef += prob(s, m, cnt) * dp[0][cnt] / C[m][cnt];
        }

        //trace(ef);
        ret = ef * accumulate(all(c), 0.0L);
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
			string cards[]            = { "+1", "-2", "*3" };
			double expected__         = -1.6666666666666667;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string cards[]            = { "+1", "+2", "+3" };
			double expected__         = 6.0;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string cards[]            = { "+3", "-7", "*4", "+6" };
			double expected__         = 3.5;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string cards[]            = { "+1", "*2", "*3" };
			double expected__         = 3.1666666666666665;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string cards[]            = { "*7", "-2", "*0", "+3", "*8" };
			double expected__         = 5.633333333333334;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string cards[]            = { "+1", "*9", "*9", "*9", "*9", "*9", "*9", "*9", "*9", "*9", "*9" };
			double expected__         = 3.5660295009090906E8;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			string cards[]            = {"*1"};
			double expected__         = 0;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string cards[]            = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string cards[]            = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = CalculationCards().getExpected(vector <string>(cards, cards + (sizeof cards / sizeof cards[0])));
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
