#include <vector>
#include <stdexcept>
#include <iostream>

void pop_min(std::vector<int>& src, std::vector<int>& dst);

std::vector<int> sorted(std::vector<int> arr)
{
    std::vector<int> ret;
    ret.reserve(arr.size());

    while (arr.size() > 0)
    {
        pop_min(arr, ret);
    }

    return ret;
}

void pop_min(std::vector<int>& src, std::vector<int>& dst)
{
    if (src.size() == 0) { throw std::length_error("Expected src to have a size of at least 1!"); }

    int min_value = src[0];

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


void print_int_vector(const std::vector<int>& vec)
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        printf("%d", vec[i]);
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
    print_int_vector(test_arr);

    puts("Sorted:");
    print_int_vector(sorted_test_arr);

    puts("Expected:");
    print_int_vector(expected_sorted_test_arr);
}