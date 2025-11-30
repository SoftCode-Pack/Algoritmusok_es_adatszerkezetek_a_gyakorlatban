
/*
// TUL LASSU PROBALKOZAS
int main () {


    int teszt_szama;
    cin >> teszt_szama;

    for (int i = 0; i < teszt_szama; i++) {
        priority_queue<int, vector<int>, less<int>> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        while (true) {
            long long input;
            cin >> input;

            if (input == 0) break;

            if (input == -1) {
                cout << maxHeap.top() << endl;
                maxHeap.pop();
                if (maxHeap.size() + 1 == minHeap.size()) {
                    maxHeap.push(minHeap.top());
                    minHeap.pop();
                }
            }
            else {
                if (maxHeap.empty()) maxHeap.push(input);
                else {
                    if (maxHeap.top() >= input) { // mediannal kisebbet szurunk be
                        if (maxHeap.size() == minHeap.size()) {
                            maxHeap.push(input);
                        }
                        else if (maxHeap.size() == minHeap.size() + 1) {
                            maxHeap.push(input);
                            minHeap.push(maxHeap.top());
                            maxHeap.pop();

                        }
                    }
                    else if (maxHeap.top() < input) { // mediannal nagyobbat szurunk be
                        if (maxHeap.size() == minHeap.size()) {
                            minHeap.push(input);
                            maxHeap.push(minHeap.top());
                            minHeap.pop();
                        }
                        else if (maxHeap.size() == minHeap.size() + 1) {
                            minHeap.push(input);

                        }
                    }
                }
            }
        }
    }
}
*/


#include <iostream>
#include <queue>

using namespace  std;

void kiegyensulyozas(priority_queue<int>& maxHeap, priority_queue<int, vector<int>, greater<int>>& minHeap) {
    if (maxHeap.size() < minHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
    else if (maxHeap.size() == minHeap.size() + 2) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int teszt_szama;
    cin >> teszt_szama;

    for (int i = 0; i < teszt_szama; i++) {
        priority_queue<int, vector<int>, less<int>> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        while (true) {
            long long input;
            cin >> input;

            if (input == 0) break;

            if (input == -1) {
                cout << maxHeap.top() << '\n';
                maxHeap.pop();
            }
            else {
                if (maxHeap.empty() or maxHeap.top() >= input) { // mediannal kisebbet szurunk be
                    maxHeap.push(input);
                }

                else { // mediannal nagyobbat szurunk be
                    minHeap.push(input);
                }


            }
            kiegyensulyozas(maxHeap, minHeap);
        }
    }
    return 0;

}