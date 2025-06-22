# C++ Coding Exercise Solution

This repository contains the solution to a C++ coding exercise that processes a stream of trade records from `input.csv` and outputs per-symbol statistics to `output.csv`.

## Build

```bash
g++ -std=c++17 -O2 -Wall solution.cpp -o Exercise
```

## Run

```bash
./Exercise input.csv output.csv
```

## Output Format

```
<symbol>,<MaxTimeGap>,<Volume>,<WeightedAveragePrice>,<MaxPrice>
```

The output is sorted in ascending order by symbol.

## Time Spent

Coding: 15:00 to 15:56 CST  
Testing and cleanup: ~5 minutes
```
