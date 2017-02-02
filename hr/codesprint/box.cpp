/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#   define TEST
#   define CHECK
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
    return os << "("; print_tuple<0>(os, tup); return os << ")"; } 
template <typename T1, typename T2>
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
constexpr auto oo  = numeric_limits<ll>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 100005;
constexpr int mx_nb = 330;
constexpr int mx_bs = 330;

int n;
int box[mx_n];
constexpr ll LIMIT = oo / 10;


inline int flr(int x, ll d) {
    if(x >= 0) return x / d;
    return -1 * (-x + d - 1) / d;
}

inline ll mul(ll a, ll b) {
    if(a <= LIMIT / b) return a * b;
    return LIMIT;
}


class Machine {
    static constexpr int CYCLE_LIMIT = 10000;
public:
    ll pending, cycle;
    constexpr Machine(): pending(1), cycle(1) { }
    Machine(ll p, ll c): pending(p), cycle(c) {
        assert(pending > 0 && cycle > 0);
    }
    bool isLow() {
        return true;
        //return cycle <= CYCLE_LIMIT;
    }

    int add(int x) {
        //if(cycle == LIMIT) return 0;
        ll ret = 0;

        if(x >= 0) {
            if(pending >= LIMIT / 2) return ret;
            if(x < pending) {
                pending -= x;
            } else {
                x -= pending;
                int times = x / cycle;
                ret += times + 1;
                pending = cycle - (x - cycle * times);
            }
        } else {
            x = abs(x);
            ll cp = cycle - pending;
            if(cp >= LIMIT / 2) return ret;
            if(x < cp) {
                pending += x;
            } else {
                if(cycle != pending) {
                    x -= cp;
                    pending = 0;
                    --ret;
                }
                ret -= x / cycle;
                pending = x % cycle;
                if(pending) --ret;
            }
        }
        if(pending == 0) pending = cycle;

        return ret;
    }

    ll needFor(ll x) {
        assert(pending > 0);
        if(x == 0) return 0;
        if(x > 0) {
            return min(pending + mul(x - 1, cycle), LIMIT);
        } else {
            if(cycle == pending) return mul(x, cycle);
            return min((cycle - pending) + mul(x - 1, cycle), LIMIT);
        }
    }

    ll next() {
        if(cycle == LIMIT) return oo;
        return pending;
    }

    ll prev() {
        if(cycle == LIMIT) return -oo;
        return (cycle == pending? cycle: (cycle - pending));
    }

};
ostream& operator<<(ostream& os, const Machine& m) {
    return os << "{(" << m.pending << ", " << m.cycle << ")}";
}

class State {
public:
    int val;
    Machine m;
    constexpr State(): val(0) {}

    State(int v, Machine _m): m(_m) {
        val = m.add(v);
    }
    
    void add(int x) {
        Machine old = m;
        ll diff = m.add(x);
        //trace(old, m, diff);
        val += diff;
    }

    // (X + c) / d
    void apply(int c, ll d) {
        if(c == 0 && d == 1) return;
        Machine newM(d, d);
        apply(newM, c);
    }

    void apply(const Machine &newM, ll c) {
        //trace(val, m, newM, c);
        m = newM;
        val = m.add(c + val);
        //trace(val);
    }
};

ostream& operator<<(ostream& os, const State& s) {
    return os << "<" << s.val << ", " << s.m << ">";
}

class Event {
    public:
    ll at, idx;

    Event(int _at, int _idx) {
        at = _at; idx = _idx;
    }

    bool operator <(const Event &e) const {
        if(at != e.at) return at < e.at;
        return idx < e.idx;
    }
};

class Block {
public:
    ll cdiv;
    int csum;
    vector<State> boxes;
    ll sum;
    int siz;
    int mn;

    Block() {}

    void init(const vi &box) {
        cdiv = 1;
        sum = csum = 0;
        mn = INT_MAX;
        trace(box);
        trace(boxes);
        siz = si(box);
        boxes.reserve(siz);
        fo(i, siz) {
            trace(boxes, State(box[i], Machine()));
            boxes.push_back(State(box[i], Machine()));
        }
        trace(boxes);
        reduce(0, 1, siz, siz-1);
    }

    void reduce(int nc, int nd, int s, int e) {
        mn = INT_MAX;
        sum = 0;
        trace(nc, nd, s, e);
        fo(i, s) {
            boxes[i].apply(csum, cdiv);
            sum += boxes[i].val;
            mn = min(mn, boxes[i].val);
        }

        rep(i, s, e) {
            boxes[i].apply(csum, cdiv);
            boxes[i].val = flr(boxes[i].val + nc, nd);
            sum += boxes[i].val;
            mn = min(mn, boxes[i].val);
        }

        re(i, e + 1, siz) {
            boxes[i].apply(csum, cdiv);
            sum += boxes[i].val;
            mn = min(mn, boxes[i].val);
        }
        cdiv = 1;
        csum = 0;
    }

    int getMin() {
        return flr((mn + csum), cdiv);
    }

    ll getSum() {
        if(cdiv > 1) reduce(0, 1, siz, siz-1);
        return sum + si(boxes) * csum;
    }

    int getMin(int s, int e) {
        reduce(0, 1, siz, siz-1);
        int ret = INT_MAX;
        rep(i, s, e) ret = min(ret, boxes[i].val);
        return ret;
    }

    ll getSum(int s, int e) {
        reduce(0, 1, siz, siz-1);
        ll ret = 0;

        rep(i, s, e) ret += boxes[i].val;
        return ret;
    }

    void add(int c) {
        if(cdiv > 1) reduce(0, 1, siz, siz-1);
        csum += c;
    }

    void divide(int d) {
        cdiv = mul(d, cdiv);
    }

    void add(int s, int e, int c) {
        reduce(c, 1, s, e);
    }

    void divide(int s, int e, int d) {
        reduce(0, d, s, e);
    }

} blocks[mx_nb];
int nb, bs;
#ifdef TRACE
ostream& operator<<(ostream& os, const Block& b) {
    return os << "[csum = " << b.csum << "; sum = " << b.sum << "; mn = " << b.mn << "; cdiv = " << b.cdiv << "; boxes = " << b.boxes << "]";
}
#endif
void init() {
    bs = max(1, int(ceil(sqrt(n))));
    nb = (n + bs - 1) / bs;
    trace(n, bs, nb);

    vi cur;
    fo(i, n) {
        cur.push_back(box[i]);
        if(i % bs == bs - 1 || i == n - 1) {
            trace(i / bs, cur);
            blocks[i / bs].init(cur);
            cur.clear();
        }
    }

    //fo(i, nb) trace(i, blocks[i]);
}

class Span {
public:
    int bi, bj;
    int b1, s1, e1, b2, s2, e2;
    Span(int l, int r) {
        bi = bj = -1;
        b1 = b2 = -1;
        int bl = l / bs, br = r / bs;
        if(bl == br) {
            b1 = bl;
            s1 = l - b1 * bs; e1 = r - b1 * bs;
        } else {
            if(br > bl + 1) {
                bi = bl + 1; bj = br - 1;
            }
            b1 = bl;
            s1 = l - b1 * bs; e1 = bs - 1;
            b2 = br;
            s2 = 0; e2 = r - b2 * bs;
        }
    }
};

ostream& operator<<(ostream& os, const Span& s) {
    return os << "{<" << s.bi << "-" << s.bj << ">; " << s.b1 << "(" << s.s1 << "," << s.e1 << "); " << s.b2 << "(" << s.s2 << "," << s.e2 << ")}";
}

void add(int l, int r, int c) {
    Span s(l, r);
    if(s.bi != -1) {
        rep(i, s.bi, s.bj) {
            blocks[i].add(c);
            //trace(i, blocks[i]);
        }
    }
    if(s.b1 != -1) {
        blocks[s.b1].add(s.s1, s.e1, c);
        //trace(s.b1, s.s1, s.e1, blocks[s.b1]);
    }
    if(s.b2 != -1) {
        blocks[s.b2].add(s.s2, s.e2, c);
        //trace(s.b2, s.s2, s.e2, blocks[s.b2]);
    }
}

void divide(int l, int r, int d) {
    Span s(l, r);
    if(s.bi != -1) rep(i, s.bi, s.bj) blocks[i].divide(d);
    if(s.b1 != -1) blocks[s.b1].divide(s.s1, s.e1, d);
    if(s.b2 != -1) blocks[s.b2].divide(s.s2, s.e2, d);
}

int min_value(int l, int r) {
    int mn = INT_MAX;
    Span s(l, r);
    if(s.bi != -1) rep(i, s.bi, s.bj) mn = min(mn, blocks[i].getMin());
    if(s.b1 != -1) mn = min(mn, blocks[s.b1].getMin(s.s1, s.e1));
    if(s.b2 != -1) mn = min(mn, blocks[s.b2].getMin(s.s2, s.e2));

    return mn;
}

ll sum_value(int l, int r) {
    ll sum = 0;
    Span s(l, r);
    if(s.bi != -1) rep(i, s.bi, s.bj) sum += blocks[i].getSum();
    if(s.b1 != -1) sum += blocks[s.b1].getSum(s.s1, s.e1);
    if(s.b2 != -1) sum += blocks[s.b2].getSum(s.s2, s.e2);

    return sum;
}

ll brute_boxes[mx_n];

void brute_divide(int l, int r, int d) {
#ifdef CHECK
    rep(i, l, r) brute_boxes[i] = flr(brute_boxes[i], d);
#endif
}

void brute_add(int l, int r, int c) {
#ifdef CHECK
    rep(i, l, r) brute_boxes[i] += c;
#endif
}

ll brute_sum(int l, int r) {
    ll sum = 0;
    rep(i, l, r) sum += brute_boxes[i];
    return sum;
}

ll brute_min(int l, int r) {
    ll sum = oo;
    rep(i, l, r) sum = min(sum, 1ll * brute_boxes[i]);
    return sum;
}


int randRange(int a, int b) {
    return rand() % (b - a + 1) + a;
}

int main() {
    ios::sync_with_stdio(false);
    int q;
#ifdef TEST
    n = 100000; q = 100000;
#else
    cin >> n >> q;
    fo(i, n) cin >> box[i];
#endif
#ifdef CHECK
    fo(i, n) brute_boxes[i] = box[i];
#endif
    init();
    while(q--) {
        int t, l, r;
        ll c, d;
#ifdef TEST
        do {
            t = randRange(1, 4);
        } while(t == 0);
        l = randRange(0, n - 1); r = randRange(0, n - 1);
        if(l > r) swap(l, r);
        //if(t == 3) t = 4;
        //if(t == 4) l = 0, r = n-1;
#else
        cin >> t >> l >> r;
#endif
        //trace("----------------------------------------------------");
        ll ans, bans;
        switch(t) {
            case 1:
#ifdef TEST
                c = randRange(-10000, 10000);
#else
                cin >> c;
#endif
                trace(l, r, c);
                add(l, r, c);
#ifdef CHECK
                brute_add(l, r, c);
#endif
                break;
            case 2:
#ifdef TEST
                d = randRange(2, 100000);
#else
                cin >> d;
#endif
                trace(l, r, d);
                divide(l, r, d);
#ifdef CHECK
                brute_divide(l, r, d);
#endif
                break;
            case 3:
                trace(t, l, r);
                ans = min_value(l, r);
                cout << ans << '\n';
#ifdef CHECK
                bans = brute_min(l, r);
                if(ans != bans) {
                    trace(ans, bans);
                    bans = brute_sum(l, r);
                    assert(ans == bans);
                }
#endif
                break;
            case 4:
                trace(t, l, r);
                ans = sum_value(l, r);
                cout << ans << '\n';
#ifdef CHECK
                bans = brute_sum(l, r);
                if(ans != bans) {
                    trace(ans, bans);
                    bans = brute_sum(l, r);
                    assert(ans == bans);
                }
#endif
                break;
        }
        fo(i, nb) trace(i, blocks[i]);
#ifdef CHECK
        //fo(i, n) cerr << brute_boxes[i] << " "; cerr << endl;
#endif
        //fo(i, n) trace(i, box[i]);

    }
    
	return 0;
}

