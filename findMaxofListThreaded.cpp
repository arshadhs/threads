#include <iostream>
#include<vector>
#include<thread>
#include<atomic>
#include<algorithm>
#include<limits>
#include <bits/stdc++.h>
//#include<time>

using namespace std;

void findMax(const vector<int> &num, size_t start, size_t end, atomic<int>& maxNum)
{
    cout << endl << "Finding Max" << flush;
    int max = 0;
    for (int i = start + 1; i <= end; ++i) {
        if (max < num[i])
            max = num[i];    
    }

    cout << endl << "max = " << max << "\tmaxNum =" << maxNum << flush;
    if (max > maxNum) maxNum = max;
}

int findMaxInParallel (const vector<int> &num) {
    cout << endl << "findingMaxinParallel" << flush;
    if (num.size() == 0) { cerr << "Empty list: "; return -1;}

    // find the number of concurrent threads supported by the available hardware implementation
    const size_t numThreads = thread::hardware_concurrency();
    cout << endl << "numThreads = " << numThreads << flush;

    // divide the vector between threads
    const size_t numSize = num.size() / numThreads;

    vector <thread> t1 (numThreads);
    atomic<int> maxNum = numeric_limits<int>::min();

    //std::this_thread::sleep_for (std::chrono::seconds(1));

    time_t start, end; 
    time(&start); 

    for (int i  = 0; i < numThreads; ++i) {
        size_t start = i * numSize;
        size_t end = (i == numThreads - 1) ? num.size() - 1 : (start + numSize - 1);

        cout << endl << "Range Start:" << start << "\tEnd: " <<end << flush;

        // Start the threads
        t1 [i] = thread(findMax, ref(num), start, end, ref(maxNum));
    }

    // Wait for all threads to finish
    for (int i  = 0; i < numThreads; ++i)
        t1[i].join();

    time(&end);

    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    cout << endl << "Time taken is : " << fixed  << time_taken << setprecision(5); 
    cout << " sec " << endl; 

    return maxNum;
}

int findMaxSimple(const vector<int> &num)
{
    time_t start, end; 
    time(&start); 
    cout << endl << "Finding Max" << flush;
    int max = 0;
    for (int i = 0; i <= num.size() - 1; ++i) {
        if (max < num[i])
            max = num[i];    
    }
    time(&end);

    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    cout << endl << "Time taken (without thread) is : " << fixed  << time_taken << setprecision(5); 
    cout << " sec " << endl; 

    cout << endl << "max = " << max<< flush;
    return max; 
}

int main() {
    vector<int> v;
    int s = INT_MAX;
    for (long long i= 0; i < s; i++)
        v.push_back(rand());
    int max = findMaxInParallel(v);     // With thread
    // int max = findMaxSimple(v);      // Without Thread
    cout << endl << "Maximum of the list of " << s << " is " << max;
}
