*This project has been created as part of the 42 curriculum by amazloum, elifbece.*
 
# push_swap
 
## Description
 
push_swap sorts a list of integers using two stacks, `a` and `b`, and a fixed set of 11 operations:
 
| Operation | Effect |
|---|---|
| `sa` / `sb` / `ss` | swap the top two elements of a / b / both |
| `pa` / `pb` | move the top of b to a / the top of a to b |
| `ra` / `rb` / `rr` | rotate up (top goes to the bottom) on a / b / both |
| `rra` / `rrb` / `rrr` | rotate down (bottom goes to the top) on a / b / both |
 
The program does not print the sorted numbers. It prints the list of operations that sorts stack `a` in ascending order (smallest on top), one per line. The goal is to use as few operations as possible.
 
Before any move, the program measures the **disorder** of the input: the number of pairs `(i, j)` with `i` above `j` and `a[i] > a[j]`, divided by the total number of pairs. 0 means sorted, 1 means fully reversed, a random list is close to 0.5.
 
The program contains four strategies:
 
| Flag | Strategy | Class (in operations) |
|---|---|---|
| `--simple` | Min extraction (selection sort with two stacks) | O(n²) |
| `--medium` | Chunk sort with windows of about √n values | O(n√n) |
| `--complex` | 3-way quicksort over both stacks | O(n log n) |
| `--adaptive` (default) | Picks a method from the measured disorder | O(n) / O(n√n) / O(n log n) |
 
## Instructions
 
### Build
 
```sh
make            # builds ./push_swap
make clean      # removes the object files (obj/)
make fclean     # removes the object files and the binary
make re         # rebuilds from scratch
```
 
### Usage
 
```sh
./push_swap 2 1 3 6 5 8
./push_swap --simple 5 4 3 2 1
./push_swap --complex "4 67 3 87 23"           # numbers can also be in one string
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
./push_swap --bench $ARG 2> bench.txt           # stats go to stderr
```
 
### Behaviour
 
- No numbers (no arguments, or only flags): prints nothing.
- Already sorted input: prints nothing.
- On error, prints `Error` followed by a newline on stderr and exits with code 1. Errors are: an argument that is not an integer (`12a`, `-`, `""`), a number outside the `int` range, a duplicate (including `0` and `-0`), an unknown flag, or two different strategy flags.
- `--bench` prints, on stderr after the operations: the disorder as a percentage, the strategy and its complexity class, the total number of operations, and the count of each operation. Because it uses stderr, `./push_swap --bench $ARG | ./checker_linux $ARG` still works.
## How it works
 
### Data structures
 
Each stack is a doubly linked list (`t_node` with `prev` and `next`, `t_stack` with `top`, `bot` and `size`). Every operation is built from four list functions (push or pop at the top or the bottom), so a move only changes a few pointers: no number is copied and nothing is allocated while sorting. All program state lives in one `t_ps` structure passed to every function (no globals).
 
### Shared building blocks
 
**Rank compression.** After parsing, every value is replaced by its rank (0 to n-1). The order is unchanged, so the disorder and the result are the same, but "the largest value in b" becomes `b.size - 1`, values can be used as array indexes, and pivots are simple arithmetic.
 
**Recording and cleanup.** Sorting functions never print. Every operation goes through `op()`, which stores its code in a growing array and applies it to the stacks. Before printing, one pass removes pairs that cancel out (`pa`+`pb`, `ra`+`rra`, `sa`+`sa`, ...) and merges pairs into one combined move (`ra`+`rb` into `rr`, `rra`+`rrb` into `rrr`, `sa`+`sb` into `ss`). This can only lower the count, so it never breaks a result or a complexity class.
 
**Small inputs (n ≤ 6).** Every strategy uses the simple sort, which sorts the last three values in at most 2 operations. Measured over every permutation: 3 values in at most 2 operations, 5 values in at most 10.
 
### Simple: min extraction, O(n²)
 
Two values are fixed with at most one `sa`. Otherwise, repeat: find the smallest value in `a`, rotate it to the top the shorter way, `pb`. When 3 values are left, sort them with at most 2 operations, then `pa` everything back. If `a` becomes sorted before that, the extra `pb`/`pa` pairs are removed by the cleanup pass. Each extraction costs at most n/2 rotations plus one push, and there are n extractions: about n²/2 operations. Space: O(n).
 
### Medium: chunk sort, O(n√n)
 
Phase 1 (a to b). Keep a counter `i` (how many values are already in `b`) and a window size `r ≈ 1.3√n` (13 for 100 values, 29 for 500):
- top of `a` ≤ `i`: `pb` then `rb` (small values go to the bottom of `b`)
- top of `a` ≤ `i + r`: `pb`
- otherwise: `ra`
Phase 2 (b to a). The largest value left in `b` is brought to the top the shorter way and pushed with `pa`. If the second largest is cheaper to reach, it is pushed first, then the largest, then `sa`.
 
Complexity: in phase 1, one full turn of `a` pushes every value in the window, so the window moves by at least `r` per turn: at most n/r turns of at most n rotations, n²/r = O(n√n) with r ~ √n. In phase 2, `b` is ordered by window, so the largest value is always within about r positions of the top or bottom: n × O(r) = O(n√n). Space: O(n).
 
### Complex: 3-way quicksort over both stacks, O(n log n)
 
The stacks are seen as four places: top of a, bottom of a, top of b, bottom of b. A chunk is a group of values in one place, described by its place and size; thanks to ranks, a chunk always holds a continuous range of ranks.
 
To sort a chunk, two pivots (at 1/3 and 2/3 of its range) split it into a max, a mid and a min part. Each value is moved with 1 to 3 operations to the place that is cheapest from its current place (for example, from the top of `a`: max to the bottom of `a` with `ra`, mid to the top of `b` with `pb`, min to the bottom of `b` with `pb rb`). The max part always goes to `a`. Then the max part is sorted, then mid, then min, recursively. Every sorted part ends on top of `a`, so building from the largest part down leaves `a` sorted. Chunks of 3 values or fewer are brought to the top of `a` and sorted with `sa`, `pb` and `pa` only, so the sorted values below are never disturbed.
 
Complexity: each level of recursion moves every value at most once with at most 3 operations, so a level costs at most 3n. Each split leaves parts of about a third of the size, so there are about log₃ n levels: O(n log n) operations. Space: O(n) for the stacks plus O(log n) recursion depth.
 
### Adaptive
 
| Disorder | Method | Class |
|---|---|---|
| < 0.2 | LIS keep + cheapest insertion | O(n) for nearly sorted input (see note) |
| 0.2 to < 0.5 | Chunk sort (medium) | O(n√n) |
| ≥ 0.5 | 3-way quicksort (complex) | O(n log n) |
 
The thresholds are compared with integers (`mistakes * 5 < pairs`, `mistakes * 2 < pairs`), so no floating point rounding is involved.
 
**Low disorder method.** Stack `a` is read as a ring, starting from its smallest value, and its longest increasing subsequence is found (patience sorting with binary search, O(n log n) CPU, zero operations). Those values are already in the right relative order, so they stay in `a`. Every other value is pushed to `b`, each time going to the nearest one from the top or the bottom. Then values come back one by one: for each value in `b`, the cost of bringing it to the top of `b` and its insertion spot to the top of `a` is computed for 4 plans (both up with `rr`, both down with `rrr`, or mixed), and the cheapest value is inserted first. Finally `a` is rotated so its minimum is on top.
 
**Note on the O(n) bound.** If m values are outside the kept subsequence, the cost is at most about n + m·n operations. When the input is nearly sorted (m is a small constant: a few swaps, a rotated sorted list), that is O(n). A disorder below 0.2 does not by itself force m to be small, and no method can sort every input with disorder below 0.2 in O(n) operations (there are too many such permutations for a linear number of moves to tell them apart). So the O(n) claim holds for the nearly sorted inputs this regime is designed for, and the worst case of this method is O(n·m).
 
**Why these thresholds.**
- Below 0.2, most values are already in order, so keeping them and moving only the rest beats any method that moves all n values.
- Between 0.2 and 0.5, the input still has long ordered runs, which the chunk sort's window pass benefits from.
- At 0.5 and above (a random list is around 0.5), the input has no useful structure, so we use the method with the best bound.
## Benchmarks
 
Measured on random inputs, 30 runs each, every output verified to sort correctly:
 
| Input | Strategy | Average | Worst |
|---|---|---|---|
| 100 random | adaptive (default) | 578 | 640 |
| 100 random | `--medium` | 538 | 578 |
| 100 random | `--complex` | 616 | 628 |
| 100 random | `--simple` | 1448 | 1654 |
| 500 random | adaptive (default) | 4339 | 4691 |
| 500 random | `--medium` | 4646 | 4853 |
| 500 random | `--complex` | 4149 | 4173 |
| 500 random | `--simple` | 32088 | 34715 |
| 500 sorted, 2 pairs swapped | adaptive (low) | 484 | |
| 500 sorted, rotated by 50 | adaptive (low) | 50 | |
 
Targets for the best grade: under 700 operations for 100 values and under 5500 for 500 values.
 
## Project structure
 
```
includes/push_swap.h                  op codes, structures, prototypes
srcs/main.c                           main, ps_exit (the only exit point)
srcs/utils/ft_utils.c                 string and output helpers (write only)
srcs/stack/stack_list.c               node creation, push/pop at top and bottom
srcs/stack/stack_list_utils.c         clear a stack, read a position
srcs/stack/stack_find.c               min/max/value positions, rotation helpers
srcs/parsing/parse_args.c             flags, blank arguments, strategy conflicts
srcs/parsing/parse_numbers.c          number reading, overflow and format checks
srcs/parsing/index_ranks.c            duplicates, rank compression
srcs/operations/operations.c          the 11 operations
srcs/operations/op_record.c           recording operations, cancel/merge pass
srcs/output/print_ops.c               printing the operations
srcs/output/print_bench.c             --bench output
srcs/strategy/strategy.c              disorder, regime choice, dispatch
srcs/sorting/simple/simple_sort.c     --simple and sort of 3
srcs/sorting/medium/chunk_sort.c      --medium
srcs/sorting/complex/quick_*.c        --complex
srcs/sorting/adaptive/adaptive_*.c    adaptive low disorder method
```
 
## Contributions
 
- **amazloum:** project base (Makefile, header, `main` and `ps_exit`, utils, linked list functions), operation recording and cleanup (`op_record.c`), disorder and strategy selection (`strategy.c`), the medium strategy (chunk sort), the complex strategy (3-way quicksort) and the adaptive low disorder method.
- **elifbece:** argument and number parsing with all error cases (`parse_args.c`, `parse_numbers.c`), rank compression and duplicate check (`index_ranks.c`), the 11 operations (`operations.c`), position and rotation helpers (`stack_find.c`), the simple strategy and sort of 3 (`simple_sort.c`), and the output (`print_ops.c`, `print_bench.c`).
- **Together:** the design of the program flow, testing (checker runs, benchmarks, leak checks, Norm), and this README.
## Resources
 
- [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)), which is what the disorder metric counts
- [Doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list)
- [Selection sort](https://en.wikipedia.org/wiki/Selection_sort)
- [Quicksort](https://en.wikipedia.org/wiki/Quicksort), including multi-pivot partitioning
- [Longest increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence), patience sorting version
- [Binary search](https://en.wikipedia.org/wiki/Binary_search_algorithm)
- [Comparison sort lower bound](https://en.wikipedia.org/wiki/Comparison_sort#Lower_bound_for_the_average_number_of_comparisons)
### AI usage
 
We used AI as a learning aid: to get explanations of concepts and algorithms, to compare approaches, and to help debug. We wrote every file ourselves, traced each function by hand on small examples, tested each file with our own test programs, and verified the final program with the checker, benchmarks, valgrind and norminette.
 
- **amazloum:** asked for explanations of algorithms and functions before writing them, and help reading compile errors.
- **elifbece:** used AI as a learning tool to better understand C concepts, data structures, and algorithms, discuss implementation approaches and edge cases, and troubleshoot issues during development. I also used it to understand testing methods and Git commands, review my reasoning, and improve project documentation.