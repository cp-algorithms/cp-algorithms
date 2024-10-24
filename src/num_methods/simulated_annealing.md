---
tags:
    - Original
---

# Simulated Annealing

**Simulated Annealing (SA)** is a randomized algorithm, which approximates the global optimum of a function. It's called a randomized algorithm, because it employs a certain amount of randomness in its search and thus its output can vary for the same input.

## The Problem

We are given a function $E(s)$, which calculates the potential of the state $s$. We are tasked with finding the state $s_{best}$ at which $E(s)$ is minimized. **SA** is suited for problems where the states are discrete and $E(s)$ has multiple local minima. We'll take the example of the [Travelling Salesman Problem (TSP)](https://en.wikipedia.org/wiki/Travelling_salesman_problem). 

### Travelling Salesman Problem (TSP)

You are given a set of nodes in 2 dimensional space. Each node is characterised by its $x$ and $y$ coordinates. Your task is to find the an ordering of the nodes, which will minimise the distance to be travelled when visiting these nodes in that order.

### State

State space is the collection of all possible values that can be taken by the independent variables.
A State is a unique point in the state space of the problem. In the case of TSP, all possible paths that we can take to visit all the nodes is the state space, and any single one of these paths can be considered as a State.

### Neighbouring state

It is a state in the state space which is close to the previous state. This usually means that we can obtain the neighbouring state from the original state using a simple transform. In the case of the Travelling Salesman Problem, a neighbouring state is obtained by randomly choosing 2 nodes, and swapping their positions in the current state. 

### The Energy Function E(s)

$E(s)$ is the function which needs to be minimised (or maximised). It maps every state to a real number. In the case of TSP, $E(s)$ returns the distance of travelling one full circle in the order of nodes in the state. 

## The Approach

We start of with a random state $s$. In every step, we choose a neighbouring state $s_{next}$ of the current state $s$. If $E(s_{next}) < E(s)$, then we update $s = s_{next}$. Otherwise, we use a probability acceptance function $P(E(s),E(s_{next}),T)$ which decides whether we should move to $s_{next}$ or stay at $s$. T here is the temperature, which is initially set to a high value and decays slowly with every step. The higher the temperature, the more likely it is to move to $s_{next}$. 
At the same time we also keep a track of the best state $s_{best}$ across all iterations. Proceeding till convergence or time runs out.

### How does this work?

This algorithm is called simulated annealing because we are simulating the process of annealing, wherein a material is heated up and allowed to cool, in order to allow the atoms inside to rearrange themselves in an arrangement with minimal internal energy, which in turn causes the material to have different properties. The state is the arrangement of atoms and the internal energy is the function being minimised. We can think of the original state of the atoms, as a local minima for its internal energy. To make the material rearrange its atoms, we need to motivate it to go across a region where its internal energy is not minimised in order to reach the global minima. This motivation is given by heating the material to a higher temperature. 

Simulated annealing, literally simulates this process. We start off with some random state (material) and set a high temperature (heat it up). Now, the algorithm is ready to accept states which have a higher energy than the current state, as it is motivated by the high value of $T$. This prevents the algorithm from getting stuck inside local minimas and move towards the global minima. As time progresses, the algorithm cools down and refuses the states with higher energy and moves into the closest minima it has found.


<center>
<img src="https://upload.wikimedia.org/wikipedia/commons/d/d5/Hill_Climbing_with_Simulated_Annealing.gif" width="800px">
<br>
<i>A visual representation of simulated annealing, searching for the maxima of this function with multiple local maxima.</i>.
<br>
<i>This <a href="https://upload.wikimedia.org/wikipedia/commons/d/d5/Hill_Climbing_with_Simulated_Annealing.gif">gif</a> by [Kingpin13](https://commons.wikimedia.org/wiki/User:Kingpin13) is distributed under <a href="https://creativecommons.org/publicdomain/zero/1.0/deed.en">CC0 1.0</a></i> license.
</center>

## Probability Acceptance Function

$P(E,E_{next},T) = 
    \begin{cases}
       \text{True} &\quad\text{if }  \exp{\frac{-(E_{next}-E)}{T}} \ge random(0,1) \\
       \text{False} &\quad\text{otherwise}\\
     \end{cases}$

This function takes in the current state, the next state and the Temperature , returning a boolean value, which tells our search whether it should move to $s_{next}$ or stay at $s$. Note that for $E_{next} < E$ , this function will always return True. 

```cpp
bool P(double E,double E_next,double T){
    double e = 2.71828;
    double prob = (double)rand()/RAND_MAX; // Generate a random number between 0 and 1
    if(pow(e,-(E_next-E)/T) > prob) return true;
    else return false;
}
```
## Code Template

```cpp
class state{
    public:
    state(){
        // Generate the initial state
    }
    state next(){
        state next;
        next = s;
        // Make changes to the state "next" and then return it
        return next;
    }
    double E(){
        // implement the cost function here
    };
};

pair<int,state> simAnneal(){
    state s = state();
    state best = s;
    double T = 1000; // Initial temperature
    double u = 0.99; // decay rate
    double E = s.E(),E_next;
    double E_best = E;
    while (T > 1){
        state next = s.next();
        E_next = next.E();
        if(P(E,E_next,T)){
            s = next;
            if(E_next < E_best){
                best = s;
                E_best = E_next;
            }
        }
        E = E_next;
        T *= u;
    }
    return {E_best,best};
}

```
## How to use:
Fill in the state class functions as appropriate. If you are trying to find a global maxima and not a minima, ensure that the $E()$ function returns negative of the function you are maximising and finally print out $-E_{best}$. Set the below parameters as per your need.

### Parameters
- $T$ : Temperature. Set it to a higher value if you want the search to run for a longer time
- $u$ : Decay. Decides the rate of cooling. A slower cooling rate (larger value of u) usually gives better results. Ensure $u < 1$. 

The number of iterations the loop will run for is given by the expression

$N =   \lceil -\log_{u}{T} \rceil$ 

To see the effect of decay rate on solution results, run simulated annealing for decay rates 0.95 , 0.97 and 0.99 and see the difference.

### Example State class for TSP
```cpp
class state{
    public:
    vector<pair<int,int>> points;

    state(){ // Initial random order of points
        points = {}; // Fill in some points to start with, or generate them randomly
    }
    state next(){ // picks 2 random indices and swaps them
        state s_next;
        s_next.points = points;
        int a = ((rand()*points.size())/RAND_MAX);
        int b = ((rand()*points.size())/RAND_MAX);
        pair<int,int> t = s_next.points[a];
        s_next.points[a] = s_next.points[b];
        s_next.points[b] = t;
        return s_next;
    }

    double euclidean(pair<int,int> a, pair<int,int> b){ // return euclidean distance between 2 points
        return pow(pow((a.first-b.first),2)+pow((a.second-b.second),2),0.5);
    }
    double E(){ // calculates the round cost of travelling one full circle.
        double dist = 0;
        bool first = true;
        int n = points.size();
        for(int i = 0;i < n; i++){
            dist += euclidean(points[i],points[(i+1)%n]);
        }
        return dist;
    };
};
```

## Extra Modifications to the Algorithm:

- Add a time based exit condition to the while loop to prevent TLE
- You can replace the e value in the Probability Acceptance function to any real number > 1. For a given $E_{next} - E > 0$, a higher e value reduces the chance of accepting that state and a smaller e value, increases it. 


## Problems

- [USACO Jan 2017 - Subsequence Reversal](https://usaco.org/index.php?page=viewproblem2&cpid=698)
- [Deltix Summer 2021 - DIY Tree](https://codeforces.com/contest/1556/problem/H)
- [AtCoder Contest Scheduling](https://atcoder.jp/contests/intro-heuristics/tasks/intro_heuristics_a)