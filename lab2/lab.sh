#!/bin/bash
g++ -c lab2.c
g++ -o lab2 lab2.o -pthread
g++ -c lab2_timed.c
g++ -o lab2_timed lab2_timed.o -pthread