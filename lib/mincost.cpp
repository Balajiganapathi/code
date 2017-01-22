
struct MinCostFlow {
    MinCostFlow(int _n,int _s,int _t) : n(_n), s(_s), t(_t), fl(0), cost(0) {
        first.resize(n,-1);
        dist.resize(n);
        prev.resize(n);
        a.reserve(8*n);
    };
    struct Edge {
        Edge(int _to,int _cap,int _cost,int _next) : to(_to), cap(_cap), cost(_cost), next(_next) {};
        int to,next,cap,cost;
    };
    void addEdge(int u,int v,int cap,int cost) {
        a.push_back(Edge(v,cap,cost,first[u])); first[u]=a.size()-1;
        a.push_back(Edge(u,0,-cost,first[v])); first[v]=a.size()-1;
    }
    bool augment() {
        dist.assign(n,inf);
        dist[s]=0;
        priority_queue < pair <int,int> > q; q.push(make_pair(0,s));
        while(q.size()) {
            if (dist[t]!=inf) break;
            pair <int,int> top=q.top(); q.pop();
            if (dist[top.second]!=-top.first) continue;
            int u=top.second;
            for(int e=first[u];e!=-1;e=a[e].next) {
                int v=a[e].to,ndist=-top.first+a[e].cost;
                if (a[e].cap>0&&dist[v]>ndist) {
                    dist[v]=ndist;
                    q.push(make_pair(-ndist,v));
                    prev[v]=e;
                }
            }
        }
        return dist[t]!=inf;
    }
    pair <int,int> flow() {
        while(augment()) {
            int cur=t,size=inf;
            while(cur!=s) {
                int e=prev[cur];
                size=min(size,a[e].cap);
                cur=a[e^1].to;
            }
            fl+=size; cost+=(dist[t])*size;
//          if (cost>=0) break;
            cur=t;
            while(cur!=s) {
                int e=prev[cur];
                a[e].cap-=size;
                a[e^1].cap+=size;
                cur=a[e^1].to;
            }
        }
        return make_pair(fl,cost);
    }
    int n,s,t,fl,cost;
    static const int inf=1000000009;
    vector <int> first,prev,dist;
    vector <Edge> a;
};


