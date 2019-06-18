#include <iostream>
#include <random>
#include <utility>
#include <algorithm>
// input: a vector of points
struct Point {
    int x;
    int y;
};
inline int square(int i) { return i * i; }
inline double distance(const Point& a, const Point& b) {
    return sqrt(square(abs(a.x - b.x))
              + square(abs(a.y - b.y)));
}

std::vector<double> calculate_all_distances(
        const std::vector<Point>& input) {
    std::vector<double> ret;
    for (int i = 0; i < input.size(); ++i) {
        for (int j = i+1; j < input.size(); ++j) {
            ret.push_back(distance(input[i], input[j]));
        }
    }
    return ret;
}

double get_distance(size_t indexA, size_t indexB,
                    const std::vector<double>& input,
                    const size_t numOfPoints) {
    if (indexA == indexB) return 0;
    if (indexA > indexB) std::swap(indexA, indexB);
    const int sz = numOfPoints;
    const int index = ((indexA * (2*sz - indexA - 1)) / 2)
                  + (indexB - indexA) - 1;
    return input[index];
}

std::vector<double> get_distances_wrt(
    size_t index,
    const std::vector<double>& input,
    const size_t numOfPoints) {

    std::vector<double> ret;
    for (int i = 0; i < numOfPoints; ++i) {
        ret.push_back(get_distance(index,
                                   i,
                                   input,
                                   numOfPoints));
    }
    return ret;
}
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}


void nearest_neighbour(std::vector<Point>& input) {
    if (input.empty()) {
        std::cerr << "Empty Input\n";
        return;
    }
    std::cout << "input: ";
    for (auto p : input) {
        std::cout << p << ' ';
    }
    std::cout << std::endl;
    auto distances = calculate_all_distances(input);
    auto distances_wrt_0 = get_distances_wrt(0,
            distances,
            input.size());
    std::cout << "All distances w.r.t. first point: ";
    for (auto d : distances_wrt_0)
        std::cout << d << ' ';
    std::cout << std::endl;
    // find the nearest point
    for (auto it = input.begin(); it != input.end()-1; ++it) {
        const Point currentPoint = *it;
        std::cout << "Current Point: " << currentPoint << "\n";
        auto nearestPoint =
            std::min_element(it + 1, input.end(),
                            [&currentPoint](const Point& a,
                                            const Point& b) {
                return distance(currentPoint, a)
                     < distance(currentPoint, b);
            });
        std::cout << "Nearest Point to "
                  << currentPoint << ": "
                  << *nearestPoint << std::endl;

        std::cout << "Distance: "
                  << distance(currentPoint, *nearestPoint);
        std::cout << "\n-----\n";
        std::swap(*(it+1), *nearestPoint);
    }
}

int main() {
    std::vector<Point> vec(10);
    std::default_random_engine e;
    std::uniform_int_distribution<> ud(0, 100);
    for (auto & i : vec) {
        i.x = ud(e);
        i.y = ud(e);
    }
    nearest_neighbour(vec);
    for (auto & i : vec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}
