/* string coder = "Balajiganapathi S"; // Never give up!  */
// Make a bit change to previous guess

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#else
#   define NDEBUG
//#   define FAST
#endif

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
    
/* util functions */
template<typename T1, typename T2, typename T3>
T1 modpow(T1 _a, T2 p, T3 mod) {
    assert(p >= 0);
    ll ret = 1, a = _a;

#ifndef FAST
    if(a < 0) {
        a %= mod;
        a += mod;
    } 

    if(a >= mod) {
        a %= mod;
    }
#endif

    for(; p > 0; p /= 2) {
        if(p & 1) ret = ret * a % mod;
        a = a * a % mod;
    }

    return ret;
}

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
constexpr int mx_n = 5003;
int n = 5000, k = 2000, x = 100;
unordered_map<string, int> attempts;

int testIt(string answers) {
    assert(si(attempts) < x);
    fo(i, n) {
        assert(answers[i] == '0' || answers[i] == '1');
    }
    int &ret = attempts[answers];
    if(ret) return ret;

    cout << answers << endl;
    cin >> ret;

    if(ret == n + 1) {
        exit(0);
    }
    return ret;
}

inline char opposite(const char &c) {
    return (c == '0')? '1': '0';
}

string genRandom() {
    string guess;
    fo(i, n) guess += '0' + rand() % 2;
    for(const auto &entry: attempts) {
        guess[entry.se-1] = opposite(entry.fi[entry.se-1]);
    }

    return guess;
}

long double expectedScore(int from, int c) {
    return from + 2 * c;
}

int fix[mx_n];
void small_diff() {
    string guess = genRandom();
    int score = testIt(guess);
    long double exp_score = expectedScore(score, 2);
    int pos = 0;
    while(si(attempts) < x) {
        int last_score = score;
        guess[pos] = opposite(guess[pos]);
        guess[score-1] = opposite(guess[score-1]);
        fix[score-1] = 1;
        score = testIt(guess);
        if(score < exp_score + eps) {
            guess[pos] = opposite(guess[pos]);
            exp_score = expectedScore(last_score, 2);
        } else {
            exp_score = expectedScore(score, 1);
        }
        fix[pos] = 1;
        ++pos;
    }
}

vector<tuple<int, int, int>> blocks;
void gen_block(int a, int b) {
    blocks.push_back(mt(b - a + 1, a, b));
    if(a == b) return;

    int m = (a + b) / 2;
    gen_block(a, m);
    gen_block(m + 1, b);
}

string do_reverse(string guess, int a, int b) {
    string ret = guess;
    rep(i, a, b) ret[i] = opposite(ret[i]);

    return ret;
}

void block_diff() {
    string guess = genRandom();
    int score = testIt(guess);
    gen_block(0, score - 1);
    sort(all(blocks));
    reverse(all(blocks));

    int best_score = score;
    fo(i, min(si(blocks), x - 2)) {
        string new_guess = do_reverse(guess, gt(blocks[i], 1), gt(blocks[i], 2));
        score = testIt(new_guess);
        if(score > best_score) {
            best_score = score;
            guess = new_guess;
        }
    }

    for(const auto &entry: attempts) {
        int pos = entry.se - 1;
        guess[pos] = opposite(guess[pos]);
    }
    testIt(guess);
}

int main() {
    ini(fix, 0);
    block_diff();
    
	return 0;
}
