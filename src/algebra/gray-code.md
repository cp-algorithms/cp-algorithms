<!--?title Gray code-->

###Definition

Gray code is a binary numeral system where two successive values differ in only one bit (binary digit). For example, for numbers of 
length 3 bits we have such sequence of Gray codes: 000, 001, 011, 010, 110, 111, 101, 100. For example, $G(4) = 6$.
This code was invented by Frank Gray in 1953.

###Finding Gray code

Lets look at bits of number $n$ and bits of number $G(n)$. Notice that $i$-th bit of $G(n)$ equals 1 only when $i$-th bit of $n$ equals 1 and 
$i + 1$-th bit equals 0 and otherwise ($i$-th bit equals 0 and $i + 1$-th bit equals 1). Thus, $G(n) = n \oplus (n >> 1)$:  

```   
  int g (int n) { 
	  return n ^ (n >> 1); 
  }
```

###Finding reversed Gray code

Having Gray code $g$ we need to restore initial number $n$.
We will move from most significant bit to less (lets least significant bit has index 1 and most significant bit — k).
We have such a relation between bits $n_i$ of number $n$ and bits $g_i$ of number $g$:

  $n_k = g_k$, <br>
  $n_{k-1} = g_{k-1} \oplus n_k = g_k \oplus g_{k-1}$, <br>
  $n_{k-2} = g_{k-2} \oplus n_{k-1} = g_k \oplus g_{k-1} \oplus g_{k-2}$, <br>
  $n_{k-3} = g_{k-3} \oplus n_{k-2} = g_k \oplus g_{k-1} \oplus g_{k-2} \oplus g_{k-3}$, <br>
  $...$ <br>

The easiest way to write it in programming code is:

```
  int rev_g (int g) {
    int n = 0;
    for (; g; g>>=1)
      n ^= g;
    return n;
  }
```

###Practical application
Gray codes have some useful applications, sometimes quite unexpected:
<ul>
<li>Gray code of $n$ bits forms a Hamiltonian cycle on a hypercube, where each bit is seen as one dimension. 
</li>
<li>Gray codes are used in technology to minimize the effect of error in the conversion of analog signals to digital (for example, in sensors). 
</li>
<li>Gray code can serve as a solution guide for the Towers of Hanoi problem.
    Let $n$ denote number of disks. We will start with Gray code of length $n$ which
    consists of zeroes only ($G(0)$) and we will move on Grey codes (from $G(i)$ to $G(i+1)$).
    Let $i$-th bit of current Grey code represents $n$-th disk (moreover, 
    least significant bit stands for the smallest disk and the most significant bit for the biggest disk). 
    Since we can change exactly one bit on each step we can treat changing $i$-th bit as moving $i$-th disk.
    Notice that there is exactly one move option for each disk (except the smallest one) on each step (except start and finish positions).
    There are always two move options for the smallest disk but there is a strategy which will always lead to answer:
    if $n$ is odd then sequence of the smallest disk moves looks like $f \to t \to r \to f \to t \to r \to ...$
    where $f$ - initial rod, $t$ - terminal rod, $r$ - remaining rod), and in case when 
    $n$ is even: $f \to r \to t \to f \to r \to t \to ...$.
</li>
<li>Gray codes are used in genetic algorithms theory.
</li>
</ul>
###Practice problems
*   <a href="http://acm.sgu.ru/problem.php?contest=0&problem=249">SGU #249 <b>"Matrix"</b> &nbsp;&nbsp;&nbsp;&nbsp; [Difficulty: medium]</a>


