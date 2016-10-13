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
constexpr int mx_n = 10000008;
unordered_set<ll> luckySet;
vector<ll> lucky;

class TheLuckyBasesDivOne {
public:
    void rec(ll num, int digs) {
        if(num > 0) {
            luckySet.insert(num);
        }
        if(digs < 16) {
            rec(10 * num + 4, digs + 1);
            rec(10 * num + 7, digs + 1);
        }
    }

    void pre() {
        rec(0, 0);
        lucky = vector<ll>(all(luckySet));
        sort(all(lucky));
    }

    bool isLuckyBase(ll n, ll b) {
        for(; n > 0; n /= b) {
            ll cur = n % b;
            if(!luckySet.count(cur)) return false;
        }

        return true;
    }

    bool isok(ll x, ll y, ll z, ll n) {
        ll lo = max(x + 1, max(y + 1, z + 1));
        ll hi = min(ll(sqrt(n / x) + 2), n / y);
        while(lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            ll cur = mid * mid * x + mid * y + z;
            if(cur <= n) lo = mid;
            else hi = mid - 1;
        }

        ll cur = lo * lo * x + lo * y + z;
        return cur == n;
    }

	long long find( long long n ) {
		long long ret = 0;
        pre();

        if(luckySet.count(n)) return -1;

        for(ll b = 5; b * b * b <= n; ++b) if(isLuckyBase(n, b)) ++ret;

        int tot = si(lucky);

        fo(i, tot) {
            ll x = lucky[i];
            ll minb1 = x + 1;
            if(minb1  * x > n) break;
            fo(j, tot) {
                ll y = lucky[j];
                ll minb2 = max(minb1, y + 1);
                if(minb2 * x + y > n) break;
                if((n - y) % x == 0) {
                    ll b = (n - y) / x;
                    //trace(b, x, y, b * x + y, n);
                    if(b >= minb2) ++ret;
                }
            }
        }

        fo(i, tot) {
            ll x = lucky[i];
            ll minb1 = x + 1;
            if(minb1 * minb1 * x > n) break;
            fo(j, tot) {
                ll y = lucky[j];
                ll minb2 = max(minb1, y + 1);
                if(minb2 * minb2 * x + minb2 * y > n) break;
                fo(k, tot) {
                    ll z = lucky[k];
                    ll minb3 = max(minb2, z + 1);
                    if(minb3 * minb3 * x + minb3 * y + z > n) break;
                    if(isok(x, y, z, n)) ++ret;
                }
            }
        }

        
		
		return ret;
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
			long long n               = 255;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long n               = 474;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long n               = 13;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long n               = 4748;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			long long n               = 10000000000000000L;
			long long expected__      = 28302;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			long long n               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long n               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
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
