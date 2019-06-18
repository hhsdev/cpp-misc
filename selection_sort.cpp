// selection sort function

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
std::vector<int>::iterator find_smallest(
    const std::vector<int>::iterator& beg,
    const std::vector<int>::iterator& end) {

    int smallest = *beg;
    std::vector<int>::iterator ret = beg;
    for (auto it = beg; it != end; ++it) {
        if (*it < smallest) {
            smallest = *it;
            ret = it;
        }
    }
    return ret;
}

void selection_sort(std::vector<int>& input) {
    const auto end = input.end();
    for (auto it = input.begin(); it != end; ++it) {
        auto smallestIt = find_smallest(it, end);
        std::swap(*it, *smallestIt);
    }
}

int main() {
    std::vector<int> input(100);
    std::iota(input.begin(), input.end(), 0);
    std::default_random_engine e(1);
    std::shuffle(input.begin(), input.end(), e);
    
    selection_sort(input);
    for (auto i : input) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}
