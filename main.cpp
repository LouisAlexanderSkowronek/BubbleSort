#include <vector>
#include <type_traits>
#include <stdexcept>
#include <iostream>

template<typename T>
void pop_min(std::vector<T>& src, std::vector<T>& dst)
{
    if (src.size() == 0) { throw std::length_error("Expected src to have a size of at least 1!"); }

    T min_value = src[0];

    std::vector<unsigned> idxs;

    for (unsigned i = 0; i < src.size(); i++)
    {
        if (src[i] < min_value)
        {
            min_value = src[i];
            idxs.clear();
            idxs.push_back(i);
        } else if (src[i] == min_value)
        {
            idxs.push_back(i);
        }
    }

    for (auto it = idxs.rbegin(); it != idxs.rend(); it++)
    {
        dst.push_back(min_value);
        src.erase(src.begin() + *it);
    }
}

template<typename T>
std::vector<T> sorted(std::vector<T> arr)
{
    std::vector<T> ret;
    ret.reserve(arr.size());

    while (arr.size() > 0)
    {
        pop_min(arr, ret);
    }

    return ret;
}

template<typename T>
void print_vector(const std::vector<T>& vec)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        if constexpr (std::is_same<T, int>::value) { printf("%d", vec[i]); }
        else if constexpr (std::is_same<T, unsigned>::value) { printf("%d", vec[i]); }
        else if constexpr (std::is_same<T, float>::value) { printf("%f", vec[i]); }
        else if constexpr (std::is_same<T, double>::value) { printf("%lf", vec[i]); }

        if (i + 1 < vec.size()) { printf(", "); }
    }

    printf("\n\n");
}

int main()
{
    const std::vector<int> test_arr = { 1, 5, 4, 9, -3, 21, 13, 2, -3, -7 };

    const std::vector<int> sorted_test_arr = sorted(test_arr);

    const std::vector<int> expected_sorted_test_arr = { -7, -3, -3, 1, 2, 4, 5, 9, 13, 21 };

    puts("Unsorted:");
    print_vector(test_arr);

    puts("Sorted:");
    print_vector(sorted_test_arr);

    puts("Expected:");
    print_vector(expected_sorted_test_arr);
}