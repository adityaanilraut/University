# Sorting Algorithms Performance Comparison

## Project Overview

This project provides a comprehensive analysis of five fundamental sorting algorithms, comparing their performance across different input configurations.

## Algorithms Analyzed

- Bubble Sort
- Insertion Sort
- Selection Sort
- Merge Sort
- Quick Sort

## Performance Metrics

The algorithms were evaluated based on:
- Time Complexity
- Space Complexity
- Performance under different data arrangements

### Detailed Algorithm Analysis

#### 1. Bubble Sort
- **Time Complexity**: 
  - Best Case: O(n)
  - Average Case: O(n²)
  - Worst Case: O(n²)
- **Space Complexity**: O(1)
- **Key Characteristics**:
  - Highest overall execution time
  - Quadratic growth pattern
  - Poor performance with large datasets

#### 2. Insertion Sort
- **Time Complexity**:
  - Best Case: O(n)
  - Average Case: O(n²)
  - Worst Case: O(n²)
- **Space Complexity**: O(1)
- **Key Characteristics**:
  - Better performance than Bubble Sort
  - Efficient with partially sorted sequences
  - Shows stepped pattern in execution time

#### 3. Selection Sort
- **Time Complexity**:
  - Best/Average/Worst Case: O(n²)
- **Space Complexity**: O(1)
- **Key Characteristics**:
  - More consistent performance than Bubble and Insertion Sort
  - Less affected by initial data arrangement
  - Steady increase in time with input size

#### 4. Merge Sort
- **Time Complexity**:
  - Best/Average/Worst Case: O(n log n)
- **Space Complexity**: O(n)
- **Key Characteristics**:
  - Most consistent performance
  - Logarithmic growth pattern
  - Minimal variation in execution time
  - Not significantly affected by input arrangement

#### 5. Quick Sort
- **Time Complexity**:
  - Best/Average Case: O(n log n)
  - Worst Case: O(n²)
- **Space Complexity**: O(log n)
- **Key Characteristics**:
  - Best overall performance
  - Very stable across different input sizes
  - Minimal impact from partial sorting
  - Consistently low execution time

## Performance Ranking (Best to Worst)

1. Quick Sort
2. Merge Sort
3. Insertion Sort
4. Selection Sort
5. Bubble Sort

## Key Insights

- Divide-and-conquer algorithms (Quick Sort, Merge Sort) significantly outperform simple comparison sorts
- Simple algorithms show quadratic growth with input size
- Advanced algorithms maintain logarithmic growth patterns
- Performance varies based on input data arrangement

## Data Arrangement

The test used a specific data configuration:
- First 100 elements: Sorted
- Middle 800 elements: Random
- Last 100 elements: Reverse sorted

## Conclusion

The analysis demonstrates the critical importance of choosing the right sorting algorithm based on:
- Data characteristics
- Dataset size
- Performance requirements

## Source Code

All implementation details and performance tests are available in `project2.cpp`.

## How to Run

```bash
# Compile the C++ file
g++ project2.cpp -o sorting_comparison

# Run the comparison
./sorting_comparison > Data.csv
```



