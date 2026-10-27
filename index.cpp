#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void simulate(vector<int> p, int n, int cap, int type) {
    vector<int> f, time;
    int faults = 0, hits = 0, t = 0;

    for (int i = 0; i < n; i++) {
        auto it = find(f.begin(), f.end(), p[i]);

        if (it != f.end()) {
            hits++;
            if (type == 2)
                time[it - f.begin()] = ++t;
        } else {
            faults++;

            if (f.size() < cap) {
                f.push_back(p[i]);
                time.push_back(++t);
            } else {
                int pos = 0;

                if (type == 1) { // FIFO
                    static int next = 0;
                    pos = next % cap;
                    next++;
                } else if (type == 2) { // LRU
                    pos = min_element(time.begin(),
                                      time.end()) - time.begin();
                } else { // Optimal
                    int farthest = -1;
                    for (int j = 0; j < cap; j++) {
                        int k = i + 1;
                        while (k < n && p[k] != f[j]) k++;
                        if (k > farthest) {
                            farthest = k;
                            pos = j;
                        }
                    }
                }

                f[pos] = p[i];
                time[pos] = ++t;
            }
        }

        cout << p[i] << " : ";
        for (int x : f) cout << x << " ";
        cout << endl;
    }

    cout << "Page Faults = " << faults << endl;
    cout << "Page Hits = " << hits << endl;
}

int main() {
    int n, cap, ch;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> p(n);
    cout << "Enter page reference string: ";
    for (int &x : p) cin >> x;

    cout << "Enter number of frames: ";
    cin >> cap;

    if (n <= 0 || cap <= 0) {
        cout << "Invalid input\n";
        return 0;
    }

    cout << "1.FIFO  2.LRU  3.Optimal\nChoose: ";
    cin >> ch;

    if (ch >= 1 && ch <= 3)
        simulate(p, n, cap, ch);
    else
        cout << "Invalid choice\n";

    return 0;
} 
