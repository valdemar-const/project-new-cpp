#!/usr/bin/env bash

clang-format -i `find projects -type f -name "*.cpp" -o -name "*.hpp"`
