struct AhoCorasick {
    const int N = 30030;

    int fail[N];
    int to[N][2];
    int ending[N];
    int sz;

    void add(const string &s) {
        int node = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (!to[node][s[i] - 'a']) {
                to[node][s[i] - 'a'] = ++sz;
            }
            node = to[node][s[i] - 'a'];
        }
        ending[node] = true;
    }

    void push() {
        queue<int> Q;
        Q.push(1);
        fail[1] = 1;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int i = 0; i < 26; ++i) {
                int &v = to[u][i];
                if (!v) {
                    v = u == 1 ? 1 : to[fail[u]][i];
                } else {
                    fail[v] = u == 1 ? 1 : to[fail[u]][i];
                    Q.push(v);
                }
            }
        }
    }
};