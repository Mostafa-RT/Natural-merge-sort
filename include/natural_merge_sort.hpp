#ifndef NATURAL_MERGE_SORT_HPP
#define NATURAL_MERGE_SORT_HPP

#include <iterator>

class NaturalMergeSort
{
   NaturalMergeSort() = delete;
   ~NaturalMergeSort() = delete;
   NaturalMergeSort(NaturalMergeSort &&) = delete;
   NaturalMergeSort(const NaturalMergeSort &) = delete;
   NaturalMergeSort &operator=(NaturalMergeSort &&) = delete;
   NaturalMergeSort &operator=(const NaturalMergeSort &) = delete;

public:
   template <typename RandomIt>
   inline static void sort(RandomIt first, RandomIt last)
   {
      NaturalMergeSort::naturalMergeSort(first, last, typename std::iterator_traits<RandomIt>::iterator_category());
   }

private:
   template <typename RandomIt>
   static void naturalMergeSort(RandomIt first, RandomIt last, std::random_access_iterator_tag)
   {
      typename std::iterator_traits<RandomIt>::difference_type n = last - first;
      if (n > 1)
      {
         size_t numberOfSlices = {1};
         size_t *slicePositions = nullptr;
         slicePositions = new size_t[n + 1];
         slicePositions[0] = {0};
         for (RandomIt i = first; i < last - 1; i++)
         {
            if (*i > *(i + 1))
            {
               slicePositions[numberOfSlices] = i + 1 - first;
               numberOfSlices++;
            }
         }
         slicePositions[numberOfSlices] = n;

         typename std::iterator_traits<RandomIt>::pointer mirrorArray = nullptr;
         try
         {
            mirrorArray = new typename std::iterator_traits<RandomIt>::value_type[n];
         }
         catch (const std::bad_alloc &e)
         {
            delete[] slicePositions;
            throw;
         }

         bool copyToMirror = {true};

         for (size_t sliceOffset = 1; sliceOffset < numberOfSlices; sliceOffset *= 2)
         {
            for (size_t i = 0; i < numberOfSlices; i += 2 * sliceOffset)
            {
               size_t middle = std::min(i + sliceOffset, numberOfSlices);
               size_t end = std::min(i + (2 * sliceOffset), numberOfSlices);

               if (copyToMirror)
               {
                  NaturalMergeSort::merge(first + slicePositions[i], first + slicePositions[middle], first + slicePositions[end], mirrorArray + slicePositions[i]);
               }
               else
               {
                  NaturalMergeSort::merge(mirrorArray + slicePositions[i], mirrorArray + slicePositions[middle], mirrorArray + slicePositions[end], first + slicePositions[i]);
               }
            }
            copyToMirror = !copyToMirror;
         }

         if (!copyToMirror)
         {
            for (size_t i = 0; i < static_cast<size_t>(n); i++)
            {
               *(first + i) = *(mirrorArray + i);
            }
         }

         delete[] mirrorArray;
         delete[] slicePositions;
      }
   }

   template <typename forwardIt, typename outputIt>
   static void merge(forwardIt first, forwardIt middle, forwardIt last, outputIt resultBeg)
   {
      forwardIt i = {first};
      forwardIt j = {middle};
      while (i != middle && j != last)
      {
         if (*i < *j)
         {
            *resultBeg = *i;
            i++;
         }
         else
         {
            *resultBeg = *j;
            j++;
         }
         resultBeg++;
      }
      while (i != middle)
      {
         *resultBeg = *i;
         i++;
         resultBeg++;
      }
      while (j != last)
      {
         *resultBeg = *j;
         j++;
         resultBeg++;
      }
   }
};

#endif // NATURAL_MERGE_SORT_HPP
