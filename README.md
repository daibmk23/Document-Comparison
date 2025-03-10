# Document Storage Optimization

## Problem Overview
This is a document storage optimization problem where the goal is to minimize the number of stored documents by identifying which documents can be converted to common documents through simple transformations. Given N documents (strings), with some similar enough to be converted to common documents with small changes. The goal is to find the minimum number of common documents needed.

## Allowed Transformations
A document can be transformed using one of these operations:
1. Add at most one character
2. Delete at most one character
3. Change at most one character
4. Perform cyclic shifting (rotating the string)

## Input/Output Format
- Input: A list of N documents (strings)
- Output: The minimum number of common documents needed

## Example
### Sample Input
```
5
abc
acc
bca
xyz
xyzt
```

### Sample Output
```
2
```

### Explanation
- "abc", "acc", and "bca" can all be converted to "abc":
  - "acc" → "abc" by changing the second character
  - "bca" → "abc" by cyclic shifting
- "xyz" and "xyzt" can be grouped together:
  - "xyz" → "xyzt" by adding "t" at the end

Therefore, only 2 common documents are needed.

## Implementation Requirements
- The solution must use hashing techniques
- Using data structures other than hash tables will result in zero points

This problem involves grouping strings that can be transformed into each other with at most one operation, and finding the minimum number of common documents needed to represent all original documents.
