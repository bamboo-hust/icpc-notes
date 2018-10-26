const int V = 1e5;
const int INF = 1e9;
struct Flow {
    vector<int> adj[V];
    int to[V], c[V], f[V];
    int n, s, t, cnt;
    int d[V];
    int cur[V];
    Flow(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        cnt = 0;
    }
    int addEdge(int u, int v, int _c) {
        to[cnt] = v, c[cnt] = _c, f[cnt] = 0;
        adj[u].push_back(cnt++);
        to[cnt] = u, c[cnt] = 0, f[cnt] = 0;
        adj[v].push_back(cnt++);
    }
    bool bfs() {
        for (int i = 0; i < n; i++) d[i] = -1;
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                int v = to[id];
                if (d[v] == -1 && f[id] < c[id]) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
    int dfs(int u, int res) {
        if (u == t) return res;
        for (int &it = cur[u]; it < adj[u].size(); it++) {
            int id = adj[u][it];
            int v = to[id];
            if (d[v] == d[u] + 1 && f[id] < c[id]) {
                int foo = dfs(v, min(c[id] - f[id], res));
                if (foo) {
                    f[id] += foo;
                    f[id ^ 1] -= foo;
                    return foo;
                }
            }
        }
        return 0;
    }
    int maxFlow() {
        int res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++) cur[i] = 0;
            while (1) {
                int foo = dfs(s, INF);
                if (!foo) break;
                res += foo;
            }
        }
        return res;
    }
};
