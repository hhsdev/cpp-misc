// Answering a redditor's question to review
// his code

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

//if one element its max and min
//divide and conquer
struct values {
    int max, min;
};

// counters to keep track of how much each function is called
int maxCallCount1 = 0;
int minCallCount1 = 0;

int minCallCount2 = 0;
int maxCallCount2 = 0;

int findCallCount1 = 0;
int findCallCount2 = 0;

// wrapper functions for std::min and std::max to
int customMax1(int a, int b) {
    ++maxCallCount1;
    return std::max(a, b);
}

int customMin1(int a, int b) {
    ++minCallCount1;
    return std::min(a, b);
}

int customMax2(int a, int b) {
    ++maxCallCount2;
    return std::max(a, b);
}

int customMin2(int a, int b) {
    ++minCallCount2;
    return std::min(a, b);
}

struct values findMinMax(vector<int> &a, int start, int end) {
    ++findCallCount1;
    if (a.empty()) return values{0, 0};
    if(start < end) {
        int mid = (start + end) / 2;
        //recursive calls on both halfs to get min, max values
        struct values left_res = findMinMax(a, start, mid);
        struct values right_res = findMinMax(a, mid+1, end);
        
        //compare left and right values and set for min,
        //max for entire length
        struct values final_res;
        final_res.min = customMin1(left_res.min, right_res.min);
        final_res.max = customMax1(left_res.max, right_res.max);
        return final_res;
    } else {
        //if only one value is there, then it is the both min,
        //and max;
        struct values final_res;
        final_res.min = final_res.max = a[start];
        return final_res;
    }
}


// version of findMinMax with 2 exit condition
values findMinMax2(vector<int> &a, int start, int end) {
    ++findCallCount2;
    if (a.empty()) return values{0, 0};
    struct values final_res;
    // if there's only two elements, directly compare them
    if (end-start == 1) {
        final_res.min = customMin2(a[start], a[end]);
        final_res.max = customMax2(a[start], a[end]);
        return final_res;
    }
    // if there's only one element, it's both max and min
    else if (end == start) {
        final_res.min = final_res.max = a[start];
        return final_res;
    }
    // else you know the drill: divide and conquer
    else {
        int mid = (end + start) / 2;
        struct values left_res = findMinMax2(a, start, mid);
        struct values right_res = findMinMax2(a, mid+1, end);
        
        struct values final_res;
        final_res.min = customMin2(left_res.min, right_res.min);
        final_res.max = customMax2(left_res.max, right_res.max);
        return final_res;
    }
}

// function to show that above way of finding min
// and max is terrible in practice
values findMinMax3(vector<int>& a) {
    if (a.empty()) return values{0, 0};
    int minimum = a[0];
    int maximum = a[0];
    for (int i = 0; i < a.size(); ++i) {
        if (minimum > a[i]) minimum = a[i];
        if (maximum < a[i]) maximum = a[i];
    }
    return values{ maximum, minimum };
}

int main() {
    using namespace std::chrono;
    high_resolution_clock clock;
    const int sampleSize = 25000000;
    // generate lots of random integers and put it into the vec
    // clock.now() just a function to time the performance:
    // can be safely ignored
    vector<int> vec;
    auto generateStart = clock.now();
    generate_n(back_inserter(vec), sampleSize, rand);
    auto generateEnd = clock.now();
    
    auto oneStart = clock.now();
    struct values res = findMinMax(vec, 0, vec.size()-1);
    auto oneEnd = clock.now();
    
    auto twoStart = clock.now();
    struct values res2 = findMinMax2(vec, 0, vec.size()-1);
    auto twoEnd = clock.now();
    
    auto threeStart = clock.now();
    struct values res3 = findMinMax3(vec);
    auto threeEnd = clock.now();

    cout << "Testing with " << sampleSize << " elements" << endl;
    cout << "Generating random numbers took "
         << duration_cast<milliseconds>
            (threeEnd-threeStart).count()
         << " ms" <<endl;
    cout << "--------------------------------------------\n";
    
    cout << "min  : " << res.min << ", "
         << "max  : " << res.max << endl;
    cout << "min2 : " << res2.min << ", "
         << "max2 : " << res2.max << endl;
    cout << "--------------------------------------------\n";
    
    cout << "called min " << minCallCount1 << " times" << endl;
    cout << "called max " << maxCallCount1 << " times" << endl;
    cout << "--------------------------------------------\n";
    
    cout << "called min2 " << minCallCount2 << " times" << endl;
    cout << "called max2 " << maxCallCount2 << " times" << endl;
    cout << "--------------------------------------------\n";
    
    cout << "called findMinMax "
         << findCallCount1 << " times" << endl;
    cout << "called findMinMax2 "
         << findCallCount2 << " times" << endl;
    cout << "--------------------------------------------\n";
    
    cout << "Time taken with findMinMax: "
         << duration_cast<milliseconds>(oneEnd-oneStart).count()
         << " ms" << endl;
    cout << "--------------------------------------------\n";
    
    cout << "Time taken with findMinMax2: "
         << duration_cast<milliseconds>(twoEnd-twoStart).count()
         << " ms" <<endl;
    cout << "--------------------------------------------\n";
    cout << "Time taken with findMinMax3: "
         << duration_cast<milliseconds>
            (threeEnd-threeStart).count()
         << " ms" <<endl;
    return 0;
}
