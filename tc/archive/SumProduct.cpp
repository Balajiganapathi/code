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
constexpr int mx_c = 202, mx_d = 11;
int C[mx_c][mx_c], p10[mx_c];;
int dp1[mx_d][mx_c];
int dp[mx_c][mx_c];

class SumProduct {
public:
    vi cnt;

    void pre() {
        fo(i, mx_c) {
            C[i][0] = C[i][i] = 1;
            re(j, 1, i) {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
                if(C[i][j] >= mod) C[i][j] -= mod;
            }
        }
        p10[0] = 1;
        re(i, 1, mx_c) p10[i] = 1ll * 10 * p10[i-1] % mod;
    }

    inline int comb(int n, int k) {
        if(n < 0 || k < 0 || k > n) return 0;
        return C[n][k];
    }

    int countdp(int i, int n) {
        if(n == 0) return 1;
        if(i == 10) return 0;
        int &ret = dp1[i][n];
        if(ret != -1) return ret;
        ret = 0;

        rep(cur, 0, min(cnt[i], n)) {
            ret = (ret + 1ll * countdp(i + 1, n - cur) * comb(n, cur)) % mod;
        }

        return ret;
    }

    int count(vi ccnt, int n) {
        cnt = ccnt;
        ini(dp1, -1);
        int ret = countdp(0, n);
        //trace(n, cnt, ret);
        return ret;
    }

    int place(int n, int c) {
        if(n < c) return 0;
        if(c <= 0) return 0;
        if(n < 0) return 0;
        int &ret = dp[n][c];
        if(ret != -1) return ret;
        ret = 0;
        if(c > 0) ret = (place(n - 1, c - 1) + 1ll * p10[n-1] * comb(n - 1, c - 1)) % mod;
        if(ret >= mod) ret -= mod;
        ret += place(n - 1, c);
        if(ret >= mod) ret -= mod;

        return ret;
    }

    int place(int n1, int c1, int n2, int c2) {
        if(n1 < c1 || n2 < c2) return 0;
        if(c1 == 0) return place(n2-1, c2);
        if(c2 == 0) return place(n1-1, c1);
        return 1ll * place(n1 - 1, c1) * place(n2 - 1, c2) % mod;
    }

    int solve(vi cnt, int n1, int n2, int d) {
        int ret = 0;
        rep(c1, 0, min(n1, cnt[d])) {
            rep(c2, 0, min(n2, cnt[d]-c1)) {
                vi rem = cnt;
                rem[d] = 0;
                int cur = 1ll * place(n1, c1) * d % mod;
                cur = 1ll * cur * count(rem, n1 - c1 + n2 - c2) % mod;
                ret += cur;
                ////trace(d, c1, c2, cur);
                if(ret >= mod) ret -= mod;
            }
        }
        ////trace(d, ret);

        return ret;
    }

    int solve(vi cnt, int n1, int n2, int d1, int d2) {
        int ret = 0;
        vi rem = cnt;
        --rem[d1]; --rem[d2];
        if(rem[d1] < 0 || rem[d2] < 0) return 0;
        int ways = count(rem, n1 + n2 - 2);

        fo(i1, n1) fo(i2, n2) {
            int cur = 1ll * d1 * d2 % mod * p10[i1] % mod * p10[i2] % mod;
             cur = 1ll * cur * ways % mod;
            ret += cur;
            if(ret >= mod) ret -= mod;
        }
        //trace(cnt, n1, n2, d1, d2, ret);

        return ret;
    }

	int findSum( vector <int> amount, int blank1, int blank2 ) {
		int ret = 0;
        pre();
        ini(dp, -1);
        fo(i, 10) fo(j, 10) {
            ret += solve(amount, blank1, blank2, i, j);
            if(ret >= mod) ret -= mod;
        }
		
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
			int amount[]              = {0,2,1,1,0,0,0,0,0,0};
			int blank1                = 2;
			int blank2                = 2;
			int expected__            = 4114;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int amount[]              = {1,6,0,0,0,0,0,0,0,0};
			int blank1                = 1;
			int blank2                = 2;
			int expected__            = 22;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int amount[]              = {1,2,3,4,5,6,7,8,9,10};
			int blank1                = 15;
			int blank2                = 3;
			int expected__            = 340242570;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int amount[]              = {3,14,15,92,65,35,89,79,32,38};
			int blank1                = 46;
			int blank2                = 26;
			int expected__            = 417461139;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int amount[]              = {100,100,100,100,100,100,100,100,100,100};
			int blank1                = 100;
			int blank2                = 100;
			int expected__            = 372980218;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int amount[]              = {0,1,1,0,0,0,0,0,0,0};
			int blank1                = 1;
			int blank2                = 1;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int amount[]              = ;
			int blank1                = ;
			int blank2                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int amount[]              = ;
			int blank1                = ;
			int blank2                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
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
