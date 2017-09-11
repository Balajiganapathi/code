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

class EllysRollerCoasters {
public:
    int n, m, si, sj;
    vector<string> cr, cf;

    bool ok(int i, int j) {
        int di = 0, dj = 0;
        if(cr[i][j] == '-') dj = 1;
        else if(cr[i][j] == '|') di = 1;
        else if(cf[i][j] == 'U') di = 1;
        else if(cf[i][j] == 'D') di = -1;
        else if(cf[i][j] == 'L') dj = 1;
        else dj = -1;
        trace(i, j);

        int ci = i, cj = j;
        trace(ci, cj, di, dj);

        bool is_left(char r, char f) {
            if(f == '.' || r == '.') return false;
            return r == '-' || f == 'L' || (r == '/' && f == 'U') || (r == '\\' && f == 'D');
        }

        bool is_right(char r, char f) {
            if(f == '.' || r == '.') return false;
            return r == '-' || f == 'R' || (r == '\\' && f == 'U') || (r == '/' && f == 'D');
        }

        bool is_top(char r, char f) {
            if(f == '.' || r == '.') return false;
            return r == '|' || f == 'U' || (r == '/' && f == 'L') || (r == '\\' && f == 'R');
        }

        bool is_bottom(char r, char f) {
            if(f == '.' || r == '.') return false;
            return r == '|' || f == 'D' || (r == '\\' && f == 'L') || (r == '/' && f == 'R');
        }


        fo(iter, n * m + 2) {
            if(ci < 0 || ci >= n || cj < 0 || cj >= m) return false;
            trace(ci, cj, cr[ci][cj], cf[ci][cj]);
            if(cr[ci][cj] == '|') {
                if(di == 0) return false;
                ci += di; cj += dj;
            } else if(cr[ci][cj] == '-') {
                if(dj == 0) return false;
                ci += di; cj += dj;
            } else if(cf[ci][cj] == 'U') {
                if(di == 0 || di == -1) return false;
                if(cr[ci][cj] == '/') di = 0, dj = -1;
                else di = 0, dj = 1;
                ci += di; cj += dj;
            } else if(cf[ci][cj] == 'D') {
                if(di == 0 || di == 1) return false;
                if(cr[ci][cj] == '/') di = 0, dj = 1;
                else di = 0, dj = -1;
                ci += di; cj += dj;
            } else if(cf[ci][cj] == 'L') {
                if(dj == -1 || dj == 0) return false;
                if(cr[ci][cj] == '/') di = -1, dj = 0;
                else di = 1, dj = 0;
                ci += di; cj += dj;
            } else if(cf[ci][cj] == 'R') {
                if(dj == 1 || dj == 0) return false;
                if(cr[ci][cj] == '/') di = 1, dj = 0;
                else di = -1, dj = 0;
                ci += di; cj += dj;
            }
            trace(ci, cj, di, dj);
            if(si == ci && sj == cj) return true;
        }

        return false;
    }
	vector <string> getPlan( vector <string> field ) {
		vector <string> ret;
        ret = field;
        n = si(ret); m = si(ret[0]);

        bool notok = false;
        fo(i, n) fo(j, m) {
            if(ret[i][j] == '.') continue;
            char top = '.', ftop = '.';
            if(i > 0) top = ret[i-1][j], ftop = field[i-1][j];
            char left = '.', fleft = '.';
            if(j > 0) left = ret[i][j-1], fleft = field[i][j-1];

            char& cur = ret[i][j];

            if(cur == 'S') {
                if(is_bottom(top, ftop) || !is_right(left, fleft)) cur = '|';
                else cur = '-';
            } else if(cur == 'U') {
                if(is_right(left, fleft)) cur = '/';
                else cur = '\\';
            } else if(cur == 'D') {
                if(is_right(left, fleft)) cur = '\\';
                else cur = '/';
            } else if(cur == 'L') {
                if(is_bottom(top, ftop)) cur = '/';
                else cur = '\\';
            } else if(cur == 'R') {
                if(is_bottom(top, ftop)) cur = '\\';
                else cur = '/';
            }
        }

        trace(ret, field);
        cr = ret; cf = field;
        fo(i, n) fo(j, m) if(ret[i][j] != '.') {
            si = i; sj = j;
            bool o = ok(si, sj);
            trace(si, sj, o);
            if(!o) {
                notok = true;
                break;
            }
        }

        trace(notok);
        if(notok) return vector<string>();
		
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
	template<> std::ostream& operator<<(std::ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, std::clock_t elapsed) { 
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
			string field[]            = {"RSSLRD",
 "SDDSSS",
 "SULUUS",
 "ULRLDL",
 "RLSSRL",
 "SDUSDL",
 "SRSLRD",
 "RSSSSL"};
			string expected__[]       = {"/--\\/\\", "|/\\|||", "|\\/\\/|", "\\\\/\\//", "//||\\\\", "|//|//", "|\\-/\\\\", "\\----/" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string field[]            = {"RDL",
 "RLL"};
			string expected__[]       = { };

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string field[]            = {"DSSSSLDSSSDRSSSDDSSDDSSDRDRSSSD",
 "USLRSUSDSSUSDSLSUSDSSDLSSSRSSDS",
 "..SS..SS...SS.SSRSUSSSSSSS...SS",
 "..SS..SS...SS.SSSDSUSSSSSS...SS",
 "..SS..SS...SS.SSSRSDSULSSS...SS",
 "..SS..SS...SS.SSUSSUUSSUUL...UL",
 "..SS..SRSSDSRSLSDSSSSSSSSSSSSSL",
 "..RU..RSSSURSSSURSSSSSSSSSSSSSU"};
			string expected__[]       = {"/----\\/---\\/---\\/--\\/--\\/\\/---\\", "\\-\\/-/|/--/|/-\\|\\-\\||/\\|||\\--\\|", "..||..||...||.||/-/|||||||...||", "..||..||...||.|||/-/||||||...||", "..||..||...||.|||\\-\\|\\/|||...||", "..||..||...||.||\\--/\\--/\\/...\\/", "..||..|\\--\\|\\-/|/-------------\\", "..\\/..\\---/\\---/\\-------------/" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string field[]            = {"DD.RSSSL.....DSSLRL.DSSLRL..RLDSD.DSSSSSSD",
 "SUSU...UDDSSLRSSLSS.UL.RUUSSURU.UDS.DSD.DU",
 "SRSL.RSSLUL.RDRD.RU..USD.RSSSLRSLSUSLRU.S.",
 "SS.RSU.DDRL..SSSDLDSSSDRDRL.RUS.RU.RDULRL.",
 "SRSDRSSUSS.DSURURLRD..UDULRSU.S.RSSLSRLRD.",
 "SRLSUD..UL.RLDSDDL.RD..SRLRL..S.S.DSUS..RD",
 "SSSS.S.RSSLDURLSUUDLUL.UU.RUDSL.SDU..S.RLS",
 "RUSS.S.S.DLSDDRL..RU.UD..RSSU.DLULRD.ULULS",
 "DSLS.RDRSLRLUURLRL.RDRLRDSDD..RURSURL.S..S",
 "S.RLRLUD.RURL.RURU.SUUDLSSUU.DD.S.DSL.USSL",
 "RSU.SS.S.S.RU.DSD..RL.RDSUSSSLRSU.S.DLDL..",
 "DSSSLRSL.S..DSU.RDDLRDDLS....RD...USLUURSD",
 "RLDSSSLRSUDDS.DSDSSSRLRDUSSLDLUSSSSL.DL..S",
 ".SSDDDUS..SSS.RDSULSRSLS.DDSRSDDLRLRDSUSSL",
 ".RURLUDSRLRLRSDUURLRSLSS.RLRL.SRLRU.UL.DSL",
 "RSSL.RUSSSRD..RSDRU.DLSS..RDULS.DSSDDL.USU",
 "SDLRSL.UUSSSRD.DUDDDU.RU.RUUDULRUDDRLS.RSL",
 "ULSDSSLRSURLRU.SRUUURSSSSL..S..S.SSRSU.ULS",
 ".RURDRUUL..RSDDLS..RUDSSSSL.RD.S.RUUSDRDSS",
 ".RSSUS..UL.S.RU.RL.UDRSSSSLDLUSUDSSSSLRUUU",
 "RL..RLRSLS.RSD.RSURDRSSSDDSUUSSSLRSSDDL.RD",
 "SRSLSRLRLSDL.S.RL.RLRLDSUUD..RL..RSSLSS.UU",
 "RSLULUSLRLRL.SDLSRSSUSUSSSU.DUS.DSD.RURL..",
 ".RLDSDRLRSLRDSUUSUL..RSSSSSSL.UDUDRLRSDUSL",
 ".RSU.SULRSUSSS.DL.S.DSSSD.RL..RL.SDUDDULDL",
 "RSSLRURDRD.RUSRUDLRSL.RDULUURSU.DUS.UL.SS.",
 "USSUSDUS.S.RDSRDSUD.RDUL.SRLS...SRLDD..SUL",
 ".RSSURLS.RLSSRSUUSL.SS...SULRL..RUDLSDLS.S",
 ".SDDDSUS.DLUU..DD..RURSSSUDSSURSSLRSUSULRU",
 ".SSSRSDRDS.RSD.UURLSRD.DSLRLRLS.RU.DSU.RL.",
 "RUSRSSLDURLULUL..SSSSUSL.S.SUUUSLRDUSL.SDD",
 "RSL..RLRD.UDS.S.RLRLUD.DDS.S.RSSSLUD.USURL",
 "DSSSDUL.S..SRDSDU....SDLRL.SDL..DSDUSSSSSL",
 "UDDSU.RDRSDSRUSRSD.DLSS.DL.ULRSLS.RLRSD.DL",
 ".UU.RLULDLRURSUDLS.RLUL.SS...SDURL.RLDU.S.",
 "RDDDSSDDSUSLDSLSSS...RSSLUSDDUS..S.DDRD.RL",
 "RUUURLULUSSLRSLUUUSSSL.....UL.USSL.UL.USSU"};
			string expected__[]       = {"/\\./---\\...../--\\/\\./--\\/\\../\\/-\\./------\\", "|\\-/...\\\\/--\\\\--/||.\\\\.\\/\\--/\\/.\\\\|./-\\.//", "|/-\\./--/\\\\.\\\\/\\.\\/..\\-\\./---\\/-\\|\\-///.|.", "||.\\-/./\\//..|||/\\/---\\\\\\\\\\.//|.\\/./\\\\\\//.", "|\\-\\/--/||./-/\\/\\/\\\\..\\\\\\\\\\-/.|./--/|//\\\\.", "|/\\|\\\\..\\/.\\\\/-\\/\\.\\\\..|///\\..|.|./-/|..\\\\", "||||.|./--\\//\\\\|\\//\\\\\\.\\/.\\//-/.|//..|./\\|", "\\/||.|.|.//|/\\\\/..\\/.\\\\../--/./\\\\//\\.\\\\\\/|", "/-/|.\\\\\\-///\\//\\/\\./\\///\\|/\\..\\//-/\\\\.|..|", "|.///\\\\\\.///\\.\\/\\/.|\\///||\\/./\\.|./-/.\\--/", "\\-/.||.|.|.\\/./-\\..\\\\.\\\\|\\---/\\-/.|./\\/\\..", "/---/\\-/.|../-/.\\\\/\\\\\\//|..../\\...\\-/\\/\\-\\", "\\\\/---\\/-//\\|./-\\|||//\\\\\\--\\//\\----\\./\\..|", ".||/\\//|..|||.\\\\|\\/|\\-\\|./\\|\\-\\/\\/\\\\\\|\\--/", ".\\/\\/\\\\|/\\\\/\\-\\\\//\\\\-\\||.\\/\\\\.|\\/\\/.\\/./-\\", "/--\\.//|||/\\..\\-\\\\/.//||../\\\\\\|./--\\/\\.\\-/", "|/\\\\-/.\\/|||/\\.///\\//.\\/.//\\\\\\////\\\\/|./-\\", "\\/|/--\\/-/\\/\\/.|//\\//----/..|..|.||/-/.\\\\|", ".//\\\\//\\\\../-\\//|..///----\\.\\\\.|.\\/\\-\\/\\||", ".\\--/|..\\\\.|.\\/.\\\\.\\\\\\----//\\\\-//----/\\/\\/", "/\\..///-\\|.\\-\\./-//\\\\---\\/-/\\---//--\\/\\./\\", "|\\-\\|////|/\\.|.\\\\.\\//\\/-/\\\\../\\..\\--/||.\\/", "\\-\\\\/\\-///\\/.|/\\|/--/|\\---/.//|./-\\.//\\\\..", ".///-\\/\\\\-\\/\\|\\/|\\\\..\\------/.\\\\\\\\\\\\\\-\\\\-\\", ".\\-/.|\\//-/|||.//.|./---\\./\\..//.|///\\\\\\//", "/--\\///\\\\\\.\\/|///\\\\-/./\\\\\\\\//-/.//|.\\/.||.", "\\--/|//|.|./\\|\\\\|\\\\./\\\\/.|/\\|...|///\\..|\\\\", "./--/\\\\|.\\\\||\\-/\\-/.||...|\\/\\\\..\\///|/\\|.|", ".|/\\/-/|.//\\/../\\..//\\---//--//--\\\\-/|\\///", ".|||\\-\\\\\\|./-\\.\\//\\|/\\./-\\\\\\/\\|.//./-/.//.", "//|\\--///\\\\\\\\\\\\..||||\\-/.|.|\\/\\-//\\\\-\\.|/\\", "\\-/../\\\\\\.\\\\|.|.//\\/\\\\./\\|.|./---/\\\\.\\-/\\/", "/---\\\\/.|..|\\\\|//....|//\\/.|//../-\\\\-----\\", "\\\\/-/./\\\\-\\|//|\\-\\./\\||./\\.\\//-\\|.\\\\/-\\.//", ".\\/./\\\\//\\\\/\\-//\\|.\\/\\/.||...|//\\\\.\\///.|.", "/\\/\\||/\\|\\-\\/-\\|||.../--/\\-\\//|..|./\\\\\\.\\\\", "\\/\\/\\/\\/\\--/\\-/\\/\\---/.....\\/.\\--/.\\/.\\--/" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 4: {
			string field[]            = {"RSD", "S.S", "USL"};
			string expected__[]       = {"/-\\", "|.|", "\\-/"};

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 5: {
			string field[]            = ;
			string expected__[]       = ;

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string field[]            = ;
			string expected__[]       = ;

			std::clock_t start__      = std::clock();
			vector <string> received__ = EllysRollerCoasters().getPlan(vector <string>(field, field + (sizeof field / sizeof field[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
