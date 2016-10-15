/* string coder = "Balajiganapathi S"; // Never give up!  */



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

    
class FindingFriend {
public:
	int find( int roomSize, vector <int> leaders, int friendPlace ) {
		int ret = 0;
        fo(i, si(leaders)) {
            if(leaders[i] == friendPlace) return 1;
        }

        sort(all(leaders));
        fo(i, si(leaders)) if(friendPlace > leaders[i]) {
            int occupied = 0;
            bool possible = true;
            fo(j, si(leaders) - 1) {
                occupied += leaders[j+1] - leaders[j];
                if(i == j) ++occupied;
                if(leaders[j+1] > friendPlace && friendPlace > leaders[j]) --occupied;
                //trace(i, j, occupied);
                if(occupied > (j+1) * roomSize) {
                    possible = false;
                    break;
                }
            }
            //trace(i, possible);

            ret += possible;
        }
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
