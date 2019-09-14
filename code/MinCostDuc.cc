struct Network {
    struct Edge {
        int v, cap, cost, flow;
        int remain() {
            return cap - flow;
        }
    };
    vector<Edge> E;
    vector< vector<int> > a;
    vector<int> prev;

    int n, s, t;

    Network(int n, int s, int t): n(n), s(s), t(t) {
        a.resize(n); prev.resize(n);
    }

    void add_directed_edge(int u, int v, int cap, int cost) {
        a[u].push_back(E.size()); E.push_back(Edge{v, cap, cost, 0});
        a[v].push_back(E.size()); E.push_back(Edge{u, 0, -cost, 0});
    }

    void add_undirected_edge(int u, int v, int cap, int cost) {
        add_directed_edge(u, v, cap, cost);
        add_directed_edge(v, u, cap, cost);
    }

    bool find_path() {
        vector<int> d(n, INF);
        prev.assign(n, -1);
        queue<int> Q;
        vector<bool> in_queue(n);
        Q.push(s); in_queue[s] = true; d[s] = 0;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop(); in_queue[u] = false;
            for (int e : a[u]) {
                int v = E[e].v;
                if (E[e].flow < E[e].cap && d[v] > d[u] + E[e].cost) {
                    d[v] = d[u] + E[e].cost;
                    prev[v] = e;
                    if (!in_queue[v]) {
                        in_queue[v] = true;
                        Q.push(v);
                    }
                }
            }
        }
        return prev[t] != -1;
    }

    pair<int, int> min_cost_max_flow() {
        int maxflow = 0;
        int mincost = 0;

        auto inc_flow = [&]() {
            int flow = INF;
            for (int u = t; u != s; ) {
                int e = prev[u];
                flow = min(flow, E[e].remain());
                u = E[e ^ 1].v;
            }
            for (int u = t; u != s; ) {
                int e = prev[u];
                mincost += E[e].cost * flow;
                E[e].flow += flow;
                E[e ^ 1].flow -= flow;
                u = E[e ^ 1].v;
            }
            maxflow += flow;
        };

        while (find_path()) inc_flow();
        return make_pair(maxflow, mincost);
    }
};