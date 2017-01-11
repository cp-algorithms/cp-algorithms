<!--?title The Optimal Schedule Of Jobs Given Their Deadlines And Durations-->

# The Optimal Schedule Of Jobs Given Their Deadlines And Durations

Suppose, we have a set of jobs, and we are aware of every job’s deadline and its duration. The execution of a job cannot be interrupted prior to its ending. It is required to create such a schedule to accomplish the biggest number of jobs.

## Solving

The algorithm of the solving is **greedy**. Let’s sort all the jobs by their deadlines and look at them in descending order. Also, let’s create a queue $q$, in which we’ll gradually put the jobs and extract one with the least run-time (for instance, we can use set or priority_queue). Initially, $q$ is empty.

Suppose, we’re looking at the $i$-th job. First of all, let’s put it into $q$. Let’s consider the period of time between the deadline of $i$-th job and the deadline of $i-1$-th job. That is the segment of some length $T$. We will extract jobs from $q$ (in their left duration ascending order) and execute them until the whole segment $T$ is filled. Important: if at any moment of time the extracted job can only be partly executed until segment $T$ is filled, then we execute this job partly just as far as possible, i.e., during the $T$-time, and we put the remaining part of a job back into $q$.

On the algorithm’s completion we’ll choose the optimal solution (or, at least, one of several solutions). The running time of algorithm is $O(n \log n)$.

## Implementation

````cpp
int n;
vector < pair<int,int> > a; // jobs as a vector of pairs (deadline, duration)

... reading n and a ...

sort (a.begin(), a.end());

typedef set < pair<int,int> > t_s;
t_s s;
vector<int> result;
for (int i=n-1; i>=0; --i) {
    int t = a[i].first - (i ? a[i-1].first : 0);
    s.insert (make_pair (a[i].second, i));
    while (t && !s.empty()) {
        t_s::iterator it = s.begin();
        if (it->first <= t) {
            t -= it->first;
            result.push_back (it->second);
        }
        else {
            s.insert (make_pair (it->first - t, it->second));
            t = 0;
        }
        s.erase (it);
    }
}

for (size_t i=0; i<result.size(); ++i)
    cout << result[i] << ' ';
````
