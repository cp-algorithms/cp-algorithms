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


