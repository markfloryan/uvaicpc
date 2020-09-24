#include <iostream>
#include <utility>

std::pair<int, int> veclf[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
void recurse(int x, int y, int map[6][6][3], int valf, int vala, int dir, bool* visited, bool layout[6][6]){
	if(visited[vala]){
		return;
	}

	visited[vala] = true;

	int* dst = map[vala][valf];

	std::pair<int, int> newl{ x + veclf[(dir + 3) % 4].first, y + veclf[(dir + 3) % 4].second };
	std::pair<int, int> newf{ x + veclf[dir].first, y + veclf[dir].second };
	std::pair<int, int> newr{ x + veclf[(dir + 1) % 4].first, y + veclf[(dir + 1) % 4].second };

	if(newl.first >= 0 && newl.first < 6 && newl.second >= 0 && newl.second < 6){
		if(layout[newl.first][newl.second]){
			recurse(newl.first, newl.second, map, vala, dst[0], (dir + 3) % 4, visited, layout);
		}
	}
	if(newf.first >= 0 && newf.first < 6 && newf.second >= 0 && newf.second < 6){
		if(layout[newf.first][newf.second]){
			recurse(newf.first, newf.second, map, vala, dst[1], dir, visited, layout);
		}
	}
	if(newr.first >= 0 && newr.first < 6 && newr.second >= 0 && newr.second < 6){
		if(layout[newr.first][newr.second]){
			recurse(newr.first, newr.second, map, vala, dst[2], (dir + 1) % 4, visited, layout);
		}
	}
}

void problemB(){
	bool layout[6][6];
	int x, y;

	for(int i = 0; i < 6; i++){
		std::string line;
		std::getline(std::cin, line);
		for(int j = 0; j < 6; j++){
			if(line[j] == '.'){
				layout[j][i] = false;
			} else{
				layout[j][i] = true;
				x = j;
				y = i;
			}
		}
	}

	int map[6][6][3] = {
		{
			{ 0, 0, 0 }, 
			{ 5, 3, 4 },
			{ 0, 0, 0 }, 
			{ 4, 1, 5 },
			{ 1, 5, 3 },
			{ 3, 4, 1 },
		},
		{
			{ 4, 2, 5 }, 
			{ 0, 0, 0 },
			{ 5, 0, 4 },
			{ 0, 0, 0 },
			{ 2, 5, 0 },
			{ 0, 4, 2 },
		},
		{
			{ 0, 0, 0 },
			{ 4, 3, 5 },
			{ 0, 0, 0 },
			{ 5, 1, 4 },
			{ 3, 5, 1 },
			{ 1, 4, 3 },
		},
		{
			{ 5, 2, 4 },
			{ 0, 0, 0 },
			{ 4, 0, 5 },
			{ 0, 0, 0 },
			{ 0, 5, 2 },
			{ 2, 4, 0 },
		},
		{
			{ 3, 2, 1 },
			{ 0, 3, 2 },
			{ 1, 0, 3 },
			{ 2, 1, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 0 },
		},
		{
			{ 1, 2, 3 },
			{ 2, 3, 0 },
			{ 3, 0, 1 },
			{ 0, 1, 2 },
			{ 0, 0, 0 },
			{ 0, 0, 0 },
		},
	};

	bool success = false;
	for(int i = 1; i < 6; i++){
		if(i == 2) continue;
		for(int j = 0; j < 4; j++){
			bool visited[6]{ 0,0,0,0,0,0 };
			recurse(x, y, map, i, 0, j, visited, layout);
			success = true;
			for(int k = 0; k < 6; k++){
				success &= visited[k];
			}
			if(success){
				break;
			}
		}
	}

	std::cout << "can" << (success ? "" : "not") << " fold" << std::endl;
}
