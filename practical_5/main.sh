#!/bin/bash

# This script automates the Knapsack experiment by extracting, compiling,
# and running the necessary code from the markdown generator script.

set -e # Exit immediately if a command exits with a non-zero status.

GENERATOR_SCRIPT="main.sh"

if [ ! -f "$GENERATOR_SCRIPT" ]; then
  echo "Error: The source file '$GENERATOR_SCRIPT' was not found."
  echo "Make sure it's in the current directory."
  exit 1
fi

echo "==> Phase 1: Extracting code payloads from the Canvas..."

# Use awk to find the specific code blocks and extract them to temporary files.
# The c_section and py_section counters ensure we grab the correct blocks.
awk '
  /^## 4\(a\)/ {c_section=1}
  /^## 4\(b\)/ {c_section=2}
  /^## Python Code for Plotting/ {py_section=1}
  /^```c/ && c_section==1 { in_c_block=1; next }
  /^```c/ && c_section==2 { in_c_block=2; next }
  /^```python/ && py_section==1 { in_py_block=1; next }
  /^```$/ { in_c_block=0; in_py_block=0; }
  in_c_block==1 { print > "temp_fractional.c" }
  in_c_block==2 { print > "temp_knapsack01.c" }
  in_py_block==1 { print > "temp_plotter.py" }
' "$GENERATOR_SCRIPT"

echo "==> Validating extracted files..."

# Add checks to ensure awk actually created the files
if [ ! -f "temp_fractional.c" ] || [ ! -f "temp_knapsack01.c" ] || [ ! -f "temp_plotter.py" ]; then
  echo "Error: Failed to extract one or more code files."
  echo "This usually means the awk patterns did not match the structure of '$GENERATOR_SCRIPT'."
  echo "Please check that the markdown headers (e.g., '## 4(a)') and code fences are correct."
  # Clean up any partial files before exiting
  rm -f temp_fractional.c temp_knapsack01.c temp_plotter.py
  exit 1
fi

echo "==> Payloads extracted and validated."

echo "==> Phase 2: Compiling and running C code..."

# Compile and run the first C program
echo "--> Compiling Fractional Knapsack (Greedy)..."
gcc temp_fractional.c -o fractional_runner
echo "--> Running Fractional Knapsack to generate fractional_knapsack.txt..."
./fractional_runner

# Compile and run the second C program
echo "--> Compiling 0/1 Knapsack (DP)..."
gcc temp_knapsack01.c -o knapsack01_runner
echo "--> Running 0/1 Knapsack to generate 01_knapsack.txt..."
./knapsack01_runner

echo "==> Data files generated."

echo "==> Phase 3: Running Python plotter..."
python3 temp_plotter.py
echo "==> Plots generated: knapsack_time_comparison.png, knapsack_space_comparison.png"

echo "==> Phase 4: Cleaning up temporary files..."
rm temp_fractional.c temp_knapsack01.c temp_plotter.py fractional_runner knapsack01_runner
echo "==> Cleanup complete."

echo "==> Experiment finished successfully."
