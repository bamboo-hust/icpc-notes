Let m, n, a, b be any interger. Let g = gcd(m, n).
    x % m = a
    x % n = b
if (a % g == b % g) : it has unique solution modulo lcm(n, m)
else : no solution

g = u * m + v * n
x = (a * v * n + b * u * m) / g