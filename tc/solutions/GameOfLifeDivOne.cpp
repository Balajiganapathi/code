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
constexpr int mx_n = 52;

ll dp[mx_n][mx_n][2][2][2];

class GameOfLifeDivOne {
public:
    string str;
    int n;
    // i -> current i 0 to n-1
    // k -> remaining ones needed K to 0
    // f -> first char 0/1
    // l -> last char 0/1
    // c -> cnt of last char 1/2+
    ll solve(int i, int k, int f, int l, int c) {
        if(i == n) return k == 0;
        ll &ret = dp[i][k][f][l][c-1];

        ret = 0;
        if(str[i] == '0' || str[i] == '?') {
        }

        return ret;
    }

    ll solve(int k) {
        ini(dp, -1);
        if(str[0] == '0') return solve(0, k, 0, 0, 1);
        else if(str[0] == '1') return solve(0, k, 1, 1, 1);
        return solve(0, k, 0, 0, 1) + solve(0, k, 1, 1, 1);
    }

    ll comb(ll n, ll k) {
        if(k == 0) return 1;
        ll ret = 1;
        int c = 0;
        rep(i, n - k + 1, n) {
            ++c;
            ret = ret * i / c;
        }

        return ret;
    }

    ll solve0(int k) {
        int ones = 0, zeros = 0, q = 0;
        fo(i, n) {
            if(str[i] == '0') ++zeros;
            else if(str[i] == '1') ++ones;
            else ++q;
        }
        int atleast = max(0, k - ones);

        ll ret = 0;
        rep(i, atleast, q) ret += comb(q, i);

        return ret;
    }


	long long theCount( string init, int T, int K ) {
        str = init;
        n = si(str);
        if(T == 0) return solve0(K);
		
		return solve(K);
	}
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
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
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string init               = "0?1";
			int T                     = 1;
			int K                     = 1;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string init               = "?????????";
			int T                     = 0;
			int K                     = 1;
			long long expected__      = 511;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string init               = "??0???????";
			int T                     = 58;
			int K                     = 6;
			long long expected__      = 151;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string init               = "?????????1";
			int T                     = 47;
			int K                     = 3;
			long long expected__      = 453;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string init               = "?????????1???0???1??1??????0??????0??0????1???????";
			int T                     = 12;
			int K                     = 40;
			long long expected__      = 31577324313LL;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string init               = ;
			int T                     = ;
			int K                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string init               = ;
			int T                     = ;
			int K                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string init               = ;
			int T                     = ;
			int K                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = GameOfLifeDivOne().theCount(init, T, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}
 

int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
