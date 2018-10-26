struct SuffixArray {
    static const int N = 1e5 + 5;
    static const char sep = '$';

    int n;
    char s[N];
    int sa[N], ra[2][N];
    int lcp[N];

    SuffixArray(char *t) {
        build(t);
    }

    void build(char* t) {
        strcpy(s, t), n = strlen(s);
        for (int i = 0; i < n; i++) {
            sa[i] = i, ra[0][i] = 0, ra[1][i] = s[i] + 1;
        }
        for (int d = 1; radixsort(); d <<= 1) {
            for (int i = 0; i < n; i++) {
                if (i + d < n) {
                    ra[1][i] = ra[0][i + d] + 1;
                }
                else {
                    ra[1][i] = 0;
                }
            }
        }
        buildlcp();
    }

    int radixsort() {
        static int p[N];
        static int tmpsa[N];
        static int tmpra[N];
        int mx = max(256, n) + 1;
        for (int step = 1; step >= 0; step--) {
            fill_n(p, mx, 0);
            for (int i = 0; i < n; i++) {
                p[ra[step][i] + 1]++;
                tmpsa[i] = sa[i];
            }
            partial_sum(p, p + mx, p);
            for (int i = 0; i < n; i++) {
                sa[p[ra[step][tmpsa[i]]]++] = tmpsa[i];
            }
        }
        int ptr = 0;
        tmpra[sa[0]] = ptr;
        for (int i = 1; i < n; i++) {
            int u = sa[i - 1];
            int v = sa[i];
            if (ra[0][u] < ra[0][v] || ra[1][u] < ra[1][v]) {
                ptr++;
            }
            tmpra[v] = ptr;
        }
        for (int i = 0; i < n; i++) ra[0][i] = tmpra[i];
        return ptr < n - 1;
    }

    void buildlcp() {
        for (int i = 0, k = 0; i < n; i++) {
            if (!ra[0][i]) lcp[ra[0][i]] = 0;
            else {
                for (int j = sa[ra[0][i] - 1]; s[i + k] == s[j + k] && s[i + k] != sep; k++);
                lcp[ra[0][i]] = k;
                k = max(k - 1, 0);
            }
        }
    }
};
