#!/bin/bash

SOURCE_DIR="../Airline-Reservation-System/src"

for file in "$SOURCE_DIR"/*; do
	if [[ -f "$file" && ( "$file" == *.cpp || "$file" == *.h ) ]]; then
		FILE_NAME=$(basename "$file")
		echo "Formatting: $file..."
		clang-format "$file"  > "${FILE_NAME%.*}_clang-format_output.txt"
		diff "$file" "${FILE_NAME%.*}_clang-format_output.txt" > "${FILE_NAME%.*}_diff.txt"
		rm "${FILE_NAME%.*}_clang-format_output.txt"
		echo -e "Clang formatting done for ${file}. Differences between original and suggested formatting saved in ${FILE_NAME%.*}_diff.txt\n"
	fi
done

