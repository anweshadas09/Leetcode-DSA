class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());

        long long currMass = mass;

        for (int &m : asteroids) {
            if (currMass < m) {
                return false;
            }
            else if (currMass >= m) {
                currMass += m;
            }
        }

        return true;
    }
};