#include <iostream>
#include <sstream>

#define endl '\n'
#define DEBUG(x) do { cerr << #x << ": " << x << endl; } while (0)

using namespace std;

struct element {
    bool isSlash;
    short first = 0;
    short second = 0;

    bool conflict(const element& other) {
		if (first == 0 || other.first == 0) return false;
		if (first == other.first) return true;
		if (isSlash) {
			if (second == other.first) return true;
			if (other.isSlash && second == other.second) return true;
		}
		if (other.isSlash && other.second == first) return true;
		return false;
    }
};

bool isValid(element grid[6][6], int row, int col, element val) {
	// check entire column
	for (int r = 0; r < 6; ++r) {
		if (r != row && grid[r][col].conflict(val)) return false;
	}

	// check entire row
	for (int c = 0; c < 6; ++c) {
		if (c != col && grid[row][c].conflict(val)) return false;
	}

	// check box
	int rr = 2*(row / 2), cc = 3*(col / 3);
	for (int r = rr; r < rr + 2; ++r) {
		for (int c = cc; c < cc + 3; ++c) {
			if ((r != row || c != col) && grid[r][c].conflict(val)) return false;
		}
	}

    return true;
}

bool solve(element grid[6][6], int row, int col) {
    if (row == 6) return true; // Reached end
    int newCol = (col + 1) % 6;
    int newRow = row; if (newCol == 0) ++newRow;

	// check which values we need to set
    bool solve1 = grid[row][col].first == 0;
    bool solve2 = grid[row][col].isSlash && grid[row][col].second == 0;

	// find bounds for setting first value (above slash)
	int lo1 = (solve1) ? 1 : grid[row][col].first;
    int hi1 = (solve1) ? (!solve2 && grid[row][col].isSlash ? grid[row][col].second - 1 : 9)
                       : grid[row][col].first;

	for (int i = lo1; i <= hi1; ++i) {
		// find bounds for setting second value (below slash)
		int lo2 = (solve2) ? i + 1 : grid[row][col].second;
		int hi2 = (solve2) ? 9 : grid[row][col].second;

		for (int j = lo2; j <= hi2; ++j) {
			grid[row][col].first = i;
			grid[row][col].second = j;

			if (isValid(grid, row, col, grid[row][col])) {
				if (solve(grid, newRow, newCol)) return true;
			}
		}
	}

	// reset values if failed
	if (solve1) grid[row][col].first = 0;
	if (solve2) grid[row][col].second = 0;

	return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    element grid[6][6];
    string str;

    for (int r = 0; r < 6; ++r) {
        getline(cin, str);
        stringstream ss(str);
        for (int c = 0; c < 6; ++c) {
            string tmp;
            ss >> tmp;
            if (tmp.size() == 3) {
                grid[r][c].first = (tmp[0] == '-') ? 0 : tmp[0] - '0';
                grid[r][c].second = (tmp[2] == '-') ? 0 : tmp[2] - '0';
                grid[r][c].isSlash = true;
            } else {
                grid[r][c].first = (tmp[0] == '-') ? 0 : tmp[0] - '0';
                grid[r][c].isSlash = false;
            }
        }
    }

    solve(grid, 0, 0);

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (grid[i][j].isSlash) cout << (int)grid[i][j].first << "/" << (int)grid[i][j].second << " ";
            else cout << (int)grid[i][j].first << " ";
        }
        cout << endl;
    }

    return 0;
}
