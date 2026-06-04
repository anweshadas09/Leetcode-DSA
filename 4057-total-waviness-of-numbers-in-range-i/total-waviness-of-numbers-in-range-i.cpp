class Solution {
public:
    int totalWaviness(int num1, int num2) {
        int ans = 0;

        for (int x = num1; x <= num2; x++) {
            ans += waviness(x);
        }

        return ans;
    }

    int waviness(int x) {
        vector<int> d;

        while (x > 0) {
            d.push_back(x % 10);
            x /= 10;
        }

        int n = d.size();

        if (n < 3) {
            return 0;
        }

        int cnt = 0;

        for (int i = 1; i < n - 1; i++) {
            if ((d[i] > d[i - 1] && d[i] > d[i + 1]) ||
                (d[i] < d[i - 1] && d[i] < d[i + 1])) {
                cnt++;
            }
        }

        return cnt;
    }
};