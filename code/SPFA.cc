struct Graph {
    vector< vector< pair<int, int> > > a;
    vector<int> d;
    int n;

    Graph(int n) {
        this->n = n;
        a.resize(n);
    }

    void add_edge(int u, int v, int c) {
        // x[u] - x[v] <= c
        a[v].push_back(make_pair(u, c));
    }

    bool spfa(int s) {
        // return false if found negative cycle from s
        queue<int> Q;
        vector<bool> inqueue(n);
        d.assign(n, INF);
        d[s] = 0;
        Q.push(s); inqueue[s] = 1;

        vector<int> cnt(n);
        cnt[s] = 1;

        while (!Q.empty()) {
            int u = Q.front(); Q.pop(); inqueue[u] = 0;
            for (auto e : a[u]) {
                int v = e.first;
                int c = e.second;
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                    cnt[v]++;
                    if (cnt[v] >= n) return false;
                    if (!inqueue[v]) {
                        Q.push(v);
                        inqueue[v] = 1;
                    }
                }
            }
        }

        return true;
    }

    int spfa(int s, int t) {
        assert(spfa(s));
        return d[t];

    }
};