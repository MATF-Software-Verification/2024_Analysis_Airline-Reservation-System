QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_airline_reservation_system.cpp

DISTFILES += \
    ../Airline-Reservation-System/src/Flights.txt \
    ../Airline-Reservation-System/src/HotelCharges_perday.txt \

HEADERS += \
    ../Airline-Reservation-System/src/DateAndTime.h \
    ../Airline-Reservation-System/src/Flight.h \
    ../Airline-Reservation-System/src/FlightUI.h \
    ../Airline-Reservation-System/src/Graph.h \
    ../Airline-Reservation-System/src/List.h \
    ../Airline-Reservation-System/src/ListUI.h \
    ../Airline-Reservation-System/src/Stack.h \
    ../Airline-Reservation-System/src/UserInterface.h \
    ../Airline-Reservation-System/src/Vector.h \
    ../Airline-Reservation-System/src/makeGraph.h


QMAKE_CXXFLAGS += -g -Wall -O0 --coverage
LIBS += -lgcov


