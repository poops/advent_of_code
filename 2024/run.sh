#!/bin/bash
set -euo pipefail

if [ $# -eq 0 ]; then
  echo "usage:"
  echo "$0 01"
elif [[ "$1" == *".."* ]]; then
  echo "invalid directory"
elif [ ! -d "$1" ]; then
  echo "directory not found: $1"
elif [ ! -f "$1/$1.c" ]; then
  echo "file not found: $1/$1.c"
else
  cd $1
  gcc -Wall -Wextra -std=c2x -pedantic -o /tmp/$1 $1.c
  /tmp/$1
fi
