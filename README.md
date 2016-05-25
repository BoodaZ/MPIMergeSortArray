# MPIMergeSortArray
Sorting algorithm.
1. Process (0) will initialize an array of 1000 integers with any numbers. 
2.Process (0) will send N partitions of the array to N processes, each partition of size = (N\ Process count).
3.Each Other Process will receive the array part.
4.Each Other Process will sort the received array part. 
5.Each Other Process will send the sorted array back to process (0). 
6.Process (0) will receive the sorted array parts. 
7.Process (0) will merge each received part to the final sorted array. 
8. Merging array parts can be used using a merge function that merges two sorted arrays, the merge function is in the same folder with this document “MergeSortedArrays” and how to be used.
