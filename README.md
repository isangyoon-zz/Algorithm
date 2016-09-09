# Algorithms for PS
This is a C++ codes for Problem Solving(PS). It includes some algorithms such as arithmetic, helper function, data structures and etc.

## Data Structures
### 1. Fenwick Tree (Binary Indexed Tree; BIT)
A Fenwick tree (binary indexed tree; BIT) is a data structure that can efficiently update elements and calculate prefix sums in a table of numbers.

#### Usages
```c++
fenwick_tree<int> tree(std::size_t size);

/* Modifiers */
tree.assign(size, default_value); // assign new contents to the BIT, replacing its current contents, and modifying its size accordingly.
tree.resize(size, default_value); // resizes the container so that it contains n elements.

/* Capacity */
std::size_t size = tree.size(); // returns the number of elements in the BIT.

/* Operatation */
tree.query(int p); // returns the value of the element at index p.
tree.update(int p, int value); // add some value to element at index p.
```
### 2. Union Find (Disjoint Set)
Union-find (disjoint-set or merge-find set) is a data structure that keeps track of a set of elements partitioned into a number of disjoint subsets.

#### Usages
```c++
unionfind disjoint_set(std::size_t n);

/* Operations */
disjoint_set.find(x); // determine which subset a particular element is in. 
disjoint_Set.unite(x, y); // join two subsets into a single subset.
```

## Graph
### Flow Networks
A flow network is a directed graph where each edge has a capacity and each edge receives a flow.

#### 1. Ford Fulkerson
The Ford–Fulkerson algorithm (FFA) is a greedy algorithm that computes the maximum flow in a flow network.

##### Usages
```c++
ford_fulkerson maximum_flow(std::size_t size, int source, int sink);

/* Operations */
maximum_flow.add_edge(u, v, capacity); // adds edge from u to v
maximum_flow.add_edge_from_source(v, capacity); // adds edge from source to v
maximum_flow.add_edge_to_sink(u, capacity); // adds edge u to sink

maximum_flow.flow(); // returns the maximum flow in graph
```

#### 2. Edmonds Karp
The Edmonds Karp algorithm is an implementation of the Ford Fulkerson algorithm for computing the maximum flow in a flow network in O(V^2 E) time.

##### Usages
```c++
edmonds_karp maximum_flow(std::size_t size, int source, int sink);

/* Operations */
maximum_flow.add_edge(u, v, capacity); // adds edge from u to v
maximum_flow.add_edge_from_source(v, capacity); // adds edge from source to v
maximum_flow.add_edge_to_sink(u, capacity); // adds edge u to sink

maximum_flow.flow(); // returns the maximum flow in graph
```

#### 3. Dinic


## Mathematics
* greatest common divisors (GCD)
* extended greatest common divisors (extended GCD)
* calculate sum of(number of) divisors 
* calcuate euler's phi function
* chinese remainder thoerem
* combination, permutation
* powerset (the set of all subsets of set)
* find prime number (sieve of eratosthenes, sieve of atkin)

## Miscellaneous
### Fast I/O
Lets say you have take an input of largest numbers, there are many methods.

```c++
#include <iostream>

int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int x;
  std::cin >> x;
  
  return 0;
}
```
you can use std::cin which is a standard method to obtain input from STDIN.
However, there are better methods.

```c++
#include <cstdio> // stdio.h

int main(int const argc, char const** argv)
{
  int x;
  scanf("%d", &x);
  
  return 0;
}
```
printf, scanf are roughly thrice as fast as the std::cin, std::cout.

```c++
#include <cstdio>

// using io::read_int();

int main(int const argc, char const** argv)
{
  /* emit */
  
  return 0;
}
```
this is one of the fastest way to take an integer input from STDIN this is around 10 times faster than sacnf.
This is very useful in competetive programming!
