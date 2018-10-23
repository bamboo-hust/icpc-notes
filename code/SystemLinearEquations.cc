// extended version, uses diophantine equation solver to solve system of congruent equations
pair<int, int> solve(int a, int b, int c) {
	// solve ax + by == c
	int d = __gcd(a, b);
	int x = bezout(a / d, b / d);
	int y = (d - a * x) / b;
	c /= d;
	return make_pair(x * c, y * c);
}

int lcm(int a, int b) {
	return a / __gcd(a, b) * b;
}

int solveSystem(vector<int> a, vector<int> b) {
	// xi mod bi = ai
	int A = a[0], B = b[0];
	// x mod B = A
	for (int i = 1; i < a.size(); ++i) {
		int curB = b[i], curA = a[i];
		// x = Bi + A = curB * j + curA
		pair<int, int> ij = solve(B, -curB, curA - A);
		assert(B * ij.first + A == curB * ij.second + curA);
		int newA = (B * ij.first + A);
		B = lcm(B, curB);
		A = newA % B;
		if (i + 1 == a.size()) return A;
	}
}

int main() {
	vector<int> a = {0, 3, 3};
	vector<int> b = {3, 6, 9};
	cout << solveSystem(a, b) << endl;
	return 0;
}
