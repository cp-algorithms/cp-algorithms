<!--?title Convex hull trick and Li Chao tree -->

# Convex hull trick and Li Chao tree

Consider following problem. There are $n$ cities. You want to travel from city $1$ to city $n$ by car. To do this you have to buy some gasoline. It is known that liter of gasoline costs $cost_k$ in $k^{th}$ city. Initially your fuel tank is empty and you spend one liter of gasoline per kilometer. Cities are located on the same line in ascending order with $k^{th}$ city having coordinate $x_k$. Also you have to pay $toll_k$ to enter $k^{th}$ city. Your task is to make the trip with minimum possible cost. It's obvious that solution can be calculated via dynamic programming

$$dp_i = toll_i+\min\limits_{j<i}(cost_j \cdot (x_i - x_j)+dp_j)$$

Naive approach will give you $O(n^2)$ complexity which can be improved to $O(n \log n)$ or $O(n \log [C \varepsilon^{-1}])$ where $C$ is largest possible $|x_i|$ and $\varepsilon$ is precision with which $x_i$ is considered ($\varepsilon = 1$ for integers which is usually the case). To do this one should note that problem can be reduced to adding linear functions $k \cdot x + b$ to the set and finding minimum value of function in some particular point $x$. There are two main approaches one can use here.

## Convex hull trick

Idea of this approach is to maintain lower convex hull of linear functions. After that 

## Li Chao tree
