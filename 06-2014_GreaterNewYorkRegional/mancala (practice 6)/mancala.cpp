#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#define endl '\n'
#define DEBUG(x) do { cerr << #x << ": " << x << endl; } while (0)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int P, N, K, memo[2001][80];
    string str;

    memset(memo, 0, 2001*80*sizeof(int));

    getline(cin, str);
    stringstream(str) >> P;

    // precompute
    for (int n = 1; n <= 2000; ++n) {
        int idx;
        for (idx = 0; idx < 80 && memo[n-1][idx] != 0; ++idx) {
            memo[n][idx] = memo[n-1][idx] - 1;
        }

        memo[n][idx] = idx + 1;

		++idx;

        for (; idx < 80; ++idx) memo[n][idx] = memo[n-1][idx];

    }

    for (int p = 0; p < P; ++p) {
        getline(cin, str);
        stringstream(str) >> K >> N;

        // find latest idx
        int end = 80;
        while (memo[N][end-1] == 0) --end;
        cout << K << " " << end << endl;

        for (int i = 0; i < end; ++i) {
            if (i > 0 && i % 10 == 0) cout << endl;
            cout << memo[N][i] << " ";
        }
        cout << endl;
    }

    return 0;
}
