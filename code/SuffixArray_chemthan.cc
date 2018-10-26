#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>

using namespace std;

#include "SuffixArray.h"

const int N = 1e5 + 5;

char s[N];

int main() {
	ios::sync_with_stdio(false);

	cin >> s;
	SuffixArray sa(s);
	for (int i = 0; i < sa.n; ++i) {
		cout << sa.sa[i] << '\n';
	}

	return 0;
}