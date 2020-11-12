#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define endl '\n'
#define DEBUG(x) do { cerr << #x << ": " << x << endl; } while (0)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int P, K;
    int nums[12];
    int ans = 0;
    string str;

    getline(cin, str);
    stringstream(str) >> P;

    for (int p = 0; p < P; ++p) {
        getline(cin, str);
        stringstream ss(str);
        ss >> K; // actual garbage
        for (int i = 0; i < 12; ++i) ss >> nums[i];

        ans = 0;

        for (int i = 1; i < 11; ++i) {
            int lo = nums[i];
            for (int j = i; j < 11 && nums[j] > nums[i - 1]; ++j) {
                lo = min(lo, nums[j]);
                if (lo > nums[j + 1]) ++ans;
            }
        }

        cout << K << " " << ans << endl;
    }

    return 0;
}
