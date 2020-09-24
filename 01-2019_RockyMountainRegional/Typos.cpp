#include <iostream>
#include <vector>
#include <cstring>

struct chartree {
	chartree* subtrees[26];
	bool end;

	chartree(){
		memset(subtrees, 0, 26 * sizeof(chartree*));
		end = false;
	}
};

bool trav(chartree* tree, const char* string){
	if(!*string){
		return tree->end;
	} else{
		if(tree->subtrees[*string - 'a']){
			return trav(tree->subtrees[*string - 'a'], string + 1);
		}
		return false;
	}
}

bool travbranch(chartree* tree, const char* string){
	if(!*string){
		return false;
	} else{
		if(tree->subtrees[*string - 'a']){
			if(travbranch(tree->subtrees[*string - 'a'], string + 1)){
				return true;
			}
		}
		if(string[1] && tree->subtrees[string[1] - 'a']){
			return trav(tree->subtrees[string[1] - 'a'], string + 2);
		} else if(!string[1]){
			return tree->end;
		}
		return false;
	}
}

void insert(chartree* tree, const char* string){
	if(*string){
		if(!tree->subtrees[*string - 'a']){
			tree->subtrees[*string - 'a'] = new chartree();
		}
		insert(tree->subtrees[*string - 'a'], string + 1);
	} else{
		tree->end = true;
	}
}

void problemJ(){
	int n;
	std::cin >> n;

	chartree base{};
	std::vector<std::string> strings{};
	for(int i = 0; i < n; i++){
		std::string s;
		std::cin >> s;
		strings.emplace_back(s);
		insert(&base, s.c_str());
	}

	bool any = false;
	for(const auto& s : strings){
		if(travbranch(&base, s.c_str())){
			any = true;
			std::cout << s << std::endl;
		}
	}

	if(!any){
		std::cout << "NO TYPOS" << std::endl;
	}
}
