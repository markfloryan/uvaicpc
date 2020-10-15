# BioTrip 

### Problem
Given a graph under the constraint that in order to go from one edge to another, they must be within a certain angle of each other, find the shortest path to a given node and back. 

## Solution
Depending on which edge you come from, you may have different edges availabe at the same vertex. In effect, a vertex really can be thought of as connecting two edges. Swapping edges and vertices creates an "edge dual" graph, and finding the shortest path from the start to the end and back on the edge dual gives you the solution to this problem.

My implementation didn't fully swap the two, but the recursive solving component is built on this idea.