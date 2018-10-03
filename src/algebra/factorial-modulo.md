<!--?title Factorial modulo P -->
# Factorial modulo $p$ in $O(p \log n)$
In some cases it is necessary to consider complex formulas modulo $p$, containing factorials in both numberator and denominator. We consider the case when $p$ is relatively small. This problem makes sense only when factorials are included in both numerator and denominator of fractions. Otherwise $p!$ and subsequent terms will reduce to zero, but in fractions all multipliers containing $p$ can be reduced, and the resulting expression will be non-zero modulo $p$.

Thus, formally the task is: You want to calculate $n!%p$, without taking into account all the multiple factors of $p$, included in the factorial. Learning how to effectively calculate a factorial, we can quickly calculate the value of the various combinatorial formulae (for example, [Binomial coefficients](https://cp-algorithms.com/combinatorics/binomial-coefficients.html)).

## Algorithm
Let's write this modified factorial explicitly.
$$
\begin{array}{clc}
n!\%p & = 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \underbrace{1}_{p} \cdot (p+1) \cdot (p+2) \cdot \ldots \cdot (2p-1) \cdot \underbrace{2}_{2p} \\ & \quad \cdot (2p+1) \cdot \ldots \cdot (p^2-1) \cdot \underbrace{1}_{p^2} \cdot (p^2 +1) \cdot \ldots \cdot n \\
& = 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \cdot \underbrace{1}_{p} \cdot 2 \cdot \ldots \cdot (p-1) \cdot \underbrace{2}_{2p} \cdot 1 \cdot 2 \\
& \quad \cdot \ldots \cdot (p-1) \cdot \underbrace{1}_{p^2}
\cdot 1 \cdot 2 \cdot \ldots \cdot (n\%p) (\mathrm{mod} p)\\

\end{array}
$$

It can be clearly seen that factorial is divied into several blocks of same length expect for the last one.

$$
\begin{array}{cll}
n!\,\% \, p & = \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{1st} \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 2}_{2nd} \cdot \ldots \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{p-th} \cdot \ldots \cdot \\
& \quad \underbrace{1 \cdot 2 \cdot \cdot \ldots \cdot (n\%p)}_{tail} (\mathrm{mod} p).

\end{array}
$$

The General part of the blocks it is easy to count — it's just $(p-1)!\ \mathrm{mod}\ p$ that you can calculate programmatically or via Wilson theorum, accroding to which $(p-1)!\ {\rm mod}\ p = p-1$. To multiply these common parts of all blocks, we can raise the value to the degree modulo $p$ which can be done in $O(\log n)$ operations using Binary Exponentiation; however, you may notice that we actually built negative one in some degree, and therefore the result will always be either $1$ or $p-1$, depending on the parity of the index. The value of the last partial block can be calculated separately in $O(p)$. Leaving only the last elements of the blocks, we can examine that:
$$
\begin{array}{cll}
n!\,\% \, p & = \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 2} \cdot \ldots \cdot \underbrace{ \ldots \cdot (p-1)} \cdot \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 1} \cdot \underbrace{ \ldots \cdot 2} \cdots
\end{array}
$$
And again, we receive "modified" factorial form but with smaller dimension ($\lfloor n / p \rfloor$ blocks remain). Thus, in the calculation of "modified" the factorial $n!_{\%p}$ we drove over $O(p)$ operations to the calculation of $(n/p)!_{\%p}$. Revealing this recursive dependence, we obtain that the recursion depth is $O(\log_p n)$, the total asymptotic behavior of the algorithm is thus $O(p \log_p n)$.
