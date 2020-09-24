#include <cstdlib>
#include <iostream>

int hogwarts(int** original, int** now, bool** visited, int onum, int nnum, int goal, bool* valid){
	if(onum == goal && nnum == goal){
		*valid = true;
	}
	if(onum == goal && nnum != goal){
		*valid = true;
		return 0;
	}
	if(onum == 0 || nnum == 0){
		return 1;
	}
	if(visited[onum][nnum]){
		return 1;
	}

	visited[onum][nnum] = true;

	for(int i = 0; i < 4; i++){
		auto res{ hogwarts(original, now, visited, original[onum][i], now[nnum][i], goal, valid) };
		if(res == 0){
			return 0;
		}
	}
	return 1;
}


// ignore the memory leaks; this is for a programming competition, so it doesn't matter.
int main(){
	int size;
	std::cin >> size;

	int** original = (int**) malloc(sizeof(int*) * (size + 1));
	int** now = (int**) malloc(sizeof(int*) * (size + 1));
	bool** visited = (bool**) malloc(sizeof(bool*) * (size + 1));

	for(int i = 1; i <= size; i++){
		original[i] = (int*) malloc(4 * sizeof(int));
		visited[i] = (bool*) malloc((size + 1) * sizeof(bool));
		memset(visited[i], 0, (size + 1) * sizeof(bool));
		std::cin >> original[i][0] >> original[i][1] >> original[i][2] >> original[i][3];
	}

	for(int i = 1; i <= size; i++){
		now[i] = (int*) malloc(4 * sizeof(int));
		std::cin >> now[i][0] >> now[i][1] >> now[i][2] >> now[i][3];
	}

	bool valid = false;
	auto res = hogwarts(original, now, visited, 1, 1, size, &valid);

	if(!valid){
		std::cout << "Impossible" << std::endl;
	} else{
		if(res == 0){
			std::cout << "No" << std::endl;
		} else{
			std::cout << "Yes" << std::endl;
		}
	}
}
