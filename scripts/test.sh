#!/bin/bash

# Build our project first
./scripts/build.sh || exit 1

# Now run our tests
./bin/pipeSimTests

