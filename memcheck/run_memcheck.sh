#!/bin/bash

SOURCE_DIR="../Airline-Reservation-System/src"
OUTPUT_FILE="$(date +%Y-%m-%d_%H:%M:%S).memcheck.out"

cd $SOURCE_DIR
echo "Starting compilation..."
g++ -o airline_reservation_system Main.cpp

cd ../../memcheck

echo "Starting memcheck analysis..."
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file="$OUTPUT_FILE" --track-origins=yes $SOURCE_DIR/airline_reservation_system

echo "Memcheck analysis done. Output saved in $OUTPUT_FILE file."

