---
tags:
  - Translated
e_maxx_link: schedule_with_completion_duration
---

# Optimal schedule of jobs given their deadlines and durations

Suppose, we have a set of jobs, and we are aware of every job’s deadline and its duration. The execution of a job cannot be interrupted prior to its ending. It is required to create such a schedule to accomplish the biggest number of jobs.

## Algorithm

The algorithm of the solving is **greedy**. Let’s sort all the jobs by their deadlines and look at them in descending order. Also, let’s create a queue $q$, in which we’ll gradually put the jobs and extract one with the least run-time (for instance, we can use set or priority_queue). Initially, $q$ is empty.

Suppose, we’re looking at the $i$-th job. First of all, let’s put it into $q$. Let’s consider the period of time between the deadline of $i$-th job and the deadline of $i-1$-th job. That is the segment of some length $T$. We will extract jobs from $q$ (in their left duration ascending order) and execute them until the whole segment $T$ is filled. Important: if at any moment of time the extracted job can only be partly executed until segment $T$ is filled, then we execute this job partly just as far as possible, i.e., during the $T$-time, and we put the remaining part of a job back into $q$.

On the algorithm’s completion we’ll choose the optimal solution (or, at least, one of several solutions). The running time of algorithm is $O(n \log n)$.

## Correctness Proof

### Lemma

Let a list of jobs be sorted by non-decreasing deadlines
$J_1, J_2, \dots, J_k$ with deadlines
$d_1 \le d_2 \le \dots \le d_k$ and durations $t_1, t_2, \dots, t_k$.

If for every $i$ the following condition holds:

$$
\sum_{j=1}^{i} t_j \le d_i,
$$

then executing the jobs sequentially in the order
$J_1, J_2, \dots, J_k$ produces a feasible **non-preemptive schedule**
in which every job finishes before its deadline.

#### Proof

When executing the jobs in this order, the finishing time of job $J_i$
is equal to

$$
\sum_{j=1}^{i} t_j.
$$

By assumption,

$$
\sum_{j=1}^{i} t_j \le d_i,
$$

therefore job $J_i$ finishes no later than its deadline $d_i$.
Since this holds for every $i$, all jobs complete before their
deadlines, and the schedule is feasible without interruption.

### Proof of Algorithm

Let the jobs be sorted by non-decreasing deadlines and denote them as
$J_1, J_2, \dots, J_n$ with deadlines $d_1 \le d_2 \le \dots \le d_n$.
Define $d_0 = 0$.

We process jobs from right to left. For each job $J_i$, consider the time
segment

$$
T = d_i - d_{i-1}.
$$

At step $i$, all jobs $J_i, J_{i+1}, \dots, J_n$ are candidates to be
scheduled before their deadlines. These jobs are stored in a set ordered
by their remaining durations.

During the segment of length $T$, the algorithm repeatedly chooses the job
with the smallest remaining duration $t_j$ from the set.

Two cases arise:

- **If $T \ge t_j$**:  
   The job can be completed entirely within this segment. We execute it,
   remove it from the set, and decrease $T$ by $t_j$.

- **If $T < t_j$**:  
   The job cannot be completed within this segment. In this case we execute
   it for $T$ time units and reduce its remaining duration to $t_j - T$,
   inserting the remaining part back into the set.

Choosing the job with the smallest remaining duration is optimal because,
for a fixed amount of time $T$, executing shorter jobs first maximizes the
number of jobs that can be completed within that time segment.

The greedy algorithm may conceptually execute jobs partially when
filling the segments $T = d_i - d_{i-1}$.
This preemption is only used to determine which jobs can be completed
within the available time.

The algorithm ensures that the total duration of the selected jobs
never exceeds the time available before their deadlines.
Therefore the chosen set of jobs satisfies the condition of the lemma.

Consequently, the selected jobs can be executed non-preemptively
in the order of their deadlines, producing a valid schedule in which
every job finishes before its deadline.

## Implementation

The following function takes a vector of jobs (consisting of a deadline, a duration, and the job's index) and computes a vector containing all indices of the used jobs in the optimal schedule.
Notice that you still need to sort these jobs by their deadline, if you want to write down the plan explicitly.

```{.cpp file=schedule_deadline_duration}
struct Job {
    int deadline, duration, idx;

    bool operator<(Job o) const {
        return deadline < o.deadline;
    }
};

vector<int> compute_schedule(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end());

    set<pair<int,int>> s;
    vector<int> schedule;
    for (int i = jobs.size()-1; i >= 0; i--) {
        int t = jobs[i].deadline - (i ? jobs[i-1].deadline : 0);
        s.insert(make_pair(jobs[i].duration, jobs[i].idx));
        while (t && !s.empty()) {
            auto it = s.begin();
            if (it->first <= t) {
                t -= it->first;
                schedule.push_back(it->second);
            } else {
                s.insert(make_pair(it->first - t, it->second));
                t = 0;
            }
            s.erase(it);
        }
    }
    return schedule;
}
```

## Alternate Algorithm

There is a simpler greedy algorithm to solve this problem.

- Sort the jobs by their deadlines in non-decreasing order.
- We will maintain a set of selected jobs, ordered by their durations (using a data structure like a set or priority queue to quickly access the job with the maximum duration).
- Initialize the total scheduled time to 0.

- For each job in order of non-decreasing deadlines:
    - Add the job's duration to the total scheduled time.
    - Insert the job into the set.
    - If the total scheduled time exceeds the job's deadline, remove the job with the longest duration from the set (which may be the current job itself), and subtract its duration from the total time.

After processing all jobs, the set contains the maximum number of jobs that can be scheduled without violating any deadlines. The jobs should be executed in the order of their deadlines to ensure they meet their deadlines.

The running time of this algorithm is also $O(n \log n)$.

## Correctness Proof

Let the jobs be sorted by non-decreasing deadlines
$J_1, J_2, \dots, J_n$ with deadlines
$d_1 \le d_2 \le \dots \le d_n$.Define $d_0 = 0$.

The algorithm processes the jobs in this order while maintaining a set
$S$ of selected jobs and the total scheduled processing time

$$
T = \sum_{J_j \in S} t_j.
$$

When considering job $J_i$, we tentatively add it to the set and update
$T := T + t_i$.

- If $T \le d_i$, the schedule remains feasible and we keep the job.
- If $T > d_i$, we remove the job with the largest duration from $S$
  and decrease $T$ accordingly.

Removing the job with the largest duration is optimal because it reduces
the total processing time by the greatest amount while removing only one
job, thus maximizing the number of remaining jobs.

After each step the algorithm maintains the invariant

$$
\sum_{J_j \in S} t_j \le d_i.
$$

Therefore the selected jobs satisfy the condition of the [lemma](#lemma). Consequently, executing the jobs in $S$ in the order of
their deadlines produces a feasible non-preemptive schedule in which
every job finishes before its deadline.

## Implementation

The following function implements the alternate approach, taking a vector of jobs and returning the indices of the scheduled jobs in order of their execution.

```{.cpp file=schedule_deadline_duration_alternate}
struct Job {
    int deadline, duration, idx;

    bool operator<(Job o) const {
        return deadline < o.deadline;
    }
};

vector<int> compute_schedule(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end());
    set<pair<int, int>> s;
    int stime = 0;
    for (int i = 0; i < jobs.size(); i++){
        int ti = jobs[i].duration;
        stime += ti;
        s.insert({ti, jobs[i].idx});
        if (stime > jobs[i].deadline){
            auto it = s.end();
            it--;
            stime -= it->first;
            s.erase(it);
        }
    }

    vector<int> schedule;
    for (auto& job : jobs) {
        if (s.find({job.duration, job.idx}) != s.end()) {
            schedule.push_back(job.idx);
        }
    }
    return schedule;
}
```
