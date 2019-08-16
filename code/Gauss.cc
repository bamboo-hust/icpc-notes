const int INF = 1e9;
const double EPS = 1e-9;
int gauss(vector<vector<double> > a, vector<double> &ans) {
    int m = a.size(), n = a[0].size() - 1;
    vector<int> where (n, -1); // corresponding row for each column
    for (int row = 0, col = 0; col < n; ++col) {
        // find the maximum abs value on the current column to reduce precision errors
        int maxRow = row; 
        for (int i = row + 1; i < m; ++i) {
            if (abs(a[i][col]) > abs(a[maxRow][col]))
            maxRow = i;
        }
        // if cannot find anything rather than zero then forget the current column
        if (abs(a[maxRow][col]) < EPS) continue;
        if (maxRow != row) swap(a[maxRow], a[row]);
        where[col] = row;
        for (int i = 0; i < m; ++i) if (i != row) {
            double coef = a[i][col] / a[row][col];
            for (int j = col; j <= n; ++j) {
                a[i][j] -= a[row][j] * coef;
            }
        }
        ++row; // only when found a non-zero element
    }
    ans.assign(m, 0); // default value = 0
    for (int i = 0; i < n; ++i) if (where[i] != -1) {
        ans[i] = a[where[i]][n] / a[where[i]][i];
    }
    // recheck
    for (int i = 0; i < m; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += a[i][j] * ans[j];
        }
        if (abs(sum - a[i][n]) > EPS) return 0; // no solution
    }
    // search for independent variables
    for (int i = 0; i < n; ++i) if (where[i] == -1) return INF; // infinite many solution
    return 1; // one solution saved in vector ans
}
