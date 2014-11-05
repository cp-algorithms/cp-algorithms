<!--?title Discrete Root -->

# Discrete Root

The problem of finding `discrete root` is defined as follows. Given a prime $n$, and 2 integers $a$, $k$. It is required to find all $x$ satisfying:

$x^k \equiv a \pmod n$

## The algorithm

We will solve this problem by reducing it to the discrete logarithm problem.

For this, we apply the concept of a `primitive root` modulo $n$. Let $g$ be a primitive root modulo $n$. Note that since $n$ is prime, it must exist, and it can be found in $O(Ans . \log \phi (n) . \log n)$.

We can easily discard the case where $a = 0$. In this case, obviously there is only one answer: $x = 0$.

Now we can transform the problem to:

$x^k \equiv a \pmod n$
$(g^y)^k \equiv a \pmod n$
$(g^k)^y \equiv a \pmod n$

Now we have one unknown y, which can be calculated by the discrete logarithm algorithm using baby-step-giant-step algorithm Shanks in $O(\sqrt (n) \log n)$.

Having found one solution $y_0$ (or see that there is no solution at all), we can find all solutions, which is described in the following section.

## Finding all solutions from one known solution

To completely solve the problem, recall the fact that a primitive root always has index $\phi (n)$. Therefore, if we add the term $\phi (n)$ to the exponential, we still get the same value:

$x^k \equiv g^{ y_0 . k + l . \phi (n)} \equiv a \pmod n$

Hence, all the solutions are of the form:

$x = g^{y_0 + \frac {l . \phi (n)}{k}} \pmod n$.

where $l$ is chosen such that the fraction must be an integer.

## Implementation

```cpp
int gcd (int a, int b) {
	return a ? gcd (b%a, a) : b;
}
 
int powmod (int a, int b, int p) {
	int res = 1;
	while (b)
		if (b & 1)
			res = int (res * 1ll * a % p),  --b;
		else
			a = int (a * 1ll * a % p),  b >>= 1;
	return res;
}
 
int generator (int p) {
	vector<int> fact;
	int phi = p-1,  n = phi;
	for (int i=2; i*i<=n; ++i)
		if (n % i == 0) {
			fact.push_back (i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		fact.push_back (n);
 
	for (int res=2; res<=p; ++res) {
		bool ok = true;
		for (size_t i=0; i<fact.size() && ok; ++i)
			ok &= powmod (res, phi / fact[i], p) != 1;
		if (ok)  return res;
	}
	return -1;
}
 
int main() {
 
	int n, k, a;
	cin >> n >> k >> a;
	if (a == 0) {
		puts ("1\n0");
		return 0;
	}
 
	int g = generator (n);
 
	int sq = (int) sqrt (n + .0) + 1;
	vector < pair<int,int> > dec (sq);
	for (int i=1; i<=sq; ++i)
		dec[i-1] = make_pair (powmod (g, int (i * sq * 1ll * k % (n - 1)), n), i);
	sort (dec.begin(), dec.end());
	int any_ans = -1;
	for (int i=0; i<sq; ++i) {
		int my = int (powmod (g, int (i * 1ll * k % (n - 1)), n) * 1ll * a % n);
		vector < pair<int,int> >::iterator it =
			lower_bound (dec.begin(), dec.end(), make_pair (my, 0));
		if (it != dec.end() && it->first == my) {
			any_ans = it->second * sq - i;
			break;
		}
	}
	if (any_ans == -1) {
		puts ("0");
		return 0;
	}
 
	int delta = (n-1) / gcd (k, n-1);
	vector<int> ans;
	for (int cur=any_ans%delta; cur<n-1; cur+=delta)
		ans.push_back (powmod (g, cur, n));
	sort (ans.begin(), ans.end());
	printf ("%d\n", ans.size());
	for (size_t i=0; i<ans.size(); ++i)
		printf ("%d ", ans[i]);
 
}
```

