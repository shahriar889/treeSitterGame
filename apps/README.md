# apps

This directory contains the following components:

- `client-ncurses-prof`: This is the original implementation of the client, created by the professor.
- `(san|jar)server-prototype's`: These are two server protoype implmenation 

# dependencies

- `sudo apt install libboost-all-dev`: boost for linux
-  `brew install boost`: boost for macOS via homebrew

cmake will automatically find these and build the apps

# Moving forward the main executabale will be the server-v1, it will depend on the following components 

- `root/lib`: This directory contains libraries that will be used in the more organized server implementation. 

- `root/tests/server-v1`: This directory contains basic tests that have been linked to the testing framework.

