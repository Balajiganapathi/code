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

class FairWorkload {
public:
	int getMostWork( vector <int> folders, int workers ) {
        int lo = *max_element(all(folders));
        int hi = accumulate(all(folders), 0);

        while(lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int tot = 1, cur = 0;
            fo(i, si(folders)) {
                if(cur + folders[i] > mid) {
                    cur = folders[i];
                    ++tot;
                } else {
                    cur += folders[i];
                }
            }
            if(tot <= workers) hi = mid;
            else lo = mid + 1;
        }

        return lo;
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
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
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
			int folders[]             = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
			int workers               = 3;
			int expected__            = 170;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int folders[]             = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
			int workers               = 5;
			int expected__            = 110;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int folders[]             = { 568, 712, 412, 231, 241, 393, 865, 287, 128, 457, 238, 98, 980, 23, 782 };
			int workers               = 4;
			int expected__            = 1785;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int folders[]             = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1000 };
			int workers               = 2;
			int expected__            = 1000;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int folders[]             = { 50, 50, 50, 50, 50, 50, 50 };
			int workers               = 2;
			int expected__            = 200;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int folders[]             = {1,1,1,1,100};
			int workers               = 5;
			int expected__            = 100;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int folders[]             = { 950, 650, 250, 250, 350, 100, 650, 150, 150, 700 };
			int workers               = 6;
			int expected__            = 950;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int folders[]             = ;
			int workers               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int folders[]             = ;
			int workers               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int folders[]             = ;
			int workers               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FairWorkload().getMostWork(vector <int>(folders, folders + (sizeof folders / sizeof folders[0])), workers);
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
