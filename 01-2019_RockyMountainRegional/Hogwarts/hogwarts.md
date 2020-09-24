# Hogwarts

### Description
[This problem](https://open.kattis.com/problems/hogwarts2) provided two graphs where each vertex had exactly four vertices. The problem asked whether any path from vertex 1 to vertex `n` in the first graph would also lead to vertex `n` in the second graph.

## Solution
I solved this with a depth first search going through both graphs simultaneously. This may be easier to explain with the code I used, so I've included that below. They key to avoiding infinite loops is to check for duplicate states. This means instead of just checking if I'm at a vertex I've already visited, I check if I'm at a combination of vertices in the first and second graphs that I've never seen before.

```c++
/**
 * This recursive function checks if all paths from `onum` to `goal` in the original graph will lead from `nnum` to `goal` in the second graph.
 *
 * original is the first graph, stored as an adjacency list
 * now is the second graph, stored as an adjacency list
 * visited keeps track of which states I have already been in. A state is defined as the combination of onum and nnum
 * onum is the vertex I'm at in the first graph
 * nnum is the vertex I'm at in the second graph
 * goal is the vertex I'm trying to reach
 * valid tracks whether I've made it to `goal` at all.
 */
int hogwarts(int** original, int** now, bool** visited, int onum, int nnum, int goal, bool* valid){
	if(onum == goal && nnum == goal){ // If I'm at the goal in both, then it's possible
		*valid = true;
	}
	if(onum == goal && nnum != goal){ // If I reached the goal in the first graph but not the second, then I need to return failure
		*valid = true;
		return 0;
	}
	if(onum == 0 || nnum == 0){ // If I run into node 0 in either, that means I've given up, so I should indicate that I've reached an end
		return 1;
	}
	if(visited[onum][nnum]){ // If I've visited `onum` in the first and `nnum` in the second at the same time before, return
		return 1;
	}

	visited[onum][nnum] = true; // indiciate I've visited my state

	// take the four possible paths
	for(int i = 0; i < 4; i++){
		auto res{ hogwarts(original, now, visited, original[onum][i], now[nnum][i], goal, valid) };
		if(res == 0){ // if any failed, then I've failed too; return a failure
			return 0;
		}
	}
	return 1;
}```