// l <= a * k <= r (k > 0) (l <= r) (mod)
long long solve(long long l, long long r, long long a, long long mod) {
    if (a == 0) return INF;
    if (a * 2 > mod) return solve(mod - r, mod - l, mod - a, mod);
    long long firstVal = getCeil(l, a);
    if (a * firstVal <= r) return firstVal;
    if (mod % a == 0) return INF;
    long long kPrime = solve(l % a, r % a, a - mod % a, a);
    if (kPrime == INF) return INF;
    long long res = getCeil(kPrime * mod + l, a);
    return getCeil(kPrime * mod + l, a);
}