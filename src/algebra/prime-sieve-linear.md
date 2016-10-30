<!--?title Sieve of Eratosthenes Having Linear Time Complexity -->

# Sieve of Eratosthenes Having Linear Time Complexity


We have a number $n$. We need to find out all prime numbers in a segment $[2;n]$.

The standard way of solving a task is to use Sieve of Eratosthenes. This algorithm is very simple, but it works using the time of $O(n \log \log n)$.

Although there are a lot of algorithms working for sublinear time (i.e. for $o(n)$) at the present moment, the algorithm described below is interesting by its **simplicity**: practically, it isn't more complex than any classic Sieve of Eratosthenes.

Besides, the algorithm given here as “a side effect”, in fact, calculates **the factorizations of all numbers** in a segment $[2; n]$, and that can be helpful in many practical applications.

The weakness of the given algorithm is in using **more memory** than the classic Sieve of Eratosthenes’ usage: it is needed to create an array of $n$ numbers, while for the Sieve of Eratosthenes it is enough to have just $n$ bits of memory (that is 32 times less).

Thus, we have a reason to use a described algorithm only until the numbers of order $10^7$, and not more of that.

The algorithm’s authorship appears to belong to Gries & Misra (Gries, Misra, 1978: please see references in the end). And, properly speaking, it’s incorrectly to use a term of “the Sieve of Eratosthenes” for our algorithm: these two algorithms differ too much between each other).



## The description of the algorithm


Our goal is to calculate **a minimum prime factor** $lp [i]$ for every number $i$ in a segment $[2; n]$.

Besides, we need to keep the list of all the found prime numbers - let's call it $array\ pr []$.

Initially, we’ll fill out all the values $lp [i]$ with zeros, which means that we assume all numbers are prime. During the work of the algorithm, this array will be filled gradually.

Now we’ll go through the current number $i$ from *2* to $n$. It appears we have two cases:

- $lp [i] = 0$ - that means that the number $i$ is a prime number, i.e. we haven't found any prime factors for it.

Hence, it is needed to assign $lp [i] = i$ and to add $i$ to the end of the list $pr[]$.

- $lp[i] \neq 0$ - that means that the current number $i$ is a composite number, and its minimum prime factor is $lp [i]$.

In both cases afterwards begins the process of **arranging values** in array $lp []$:  we'll be taking the numbers that are multiple to $i$ and updating values of $lp []$. However, our goal is to learn to do it in a way to set a value $lp []$ not more than once for every number.

In order to perform this we need to do the following. Let's look at the numbers of type

$x _j = i \cdot \ p _ j$,

where the sequence $p _j$ is all prime numbers not more than $lp [i]$ (for that exactly we need to keep a list of all prime numbers).

We’ll set a new value $lp [x _j]$ for all the numbers of this type, and, obviously, it will be equal to $p _j$ .

The proof of correctness of this algorithm, as well as the proof that it works for the linear time is arranged below, after the implementation.



## Implementation


The sieving will undergo till the number *N* which is defined as a constant.

````cpp
const int N = 10000000;
int lp[N+1];
vector<int> pr;
 
for (int i=2; i<=N; ++i) {
	if (lp[i] == 0) {
		lp[i] = i;
		pr.push_back (i);
	}
	for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
		lp[i * pr[j]] = pr[j];
}
````

We can speed it up a bit by getting rid of vector $pr$ (by replacing it with the simple array and a counter) and also getting rid of the duplicated multiplication in a nested cycle $for$ (for that we just need to remember the result of multiplication in a some variable).

## The proof of correctness

Let's prove the **correctness** of the algorithm, i.e. that it is setting all the values $lp []$ correctly, and every value will be set exactly once. Hence, the algorithm will work for the linear time, as all the remaining actions of the algorithm, obviously, work for *O (n)*.

For that we should notice that every number $i$ has **only one equation** in such way:

$i = lp [i] \cdot \ x$ ,

where $lp [i]$ (as previously) is a minimal prime factor of a number $i$, and the number $x$ doesn’t have the prime factors lesser than $lp [i]$, i.e.

$lp [i] \le \ lp [x]$.

Now, let's compare that with the work of our algorithm: in fact, for every $x$ it goes through all prime numbers, possible multipliers for $x$, i.e. the prime numbers till $lp [x]$ inclusive, in order to get the numbers in the equation presented above.

Hence, the algorithm, indeed, will go through every composite number exactly once, setting the correct values $lp []$ there.

That proves the correctness of the algorithm and that it works for the linear time.



## The running time and needed memory


Although the running time of $O(n)$ is better than of  $O(n \log \log n)$ of the classic Sieve of Eratosthenes, the difference between them is not so big. In practice that means just double difference in speed, and the optimized versions of the Sieve of Eratosthenes indeed do not fail to the algorithm given here.

Considering the expenditures of the memory that this algorithm needs, using an array of numbers $lp []$ of the length $n$, and an array of all prime numbers $pr []$ of the length appr. $\frac n {\ln n}$, this algorithm seems to be giving up to the classic Sieve of Eratosthenes in every sense of the word.

However, one benefit is that an array $lp []$ calculated by this algorithm allows us to look for a factorization of any number in a segment $[2; n]$ for the time of the size order of this factorization. Moreover, using just one extra array will allow us to avoid divisions when looking for factorization.

Knowing the factorizations of all numbers is a very helpful information for some tasks, and this algorithm is one of a few that allows us to find them for the linear time.



## References

- David Gries, Jayadev Misra. **A Linear Sieve Algorithm for Finding Prime Numbers** [1978]
