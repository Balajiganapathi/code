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
#define MAXN 65536
#define MAXLG 17


/* code */
constexpr int mx_n = 2003;
int dp[mx_n][2];
char A[MAXN];

struct entry
{
    int nr[2];
    int p;
} L[MAXN];

int P[MAXLG][MAXN];

void build() {
    int N,i;
    int stp, cnt;
    for(N=strlen(A), i = 0; i < N; i++)
        P[0][i] = A[i] - 'a';

    for(stp=1, cnt = 1; cnt < N; stp++, cnt *= 2)
    {
        for(i=0; i < N; i++)
        {
            L[i].nr[0]=P[stp- 1][i];
            L[i].nr[1]=i +cnt <N? P[stp -1][i+ cnt]:-1;
            L[i].p= i;
        }
        sort(L, L+N, cmp);
        for(i=0; i < N; i++)
            P[stp][L[i].p] =i> 0 && L[i].nr[0]==L[i-1].nr[0] && L[i].nr[1] == L[i- 1].nr[1] ? P[stp][L[i-1].p] : i;
    }

    int cmp(struct entry a, struct entry b)
    {
        return a.nr[0]==b.nr[0] ?(a.nr[1]<b.nr[1] ?1: 0): (a.nr[0]<b.nr[0] ?1: 0);
    }
}


bool ispalin(int i, int j) {
    int n = N / 2;
    int a = n+(n-1-i), b = n+(n-1-j);
    for(int l = MAXLG - 1; l >= 0; --l) if(i + (1 << l) -1 <= j) {
    }
}



class ConsecutivePalindromes {
public:
    string s;
    int solve(int i, int p) {
        if(i >= si(s)) return p;
        int &ret = dp[i][p];
        if(ret != -1) return ret;
        ret = 0;

        // skip i

        ret += solve(i+1, p);
        if(ret >= mod) ret -= mod;

        if(!p) {
            for(int j = i+1; j < si(s); ++j) {
                if(ispalin(i, j)) ret += solve(j + 2, 1);
            }
        } else {
            ret += solve(i+1, p);
            if(ret >= mod) ret -= mod;
        }

        return ret;
    }

	int countStrings( string S ) {
        s = S;
        N = 2 * si(s) + 1;
        fo(i, si(s)) A[i] = s[i];
        A[si(s)] = '$';
        rep(i, si(s)) A[N+1+i] = s[si(s) - 1 - i]; 
        A[N] = 0;
        build();
        ini(dp, -1);

        return solve(0, 0);
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
			string S                  = "AAA";
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "ABCDEF";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "BBAA";
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "ABCBA";
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "TOPPAPPOT";
			int expected__            = 240;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S                  = "AYUEOPPOLAKIKIKIUYOPZOOLPPPPKMOPOLIURKMQOAPLFKTURIWOOWWWPLOLWWWOPSLAA";
			int expected__            = 216072426;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string S                  = "Z";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ConsecutivePalindromes().countStrings(S);
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
