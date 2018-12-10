typedef vector<int> bigInt;
const int BASE = 1000;
const int LENGTH = 3;
 
// * Refine function
bigInt& fix(bigInt &a) {
    a.push_back(0);
    for (int i = 0; i + 1 < a.size(); ++i) {
        a[i + 1] += a[i] / BASE; a[i] %= BASE;
        if (a[i] < 0) a[i] += BASE, --a[i + 1];
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}
 
// * Constructors
bigInt big(int x) {
    bigInt result;
    while (x > 0) {
        result.push_back(x % BASE);
        x /= BASE;
    }
    return result;
}
 
bigInt big(string s) {
    bigInt result(s.size() / LENGTH + 1);
    for (int i = 0; i < s.size(); ++i) {
        int pos = (s.size() - i - 1) / LENGTH;
        result[pos] = result[pos] * 10 + s[i] - '0';
    }
    return fix(result), result;
}
 
// * Compare operators
 
int compare(bigInt &a, bigInt &b) {
    if (a.size() != b.size()) return (int)a.size() - (int)b.size();
    for (int i = (int) a.size() - 1; i >= 0; --i)
        if (a[i] != b[i]) return a[i] - b[i];
    return 0;
}
 
#define DEFINE_OPERATOR(x) bool operator x (bigInt &a, bigInt &b) { return compare(a, b) x 0; }
DEFINE_OPERATOR(==)
DEFINE_OPERATOR(!=)
DEFINE_OPERATOR(>)
DEFINE_OPERATOR(<)
DEFINE_OPERATOR(>=)
DEFINE_OPERATOR(<=)
#undef DEFINE_OPERATOR
 
// * Arithmetic operators
 
void operator += (bigInt &a, bigInt b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); ++i)
        a[i] += b[i];
    fix(a);
}
 
void operator -= (bigInt &a, bigInt b) {
    for (int i = 0; i < b.size(); ++i)
        a[i] -= b[i];
    fix(a);
}
 
void operator *= (bigInt &a, int b) {
    for (int i = 0; i < a.size(); ++i)
        a[i] *= b;
    fix(a);
}
 
void divide(bigInt a, int b, bigInt &q, int &r) {
    for (int i = int(a.size()) - 1; i >= 0; --i) {
        r = r * BASE + a[i];
        q.push_back(r / b); r %= b;
    }
    reverse(q.begin(), q.end());
    fix(q);
}
 
bigInt operator + (bigInt a, bigInt b) { a += b; return a; }
bigInt operator - (bigInt a, bigInt b) { a -= b; return a; }
bigInt operator * (bigInt a, int b) { a *= b; return a; }
 
bigInt operator / (bigInt a, int b) {
    bigInt q; int r = 0;
    divide(a, b, q, r);
    return q;
}
int operator % (bigInt a, int b) {
    bigInt q; int r = 0;
    divide(a, b, q, r);
    return r;
}
 
bigInt operator * (bigInt a, bigInt b) {
    bigInt result (a.size() + b.size());
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b.size(); ++j)
            result[i + j] += a[i] * b[j];
    return fix(result);
}
 
// * I/O routines
 
istream& operator >> (istream& cin, bigInt &a) {
    string s; cin >> s;
    a = big(s);
    return cin;
}
 
ostream& operator << (ostream& cout, const bigInt &a) {
    cout << a.back();
    for (int i = (int)a.size() - 2; i >= 0; --i)
        cout << setw(LENGTH) << setfill('0') << a[i];
    return cout;
}