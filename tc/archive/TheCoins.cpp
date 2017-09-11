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

class TheCoins {
public:
	long long find( int n, int m, int dr, int dc, vector <int> row, vector <int> column ) {
		long long ret;
		
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
			int n                     = 3;
			int m                     = 3;
			int dr                    = 1;
			int dc                    = 1;
			int row[]                 = {};
			int column[]              = {};
			long long expected__      = 6;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 5;
			int m                     = 4;
			int dr                    = 2;
			int dc                    = 1;
			int row[]                 = {3, 3};
			int column[]              = {2, 3};
			long long expected__      = 10;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 100;
			int m                     = 100;
			int dr                    = 4;
			int dc                    = 7;
			int row[]                 = {};
			int column[]              = {};
			long long expected__      = 9520;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 2;
			int m                     = 2;
			int dr                    = 1;
			int dc                    = 1;
			int row[]                 = {1, 2};
			int column[]              = {2, 1};
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 5;
			int m                     = 4;
			int dr                    = 1;
			int dc                    = 1;
			int row[]                 = {2, 4, 3, 5, 2, 2, 5, 4};
			int column[]              = {2, 2, 2, 2, 3, 4, 4, 4};
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 84;
			int m                     = 71;
			int dr                    = 74;
			int dc                    = 22;
			int row[]                 = {50, 47, 11, 57, 12, 58, 16, 5, 77, 26, 71, 45, 53, 70, 3, 50, 65, 11, 44, 58, 59, 12, 30, 78, 12, 19, 48, 53, 19, 71, 52, 77, 73, 33, 63, 73, 55, 10, 14, 66, 67, 46, 34, 60, 71, 12, 83, 18};
			int column[]              = {27, 50, 59, 37, 6, 26, 41, 67, 68, 70, 12, 3, 1, 62, 25, 70, 46, 48, 26, 5, 16, 62, 44, 39, 60, 19, 47, 32, 50, 21, 14, 38, 13, 58, 37, 70, 10, 70, 5, 6, 1, 54, 52, 9, 69, 49, 41, 58};
			long long expected__      = 970;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int n                     = 122677;
			int m                     = 996231;
			int dr                    = 41759;
			int dc                    = 481285;
			int row[]                 = {25581, 10405, 37052, 85448, 62794, 103890, 75143, 34652, 96573, 107497, 49592, 117281, 4466, 44553, 9760, 62266, 122175, 84237, 86788, 38864, 83124, 108358, 98854, 103177, 86381, 11519, 61147, 33170, 11043, 17402, 107658, 71673, 102550, 70823, 20568, 81613, 83067, 72136, 34569, 6513, 24505, 112416, 75208, 4463, 86507, 86558, 45844, 53233, 87815, 50610};
			int column[]              = {275695, 51848, 173581, 533376, 882202, 994201, 319894, 128485, 370593, 1655, 185488, 955779, 731743, 729992, 641079, 530134, 332977, 289273, 779908, 528428, 700671, 509104, 364078, 429286, 105101, 851418, 592063, 198998, 745550, 128128, 905177, 806990, 929477, 82009, 432238, 549661, 939922, 740977, 372638, 67868, 525232, 289171, 493261, 178561, 208168, 960711, 584970, 920830, 607658, 270535};
			long long expected__      = 80700538590LL;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int n                     = ;
			int m                     = ;
			int dr                    = ;
			int dc                    = ;
			int row[]                 = ;
			int column[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int m                     = ;
			int dr                    = ;
			int dc                    = ;
			int row[]                 = ;
			int column[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int n                     = ;
			int m                     = ;
			int dr                    = ;
			int dc                    = ;
			int row[]                 = ;
			int column[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = TheCoins().find(n, m, dr, dc, vector <int>(row, row + (sizeof row / sizeof row[0])), vector <int>(column, column + (sizeof column / sizeof column[0])));
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
