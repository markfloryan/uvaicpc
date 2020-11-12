#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

#define endl '\n'
#define DEBUG(x) do { cerr << #x << ": " << x << endl; } while (0)

using namespace std;

char grid[25][25] = {0};
char grid2[25][25] = {0};

void transpose(int n, int m) {
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            grid2[col][row] = grid[row][col];
        }
    }

    swap(grid, grid2);
}

void flipVertical(int n, int m) {
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            grid2[(n - 1) - row][col] = grid[row][col];
        }
    }

    swap(grid, grid2);
}

void flipHorizontal(int n, int m) {
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            grid2[row][(m - 1) - col] = grid[row][col];
        }
    }

    swap(grid, grid2);
}

vector<vector<int>> solve(int n, int m) {
    int target = n*m;

    vector<vector<int>> solutions;

    // check horizontal folds
    // fold along just below [row][0] to [row][m-1]
    for (int row = 0; row < n-1; ++row) {
        int sum = 0;

        //find squares affected by fold
        int dist = min(1 + row, n - row - 1);

        // fold over those squares
        for (int d = 0; d < dist; ++d) { // distance from fold
            for (int col = 0; col < m; ++col) {
                if (grid[row - d][col] == '#' ^ grid[row + d + 1][col] == '#') sum += 2;
            }
        }

        // add up the rest
        int lo = (dist == 1 + row) ? row + dist + 1 : 0;
        int hi = (dist == 1 + row) ? n : row - (dist - 1);
        for (int restRow = lo; restRow < hi; ++restRow) {
            for (int col = 0; col < m; ++col) {
                if (grid[restRow][col] == '#') ++sum;
            }
        }

        if (sum == target) solutions.push_back({row+1, 1, row+1, m});
    }

    // check diagonal down folds, along rows
    for (int row = 0; row < n; ++row) {
        int sum = 0;

        // find squares affected by the fold
        int dist = min(n - row, m);

        // fold over those squares
        for (int foldRow = row; foldRow < row + dist; ++foldRow) {
            for (int col = foldRow - row; col < dist; ++col) {
                int d = col - (foldRow - row);

                if (d == 0) {
                    if (grid[foldRow][col] == '#') ++sum;
                } else {
                    if (grid[foldRow][col] == '#' ^ grid[foldRow + d][col - d] == '#') sum += 2;
                }

                ++d;
            }
        }

        // remaining cells above
        for (int restRow = 0; restRow < row; ++restRow) {
            for (int col = 0; col < m; ++col) {
                if (grid[restRow][col] == '#') ++sum;
            }
        }

        // remaining cells below
        for (int restRow = row + dist; restRow < n; ++restRow) {
            for (int col = 0; col < m; ++col) {
                if (grid[restRow][col] == '#') ++sum;
            }
        }

        // remaining cells to right
        for (int restRow = row; restRow < row + dist; ++restRow) {
            for (int col = dist; col < m; ++col) {
                if (grid[restRow][col] == '#') ++sum;
            }
        }

        if (sum == target) solutions.push_back({row + 1, 1, row + dist, dist});
    }

    return solutions;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    string str;

    getline(cin, str);
    stringstream(str) >> n >> m;

    for (int row = 0; row < n; ++row) {
        getline(cin ,str);
        stringstream ss(str);
        for (int col = 0; col < m; ++col) {
            ss >> grid[row][col];
        }
    }

    // try flipping and transpose for symmetry
    vector<vector<int>> tmp;
    vector<vector<int>> tmp2;

    vector<vector<int>> solutions = solve(n, m);

    flipHorizontal(n, m);
    tmp = solve(n, m);
    for (auto v : tmp) {
        solutions.push_back({v[0], m + 1 - v[1], v[2], m + 1 - v[3]});
    }
    flipHorizontal(n, m);

    flipVertical(n, m);
    tmp = solve(n, m);
    for (auto v : tmp) {
        solutions.push_back({n + 1 - v[0], v[1], n + 1 - v[2], v[3]});
    }
    flipVertical(n, m);


    // We might have to transpose first . . .
    transpose(n, m);

    tmp = solve(m, n);

    flipHorizontal(m, n);
    tmp2 = solve(m, n);
    for (auto v : tmp2) {
        tmp.push_back({v[0], n + 1 - v[1], v[2], n + 1 - v[3]});
    }
    flipHorizontal(m, n);

    flipVertical(m, n);
    tmp2 = solve(m, n);
    for (auto v : tmp2) {
        tmp.push_back({m + 1 - v[0], v[1], m + 1 - v[2], v[3]});
    }
    flipVertical(m, n);

    for (auto v : tmp) {
        solutions.push_back({v[1], v[0], v[3], v[2]});
    }

    transpose(m, n);

    // Get best possible answer
    auto cmp = [](vector<int>& v1, vector<int>& v2) {
        int i = 0;
        while (i < v1.size() && v1[i] == v2[i]) ++i;
        return v1[i] < v2[i];
    };

    for (int i = 0; i < solutions.size(); ++i) {
        if (solutions[i][1] == solutions[i][3]) {
            // topmost first
            if (solutions[i][0] > solutions[i][2]) {
                swap(solutions[i][0], solutions[i][2]);
                swap(solutions[i][1], solutions[i][3]);
            }
        } else {
            // leftmost first
            if (solutions[i][1] > solutions[i][3]) {
                swap(solutions[i][0], solutions[i][2]);
                swap(solutions[i][1], solutions[i][3]);
            }
        }
    }

    sort(solutions.begin(), solutions.end(), cmp);
    cout << solutions[0][0] << " " << solutions[0][1] << " " << solutions[0][2] << " " << solutions[0][3] << endl;

    return 0;
}
