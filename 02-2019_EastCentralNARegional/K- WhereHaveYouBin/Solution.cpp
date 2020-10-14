#include <iostream>
#include <cstdlib>

int* types = nullptr;
int* costs = nullptr;
int* memoization = nullptr;
int initial;
int end;
int aftercounts[5];

// skipped is just passed as a precomputed value; for a given `used` and `idx1`, there is only one possible value for
// `skipped`. Therefore, it doesn't need to be memoized
int synthesize(int used, int idx1, int skipped){
    if(used == 0x1F || idx1 == initial){
        return 0;
    } else{
        if(memoization[idx1 * 32 + used] != -1){
            return memoization[idx1 * 32 + used];
        }
        int min = -1;
        for(int k = 0; k < 5; k++){
            if(!(used & (1 << k))){
                used |= (1 << k);
                int cost = 0;
                for(int j = 0; j < initial; j++){
                    if(types[j] == k && (j < idx1 || j >= idx1 + aftercounts[k])){
                        cost += costs[j];
                    }
                }
                for(int i = 0; i <= initial - end - skipped; i++){
                    if(i != 0 && types[idx1 + i - 1] == k){
                        cost += costs[idx1 + i - 1];
                    }
                    if(i != 0 && types[idx1 + aftercounts[k] + i - 1] == k){
                        cost -= costs[idx1 + aftercounts[k] + i - 1];
                    }
                    int res = cost + synthesize(used, idx1 + aftercounts[k] + i, skipped + i);
                    if(res < min || min == -1){
                        min = res;
                    }
                }
                used &= ~(1 << k);
            }
        }
        memoization[idx1 * 32 + used] = min;
        return min;
    }
}

int main(){
    std::string s;
    std::cin >> s;
    initial = s.size();
    types = (int*) malloc(s.size() * sizeof(int));
    costs = (int*) malloc(s.size() * sizeof(int));
    memoization = (int*) malloc((initial) * 32 * sizeof(int));
    for(int i = 0; i < (initial) * 32; i++){
        memoization[i] = -1;
    }
    int map[26];
    map['A' - 'A'] = 0;
    map['E' - 'A'] = 1;
    map['I' - 'A'] = 2;
    map['O' - 'A'] = 3;
    map['U' - 'A'] = 4;
    map['X' - 'A'] = -1;
    for(int i = 0; i < initial; i++){
        types[i] = map[s[i] - 'A'];
        if(s[i] != 'X')
            aftercounts[map[s[i] - 'A']]++;
    }
    for(int i = 0; i < initial; i++){
        std::cin >> costs[i];
    }
    int rem;
    std::cin >> rem;
    for(int i = 0; i < rem; i++){
        int torem;
        std::cin >> torem;
        torem--;
        costs[torem] = -1;
        types[torem] = -1;
        aftercounts[map[s[torem] - 'A']]--;
    }
    s.clear();
    std::cin >> s;
    if(s != "X"){
        for(char c : s){
            aftercounts[map[c - 'A']]++;
        }
    }
    end = aftercounts[0] + aftercounts[1] + aftercounts[2] + aftercounts[3] + aftercounts[4];
    std::cout << synthesize(0, 0, 0) << std::endl;
}