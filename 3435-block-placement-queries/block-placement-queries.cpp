class FenwickTree {
public:
    vector<int> bit;

    FenwickTree(int n) {
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        while (idx < bit.size()) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res = max(res, bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int limit = min(50000, (int)queries.size() * 3);

        set<int> obstacles = {0, limit};
        FenwickTree ft(limit + 2);

        // Add all obstacles first
        for (auto &q : queries) {
            if (q[0] == 1) {
                obstacles.insert(q[1]);
            }
        }

        // Build initial gaps
        for (auto it = obstacles.begin(); next(it) != obstacles.end(); ++it) {
            int l = *it;
            int r = *next(it);
            ft.update(r, r - l);
        }

        vector<bool> ans;

        // Process queries in reverse
        for (int i = queries.size() - 1; i >= 0; i--) {
            auto &q = queries[i];

            if (q[0] == 1) {
                int x = q[1];

                auto it = obstacles.find(x);

                int left = *prev(it);
                int right = *next(it);

                ft.update(right, right - left);

                obstacles.erase(it);
            } else {
                int x = q[1];
                int sz = q[2];

                auto it = obstacles.upper_bound(x);
                int prevObstacle = *prev(it);

                bool possible =
                    (ft.query(prevObstacle) >= sz) ||
                    (x - prevObstacle >= sz);

                ans.push_back(possible);
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};