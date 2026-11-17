# C++ Calculator (v1.0)

A modular, multi-file C++ CLI calculator built from scratch with OOP, raw pointer-based history tracking, chained calculations, and strict edge-case handling. Built in just **364 lines of code** without external libraries.

## Project Structure

```text
Calculator/
├── Calculate.h             # Class declarations, enums, and state definitions (71 LOC)
├── Calculator_Engine.cpp   # Core calculation logic, pointer history & UX flow (261 LOC)
├── main.cpp                # Application entry point (17 LOC)
├── Makefile                # Automated build configuration (15 LOC)
├── .gitignore              # Ignores compiled binaries (*.exe, *.o) and local editor files
└── README.md               # Project documentation

```

## Key Features (v1.0)

- **Chained Calculations:** Automatically carries forward the previous result as the first operand for continuous operations until explicitly reset.
- **Dynamic Pointer-Based History:** Tracks valid calculation steps and operands using raw pointers and custom string casting (`cast_numbers()`).
- **Strict Operation Validation:** Uses `enum class` (`Operations`) to validate `+`, `-`, `*`, `/`, and `%`, blocking multi-character or invalid symbols before prompting for the second operand.
- **Zero-Trap & Edge-Case Protection:** Prevents crashes on division or modulus by zero (`/` and `%`) while keeping the active result and history clean via `should_save_history()`.
- **Full State Reset:** Clears calculation history, resets counters, and restores fresh two-operand input mode on demand.
- **Sassy UX Feedback:** Delivers instant, unapologetic terminal feedback on invalid operations and out-of-bounds menu choices.

## Engineering Challenges & Lessons Learned

- **Single Responsibility Principle (SRP):** Decoupled data conversion (`cast_numbers()`) from storage (`store_history()`), letting `manager()` orchestrate the execution pipeline cleanly.
- **Immediate UX Interception:** Refactored `get_user_expression()` across both fresh-start and chained-mode branches so invalid operators trigger an immediate error without asking for `number_2`.
- **History Filtering Logic:** Isolated invalid operations and zero-division/modulus traps inside `should_save_history()` to prevent corrupted entries from polluting the history array.

## Build & Run

Ensure you have `g++` (MinGW/GCC) and `make` installed:

```bash
# Compile the project
make

# Run the executable
./calculator
```

_(On Windows PowerShell/CMD, run `calculator.exe` or `mingw32-make` depending on your setup.)_

## Roadmap (v2.0+)

- [ ] Replace step-by-step operator prompts with a single-line string expression parser (e.g., `223 + 57 * 2 ^ 3`).
- [ ] Implement operator precedence (BODMAS/Shunting-Yard algorithm).
- [ ] Add scientific functions (`pow`, `sqrt`, etc.) and input-stream type guards.
