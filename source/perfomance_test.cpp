#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <iostream>
#include "natural_merge_sort.hpp"

// Uncomment to see the generated numbers before and after the sorting

int main()
{
   std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
   std::uniform_int_distribution<uint32_t> distrib(0, 1000000);

   std::vector<uint32_t> numbers;
   // std::cout << "\n# Printing generated random numbers (0-1000000):\n";
   for (size_t i = 1; i < 8388608U; i++)
   {
      numbers.emplace_back(distrib(gen));
      // std::cout << numbers.back() << ' ';
   }
   // std::cout << "\n\n# Performing natural_merge_sort ..." << std::endl;

   auto start = std::chrono::steady_clock::now();
   NaturalMergeSort::sort(numbers.begin(), numbers.end());
   auto end = std::chrono::steady_clock::now();

   std::chrono::duration<double> diff = (end - start);
   // std::cout << "\n# Printing numbers after sort:\n";
   // for (auto &item : numbers)
   // {
   //    std::cout << item << ' ';
   // }
   // std::cout << "\n\n";
   std::cout << "# Sorting time [for n=" << numbers.size() << "]: "
             << std::fixed << std::setprecision(6) << diff.count()
             << "s\nDONE." << std::endl;
}
