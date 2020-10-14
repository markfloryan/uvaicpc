# Where Have You Bin

### Problem
Unfortunately, there is not much of a substitute for reading the actual problem statement. To give a brief summary, you are given a series of labelled bins such that bins with like labels are adjacent. Each bin has an associated cost. You are told that some given subset of bins are going to be removed (free of cost), and you must add some bins. The problem asks you to decide where to place bins and move existing bins (not free of cost) such that all bins remain adjacent to bins of the same time after all operations are done.

## Solution
The key realization here is that thereare only 120 possible orderings for the types of bins (since there are five categories). In theory, it should be very simple to find the associated cost for an end state ordering; compute the best alignment of bins in that ordering such that the minimal moves will be required to result in the ordering, then compute the sum of the cost of all mismatched bins. However, you can have empty bins between labeled bins, as below.

Consider
```
AAAXXXEEEXXXIII
```
and
```
AAAXXXXXXEEEIII
```

where X is an empty bin. Then these are both valid versions of the ordering `AEI`, and it is inefficient to calculate which is optimal naively. To solve this, I used a recursive function (on the set of used labels and current index), which computes the cost of filling out the rest of the bins, assuming the first `idx` bins are already set and the used labels cannot be used anymore.
