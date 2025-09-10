#!/bin/bash

SOURCE_DIR="../Airline-Reservation-System/src"

for file in "$SOURCE_DIR"/*; do
	if [[ -f "$file" && ( "$file" == *.cpp || "$file" == *.h ) ]]; then
		FILE_NAME=$(basename "$file")
		echo "Formatting: $file..."
		clang-format "$file"  > "${FILE_NAME%.*}_clang-format_output.txt"
		echo -e "Clang formatting done for ${file}."
	fi
done

