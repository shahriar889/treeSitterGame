# Tests

Social-gaming by team Brawndo uses the googletest framework to run tests. Particularly, the latest version (@1.14.0).

## How to run

1. Build the latest changes to the project from the root directory by running
   `cmake -S . -B build`

2. Then, from the root directory, run
   `cd <build-directory>/tests && ctest`
