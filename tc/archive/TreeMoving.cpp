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
constexpr int mx_n = 303;
constexpr int mx_mat = 512;
int mt[mx_n][mx_mat][mx_mat];
pi edges[mx_n][mx_n];
int rt[mx_n];

#define M 2
#define N (1<<M)
 
typedef int datatype;
#define DATATYPE_FORMAT "%4.2g"
typedef datatype mat[N][N]; // mat[2**M,2**M]  for divide and conquer mult.
typedef struct
{
        int ra, rb, ca, cb;
} corners; // for tracking rows and columns.
// A[ra..rb][ca..cb] .. the 4 corners of a matrix.
 
// set A[a] = I
void identity(mat A, corners a)
{
    int i, j;
    for (i = a.ra; i < a.rb; i++)
        for (j = a.ca; j < a.cb; j++)
            A[i][j] = (datatype) (i == j);
}
 
// set A[a] = k
void set(mat A, corners a, datatype k)
{
    int i, j;
    for (i = a.ra; i < a.rb; i++)
        for (j = a.ca; j < a.cb; j++)
            A[i][j] = k;
}
 
// set A[a] = [random(l..h)].
void randk(mat A, corners a, double l, double h)
{
    int i, j;
    for (i = a.ra; i < a.rb; i++)
        for (j = a.ca; j < a.cb; j++)
            A[i][j] = (datatype) (l + (h - l) * (rand() / (double) RAND_MAX));
}
 
// Print A[a]
void print(mat A, corners a, char *name)
{
    int i, j;
    printf("%s = {\n", name);
    for (i = a.ra; i < a.rb; i++)
    {
        for (j = a.ca; j < a.cb; j++)
            printf(DATATYPE_FORMAT ", ", A[i][j]);
        printf("\n");
    }
    printf("}\n");
}
 
// C[c] = A[a] + B[b]
void add(mat A, mat B, mat C, corners a, corners b, corners c)
{
    int rd = a.rb - a.ra;
    int cd = a.cb - a.ca;
    int i, j;
    for (i = 0; i < rd; i++)
    {
        for (j = 0; j < cd; j++)
        {
            C[i + c.ra][j + c.ca] = (A[i + a.ra][j + a.ca] + B[i + b.ra][j
                    + b.ca]) % mod;
        }
    }
}
 
// C[c] = A[a] - B[b]
void sub(mat A, mat B, mat C, corners a, corners b, corners c)
{
    int rd = a.rb - a.ra;
    int cd = a.cb - a.ca;
    int i, j;
    for (i = 0; i < rd; i++)
    {
        for (j = 0; j < cd; j++)
        {
            C[i + c.ra][j + c.ca] = (A[i + a.ra][j + a.ca] - B[i + b.ra][j
                    + b.ca] + mod) % mod;
        }
    }
}
 
// Return 1/4 of the matrix: top/bottom , left/right.
void find_corner(corners a, int i, int j, corners *b)
{
    int rm = a.ra + (a.rb - a.ra) / 2;
    int cm = a.ca + (a.cb - a.ca) / 2;
    *b = a;
    if (i == 0)
        b->rb = rm; // top rows
    else
        b->ra = rm; // bot rows
    if (j == 0)
        b->cb = cm; // left cols
    else
        b->ca = cm; // right cols
}
 
// Multiply: A[a] * B[b] => C[c], recursively.
void mul(mat A, mat B, mat C, corners a, corners b, corners c)
{
    corners aii[2][2], bii[2][2], cii[2][2], p;
    mat P[7], S, T;
    int i, j, m, n, k;
 
    // Check: A[m n] * B[n k] = C[m k]
    m = a.rb - a.ra;
    assert(m==(c.rb-c.ra));
    n = a.cb - a.ca;
    assert(n==(b.rb-b.ra));
    k = b.cb - b.ca;
    assert(k==(c.cb-c.ca));
    assert(m>0);
 
    if (n == 1)
    {
        C[c.ra][c.ca] += A[a.ra][a.ca] * B[b.ra][b.ca];
        return;
    }
 
    // Create the 12 smaller matrix indexes:
    //  A00 A01   B00 B01   C00 C01
    //  A10 A11   B10 B11   C10 C11
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            find_corner(a, i, j, &aii[i][j]);
            find_corner(b, i, j, &bii[i][j]);
            find_corner(c, i, j, &cii[i][j]);
        }
    }
 
    p.ra = p.ca = 0;
    p.rb = p.cb = m / 2;
 
#define LEN(A) (sizeof(A)/sizeof(A[0]))
    for (i = 0; i < LEN(P); i++)
        set(P[i], p, 0);
 
#define ST0 set(S,p,0); set(T,p,0)
 
    // (A00 + A11) * (B00+B11) = S * T = P0
    ST0;
    add(A, A, S, aii[0][0], aii[1][1], p);
    add(B, B, T, bii[0][0], bii[1][1], p);
    mul(S, T, P[0], p, p, p);
 
    // (A10 + A11) * B00 = S * B00 = P1
    ST0;
    add(A, A, S, aii[1][0], aii[1][1], p);
    mul(S, B, P[1], p, bii[0][0], p);
 
    // A00 * (B01 - B11) = A00 * T = P2
    ST0;
    sub(B, B, T, bii[0][1], bii[1][1], p);
    mul(A, T, P[2], aii[0][0], p, p);
 
    // A11 * (B10 - B00) = A11 * T = P3
    ST0;
    sub(B, B, T, bii[1][0], bii[0][0], p);
    mul(A, T, P[3], aii[1][1], p, p);
 
    // (A00 + A01) * B11 = S * B11 = P4
    ST0;
    add(A, A, S, aii[0][0], aii[0][1], p);
    mul(S, B, P[4], p, bii[1][1], p);
 
    // (A10 - A00) * (B00 + B01) = S * T = P5
    ST0;
    sub(A, A, S, aii[1][0], aii[0][0], p);
    add(B, B, T, bii[0][0], bii[0][1], p);
    mul(S, T, P[5], p, p, p);
 
    // (A01 - A11) * (B10 + B11) = S * T = P6
    ST0;
    sub(A, A, S, aii[0][1], aii[1][1], p);
    add(B, B, T, bii[1][0], bii[1][1], p);
    mul(S, T, P[6], p, p, p);
 
    // P0 + P3 - P4 + P6 = S - P4 + P6 = T + P6 = C00
    add(P[0], P[3], S, p, p, p);
    sub(S, P[4], T, p, p, p);
    add(T, P[6], C, p, p, cii[0][0]);
 
    // P2 + P4 = C01
    add(P[2], P[4], C, p, p, cii[0][1]);
 
    // P1 + P3 = C10
    add(P[1], P[3], C, p, p, cii[1][0]);
 
    // P0 + P2 - P1 + P5 = S - P1 + P5 = T + P5 = C11
    add(P[0], P[2], S, p, p, p);
    sub(S, P[1], T, p, p, p);
    add(T, P[5], C, p, p, cii[1][1]);
}

mat res[2];
int idx;
void multiply(int idx, int i) {
    corners ai = { 0, N, 0, N };
    corners bi = { 0, N, 0, N };
    corners ci = { 0, N, 0, N };
    mul(res[idx], mat[i], mat[1-idx]);
    idx = 1-idx;
}
 

class TreeMoving {
public:
    int n, m;

    void init() {
        fo(i, mx_n) rt[i] = i;
    }

    int find(int x) {
        return rt[x] == x? x: (rt[x] = find(rt[x]));
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void merge(int a, int b) {
        int ra = find(a), rb = find(b);
        if(ra == rb) return;
        if(rand() % 2) rt[ra] = rb;
        else rt[rb] = ra;
    }

	int count( int _n, vector <int> roots, vector <int> a, vector <int> b, vector <int> c ) {
		int ret = 0;
        n = _n;
        m = si(roots);
        fo(i, m) {
            vi X(n);
            X[0] = c[i];
            re(k, 1, n - 1) {
                X[k] = (1ll * a[i] * X[k-1] + b[i]) % mod;
            }

            fo(j, n - 1) {
                int u = (roots[i] + j + 1) % n;
                int v = (roots[i] + (X[j] % (j+1))) % n;
                edges[i][j] = mp(u, v);
                trace(i, j, edges[i][j]);
            }

        }

        ini(mt, 0);
        fo(i, m) {
            int j = (i + 1) % m;
            fo(k, n - 1) {
                init();
                fo(l, n - 1) if(l != k) merge(edges[j][l].fi, edges[j][l].se);
                fo(l, n - 1) if(!same(edges[i][l].fi, edges[i][l].se)) {
                    mt[i][k][l] = 1;
                }
            }
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
			int n                     = 3;
			int roots[]               = {0, 2};
			int a[]                   = {1, 2};
			int b[]                   = {1, 0};
			int c[]                   = {2, 3};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int roots[]               = {0, 0, 1};
			int a[]                   = {6, 1, 3};
			int b[]                   = {6, 5, 5};
			int c[]                   = {2, 5, 9};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 5;
			int roots[]               = {0, 1, 1, 1, 2};
			int a[]                   = {7, 4, 7, 9, 2};
			int b[]                   = {8, 3, 9, 5, 3};
			int c[]                   = {6, 0, 1, 5, 9};
			int expected__            = 22;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 3;
			int roots[]               = {0, 0, 1};
			int a[]                   = {373206610, 937739946, 172315864};
			int b[]                   = {870770575, 635025870, 765158489};
			int c[]                   = {915938656, 747443899, 387215442};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 10;
			int roots[]               = {0, 1, 0, 4, 0, 2, 1, 8, 5, 5};
			int a[]                   = {508821715, 481198414, 163209181, 56649169, 276327522, 13486359, 845629232, 482370937, 373100199, 297431939};
			int b[]                   = {256979012, 884002808, 393825387, 609998779, 816536931, 123064634, 673095376, 18224901, 510687925, 466437174};
			int c[]                   = {368733721, 596826005, 853637399, 436680590, 369153650, 853574577, 609377415, 903050702, 259325966, 105275092};
			int expected__            = 17765;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int n                     = ;
			int roots[]               = ;
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int roots[]               = ;
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int roots[]               = ;
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TreeMoving().count(n, vector <int>(roots, roots + (sizeof roots / sizeof roots[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
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
