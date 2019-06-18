// This is my implementation of insertion sort.
// I believe I was trying to roughly measure the complexity 
// of it by counting how many times std::swap got called. 
// The file properties says it was last modified on 12.1.2019.
// At the time of writing this comment, it is now 17.5.2019.

#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
int insertion_sort(std::vector<int> & vec) {
    int swapCount = 0;
    for (int i = 0; i < vec.size(); ++i) {
	for (int j = i; j > 0 && vec[j] < vec[j-1]; --j) {
		std::swap(vec[j-1], vec[j]);
		++swapCount;
	}
}
return swapCount;
}
int main() {
    std::vector<int> vec(100);
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end());
    for (int i : vec) {
    	std::cout << i << ' ';
    }
    std::cout << "\n-------------------------------\n";
    int swapCount = insertion_sort(vec);
    for (int i : vec) {
    	std::cout << i << ' ';
    }
    std::cout << "\nswap count = " << swapCount << std::endl;;
    return 0;
}
