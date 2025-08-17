#!/bin/bash

if [ -d "coverage" ]; then
	rm -r coverage_report
fi

if [ ! -d "build" ]; then
	mkdir build
fi

echo "Compiling tests..."
qmake tests/unit_airline_reservation_system.pro
make 

echo "Running tests..."
./unit_airline_reservation_system

mv tst_airline_reservation_system.* Makefile unit_airline_reservation_system target_wrapper.sh moc_predefs.h build/

mkdir coverage_report
echo "Creating coverage..."
lcov --capture --directory build --output-file coverage_report/coverage.info
echo "Removing unnecessary system files..."
lcov --remove coverage_report/coverage.info '/usr/*' '*/QtTest/*' '*/tst_airline_reservation_system.moc' --output-file coverage_report/coverage_filtered.info
echo "Generating HTML coverage report..."
genhtml coverage_report/coverage_filtered.info --output-directory coverage_report/coverage_html
xdg-open coverage_report/coverage_html/index.html
echo "Coverage report saved in 'coverage_report' directory"


