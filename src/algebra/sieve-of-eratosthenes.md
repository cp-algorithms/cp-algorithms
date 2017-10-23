<!--?title Sieve of Eratosthenes -->

# Sieve of Eratosthenes

Sieve of Eratosthenes is an algorithm for finding all the prime numbers in a segment $[1;n]$ using $O(n \log \log n)$ operations.

The idea is simple: at the beginning we write down a row of numbers and eliminate all numbers divisible by 2, except number 2 itself,  then divisible by 3, except number 3 itself, next by 7, 11, and all the remaining prime numbers till $n$.

## Implementation

```cpp
int n;
vector<char> prime (n+1, true);
prime[0] = prime[1] = false;
for (int i=2; i<=n; ++i)
    if (prime[i])
        if (i * 1ll * i <= n)
            for (int j=i*i; j<=n; j+=i)
                prime[j] = false;
```

This code first marks all numbers except zero and one as prime numbers, then it begins the process of sifting composite numbers. For this it goes through all numbers $2$ to $n$ in a cycle. If the current number $i$ is a prime number, it marks all numbers that are multiples of $i$ as composite numbers, starting from $i^2$ as all smaller numbers that are multiples of $i$ necessary have a prime factor which is less than $i$, so all of them were sifted earlier. (Since $i^2$ can easily overflow the type `int`, the additional verification is done using type `long long` before the second nested cycle).

Using such implementation the algorithm consumes $O(n)$ of the memory (obviously) and performs $O(n \log \log n)$ (this is  proven in the next section).

## Asymptotic analysis

Let's prove that algorithm's running time is $O(n \log \log n)$. It will take $\frac n p$ actions for every prime $p \le n$ the inner cycle performs. Hence, we need to evaluate the next value:

$$\sum_{\substack{p \le n, \\\ p\ is\ prime}} \frac n p = n \cdot \sum_{\substack{p \le n, \\\ p\ is\ prime}} \frac 1 p.$$

Let's recall two known facts. First fact: the number of prime numbers that are less than or equal to $n$ approximately equals  $\frac n {\ln n}$. Second fact: the $k$-th prime number approximately equals $k \ln k$ (that follows from the first fact). Then, we can write down the sum in a such way:

$$\sum_{\substack{p \le n, \\\ p\ is\ prime}} \frac 1 p \approx \frac 1 2 + \sum_{k = 2}^{\frac n {\ln n}} \frac 1 {k \ln k}.$$

Here we separated the first prime number from the rest of the numbers in the sum, since $k = 1$ in approximation $k \ln k$  is $0$ and causes division by zero operation.

Now, let's evaluate this sum using the integral of a same function over $k$ from $2$ to $\frac n {\ln n}$ (we can make such approximation because, in fact, the sum is related to the integral as its approximation using rectangle method):

$$\sum_{k = 2}^{\frac n {\ln n}} \frac 1 {k \ln k} \approx \int_2^{\frac n {\ln n}} \frac 1 {k \ln k} dk.$$

The antiderivative for the integrand is  $ \ln \ln k$. Using a substitution and removing terms of lower order, we'll get the result:

$$\int_2^{\frac n {\ln n}} \frac 1 {k \ln k} dk = \ln \ln \frac n {\ln n} - \ln \ln 2 = \ln(\ln n - \ln \ln n) - \ln \ln 2 \approx \ln \ln n.$$

Now, returning to the original sum, we'll get its approximate evaluation:

$$\sum_{\substack{p \le n, \\\ p\ is\ prime}} \frac n p \approx n \ln \ln n + o(n),$$

Q.E.D.

More strict proof (that gives more precise evaluation which is accurate within constant multipliers) you can find in the book authored by Hardy & Wright "An Introduction to the Theory of Numbers" (p. 349).

## Different optimizations of the Sieve of Eratosthenes

The biggest weakness of the algorithm is that it "walks" along the memory, constantly getting out of the cache memory limits. Because of that the constant which is concealed in $O(n \log \log n)$ is comparably big.

Besides, the consumed memory is the bottleneck for big $n$.

The methods presented below allow us to reduce the quantity of the performed operations, as well as to shorten the consumed memory noticeably.

### Sieving by the prime numbers till root

Obviously, to find all the prime numbers until $n$, it will be enough just to perform the sieving only by the prime numbers, which do not exceed the root of $n$.

Thus, the outer cycle of the algorithm will change:

```cpp
for (int i=2; i*i<=n; ++i)
```

Such optimization doesn't affect the running time (indeed, by repeating the proof presented above we'll get the evaluation         $n \ln \ln \sqrt n + o(n)$, which is asymptotically the same according to the properties of logarithm), though the number of operations will reduce noticeably.

### Sieving by the odd numbers only

Since all even numbers (except $2$) are composite, we can stop checking even numbers at all. Instead, we need to operate with odd numbers only.

First, it will allow us to half the needed memory. Second, it will reduce the number of operations performing by algorithm approximately in half.

### Reducing consumed memory

We should notice that algorithm of Eratosthenes operates with $n$ bits of memory. Hence, we can essentially reduce consumed memory by preserving not $n$ bytes, which are the variables of Boolean type, but $n$ bits, i.e. $\frac n 8$ bytes of memory.

However, such approach, which is called **bit-level compression**, will complicate the operations with these bits. Read or write operation on any bit will require several arithmetic operations and ultimately slow down the algorithm.

Thus, this approach is justified provided $n$ is so big that we cannot allocate $n$ bytes of the memory anymore. In this case we will trade saving memory ($8$ times less) with significant slowing down of the algorithm.

After all, it's worth mentioning the data structures that automatically do a bit-level compression, such as vector<bool\> and bitset<\>, have been already implemented in C++ language.

However, if speed is very important, it's better to implement a bit-level compression manually using bit operations. Still, the compilers cannot generate sufficiently fast code for today.

### Block sieving

It follows from the optimization "sieving by the prime numbers till root" that there is no need to keep the whole array $prime[1...n]$ all the time. For performing of sieving  it's enough to keep just prime numbers until root of $n$, i.e. $prime[1... \sqrt n]$ and to build the remaining part of array in blocks. In doing so, we need to keep one block only at the present moment in time.

Let $s$ be a constant which determines the size of the block, then we have $\lceil {\frac n s} \rceil$ blocks altogether, and block $k$ ($k = 0 ... \lfloor {\frac n s} \rfloor$) contains numbers in a segment $[ks; ks + s - 1]$.  We can work on blocks by turns, i.e. for every block $k$ we will go through all the prime numbers (from $1$ to $\sqrt n$) and perform sieving by them inside of a current block only. It is worth working on the first block accurately because of different reasons: first, all the prime numbers from $[1; \sqrt n]$  shouldn't remove themselves; second, the numbers $0$ and $1$ should be marked as non-prime numbers. While working on the last block it should not be forgotten that the last needed number $n$ is not necessary located in the end of the block.

Here we have the implementation of block sieving. The program reads the number $n$ and finds the number of prime numbers from $1$ to $n$.

```cpp
const int SQRT_MAXN = 100000; // square root of maximum value of N
const int S = 10000;
bool nprime[SQRT_MAXN], bl[S];
int primes[SQRT_MAXN], cnt;

int main() {

    int n;
    cin >> n;
    int nsqrt = (int) sqrt (n + .0);
    for (int i=2; i<=nsqrt; ++i)
        if (!nprime[i]) {
            primes[cnt++] = i;
            if (i * 1ll * i <= nsqrt)
                for (int j=i*i; j<=nsqrt; j+=i)
                    nprime[j] = true;
        }

    int result = 0;
    for (int k=0, maxk=n/S; k<=maxk; ++k) {
        memset (bl, 0, sizeof bl);
        int start = k * S;
        for (int i=0; i<cnt; ++i) {
            int start_idx = (start + primes[i] - 1) / primes[i];
            int j = max(start_idx,2) * primes[i] - start;
            for (; j<S; j+=primes[i])
                bl[j] = true;
        }
        if (k == 0)
            bl[0] = bl[1] = true;
        for (int i=0; i<S && start+i<=n; ++i)
            if (!bl[i])
                ++result;
    }
    cout << result;

}
```

The running time of block sieving is the same as for regular sieve of Eratosthenes (unless the size of the blocks is very small), but the needed memory will shorten to $O(\sqrt n + s)$ and "the random walking" on the memory will be reduced. On the other hand, there will be a division for each pair of a block and prime number from $[1; \sqrt n]$, and that will be far worse for smaller block sizes. Hence, it is necessary to keep balance when selecting constant $s$.

According to the performed experiments, we have the best speed of work when $s$ has a value approximately from $10^4$ to $10^5$.

## Advancement to the linear time complexity

We can convert the Eratosthenes algorithm into another algorithm that will have linear time complexity. Look at the article [Sieve of Eratosthenes Having Linear Time Complexity](./algebra/prime-sieve-linear.html). However, this algorithm has its own weaknesses.

## Pracice Problems

* [SPOJ - Printing Some Primes](http://www.spoj.com/problems/TDPRIMES/)
* [SPOJ - A Conjecture of Paul Erdos](http://www.spoj.com/problems/HS08PAUL/)
* [SPOJ - Primal Fear](http://www.spoj.com/problems/VECTAR8/)
* [SPOJ - Primes Triangle (I)](http://www.spoj.com/problems/PTRI/)
* [Codeforces - Almost Prime](http://codeforces.com/contest/26/problem/A)
* [Codeforces - Sherlock And His Girlfriend](http://codeforces.com/contest/776/problem/B)
* [SPOJ - Namit in Trouble](http://www.spoj.com/problems/NGIRL/)
* [SPOJ - Bazinga!](http://www.spoj.com/problems/DCEPC505/)
* [Project Euler - Prime pair connection](https://www.hackerrank.com/contests/projecteuler/challenges/euler134)
* [SPOJ - N-Factorful](http://www.spoj.com/problems/NFACTOR/)
* [SPOJ - Binary Sequence of Prime Numbers](http://www.spoj.com/problems/BSPRIME/)
* [UVA 11353 - A Different Kind of Sorting](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2338)
* [SPOJ - Printing some primes (hard)](http://www.spoj.com/problems/PRIMES2/)
