# Page Replacement Simulator

This project simulates four page-replacement algorithms: **FIFO**, **MIN (Optimal)**, **LRU**, and **Second Chance (Clock)**. It reads a frame count and a reference sequence of page IDs from the command line, runs each algorithm, prints a step-by-step trace, and displays a comparison summary.

## Build Instructions

Requires [CMake](https://cmake.org/) (version 3.10 or higher).

```sh
# From the project root directory
mkdir -p build
cd build
cmake ..
make
```

The executable will be at `build/page_replacement`.

## Usage

```
./page_replacement N "p1 p2 p3 ... pn"
```

- `N` — number of physical frames (≥ 1, max 64).
- The second argument is a space-separated list of page IDs (non-negative integers).

### Example

```sh
./page_replacement 3 "7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1"
```

## Clean Build

```sh
rm -rf build
```

## Algorithms

| Algorithm         | Description                                                             |
| ----------------- | ----------------------------------------------------------------------- |
| **FIFO**          | Evicts the page that has been in memory the longest.                    |
| **MIN**           | Evicts the page whose next use is farthest in the future.               |
| **LRU**           | Evicts the page that was least recently used.                           |
| **Second Chance** | FIFO with a reference bit; pages get a "second chance" before eviction. |

## Project Structure

```
├── CMakeLists.txt           # Build configuration
├── src/
│   ├── main.c               # Entry point
│   ├── input.h              # Shared types & parse_input declaration
│   ├── input.c              # CLI parsing and validation
│   ├── algorithms.h         # Algorithm declarations (FIFO, MIN, LRU, Second Chance)
│   ├── algorithms.c         # Algorithm implementations (FIFO, MIN, LRU, Second Chance)
│   ├── trace.h              # Trace & summary declarations
│   ├── trace.c              # Trace formatting & comparison table
└── docs/
    └── implementation-guide.md
```
