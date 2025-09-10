#! /bin/bash

echo "Starting analysis with cppcheck..."
cppcheck --enable=all --suppress=missingInclude --xml --xml-version=2 ../Airline-Reservation-System/src 2> cppcheck_output.xml
echo "Results saved in cppcheck_output.xml file."

cppcheck-htmlreport --file=cppcheck_output.xml --report-dir=html_report --source-dir="../Airline-Reservation-System/src" --title="Airline Reservation System"

echo "Opening report in your browser..."
xdg-open html_report/index.html


echo "Starting analysis with cppcheck with different options..."
cppcheck --enable=all --inconclusive --suppress=missingInclude --xml --xml-version=2 ../Airline-Reservation-System/src 2> cppcheck_output_possible.xml
echo "Results saved in cppcheck_output_possible.xml file."

cppcheck-htmlreport --file=cppcheck_output_possible.xml --report-dir=html_report_possible --source-dir="../Airline-Reservation-System/src" --title="Airline Reservation System"

echo "Opening report in your browser..."
xdg-open html_report_possible/index.html


