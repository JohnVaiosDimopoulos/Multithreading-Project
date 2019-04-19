#!/bin/bash

gcc -o exec Proj.c -pthread
./exec -n 100 -r 1000