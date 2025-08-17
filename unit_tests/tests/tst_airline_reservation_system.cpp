#include <QtTest>
#include <sstream>

#include "../Airline-Reservation-System/src/Graph.h"
#include "../Airline-Reservation-System/src/UserInterface.h"

class test : public QObject
{
    Q_OBJECT public : test();
    ~test();

private:
    UI ui;
    const std::string flightsFile = "../Airline-Reservation-System/src/Flights.txt";
    const std::string hotelsFile  = "../Airline-Reservation-System/src/HotelCharges_perday.txt";
    Graph *g;


private slots:

    void initTestCase(){
        g = new Graph(flightsFile, hotelsFile);
    }

    void cleanupTestCase() {
            delete g;
    }

    void testBasicDirectFlight_Found() {

            std::istringstream myInput(
                "1\n"           // Basic search
                "1\n"           // Direct flight
                "Tehran\n"      // Origin city
                "Milan\n"       // Destination city
                "0\n"           // Date
                "0\n"           // Airline
                "0\n"           // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains(" Press 1 for Direct Flights with specific date and airline. \n"
                                    " Press 2 for connected Flight with specific transit location on a specific date. "));
            QVERIFY(output.contains("Enter Origin city:"));
            QVERIFY(output.contains("Enter destination city:"));
            QVERIFY(output.contains("Enter travel date, Enter 0 if you dont want to give any specific date: "));
            QVERIFY(output.contains("Enter airline, Enter 0 if you dont want to give any specific airline: "));
            QVERIFY(output.contains("			\t\t\tAirLine:  PIA\n"
                                    "			\t\t\tTicket Price:  2000\n"
                                    "			\t\t\tDate:  1/12/2019\n"
                                    "			\t\t\tFlying Time:  14:00\n"
                                    "			\t\t\tLanding Time:  18:00\n"
                                    "			\t\t\tDuration Time:  4 hour(s) \n"));
            QVERIFY(output.contains("			\t\t\tAirLine:  KLM\n"
                                    "			\t\t\tTicket Price:  2000\n"
                                    "			\t\t\tDate:  3/12/2019\n"
                                    "			\t\t\tFlying Time:  14:00\n"
                                    "			\t\t\tLanding Time:  18:00\n"
                                    "			\t\t\tDuration Time:  4 hour(s) \n"));
    }

    void testBasicDirectFlight_NotFound() {

            std::istringstream myInput(
                "1\n"          // Basic search
                "1\n"          // Direct flight
                "Belgrade\n"   // Origin city
                "Paris\n"      // Destination city
                "1/12/2019\n"  // Date
                "AirSerbia\n"  // Airline
                "0\n"          // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("Origin city not found."));
    }

    void testBasicConnectedFlight_Found() {

            std::istringstream myInput(
                "1\n"          // Basic search
                "2\n"          // Connected flight
                "Paris\n"      // Origin city
                "Berlin\n"     // Transit city
                "Sydney\n"     // Destination city
                "1/12/2019\n"  // Date
                "0\n"          // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("Enter Origin city: "));
            QVERIFY(output.contains("Enter Transit Location: "));
            QVERIFY(output.contains("Enter Destination City: "));
            QVERIFY(output.contains("Enter date of departure: "));
            QVERIFY(output.contains("			\t\t\tAirLine:  Qatar\n"
                                    "			\t\t\tTicket Price:  25000\n"
                                    "			\t\t\tDate:  1/12/2019\n"
                                    "			\t\t\tFlying Time:  00:30\n"
                                    "			\t\t\tLanding Time:  04:00\n"
                                    "			\t\t\tDuration Time:  4 hour(s) \n"));
            QVERIFY(output.contains("			\t\t\tAirLine:  Emirates\n"
                                    "			\t\t\tTicket Price:  35000\n"
                                    "			\t\t\tDate:  1/12/2019\n"
                                    "			\t\t\tFlying Time:  05:00\n"
                                    "			\t\t\tLanding Time:  09:00\n"
                                    "			\t\t\tDuration Time:  4 hour(s) \n"
                                    "\n"
                                    "			\t\t\tTransit stay duration: 1 Hours(s)"));

            QVERIFY(output.contains("			\t\t\tAirLine:  Emirates\n"
                                    "			\t\t\tTicket Price:  35000\n"
                                    "			\t\t\tDate:  2/12/2019\n"
                                    "			\t\t\tFlying Time:  05:00\n"
                                    "			\t\t\tLanding Time:  09:00\n"
                                    "			\t\t\tDuration Time:  4 hour(s) \n"
                                    "\n"
                                    "			\t\t\tTransit Flight will fly after this date"));
            QVERIFY(output.contains("There are no more transit flights with given transit time duration."));
    }

    void testBasicConnectedFlight_NotFound() {

            std::istringstream myInput(
                "1\n"          // Basic search
                "2\n"          // Connected flight
                "Belgrade\n"   // Origin city
                "Berlin\n"     // Transit city
                "Sydney\n"     // Destination city
                "1/12/2019\n"  // Date
                "0\n"          // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("Origin city not found. "));
    }


    void testAdvancedMinimumCostFlight_Found() {

            std::istringstream myInput(
                "2\n"          // Advanced search
                "1\n"          // Minimum travel cost
                "Newyork\n"    // Origin city
                "Seoul\n"      // Destination city
                "1/12/2019\n"  // Date
                "ANA\n"        // Airline
                "0\n"          // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains(" Press 1 for flights with minimum travel cost. \n"
                                    " Press 2 for flights with minimum travel time. \n"
                                    " Press 3 for connected flights with specific location, duration and date. "));
            QVERIFY(output.contains("Enter Origin city: "));
            QVERIFY(output.contains("Enter Destination City: "));
            QVERIFY(output.contains("Enter airline name: "));
            QVERIFY(output.contains("Enter date of departure: "));
            QVERIFY(output.contains("			\t\t\tAirLine:  ANA\n"
                                    "			\t\t\tTicket Price:  36000\n"
                                    "			\t\t\tDate:  1/12/2019\n"
                                    "			\t\t\tFlying Time:  20:00\n"
                                    "			\t\t\tLanding Time:  24:00\n"
                                    "			\t\t\tDuration Time:  4 hour(s) \n"));
    }

    void testAdvancedMinimumCostFlight_NotFound() {

            std::istringstream myInput(
                "2\n"          // Advanced search
                "1\n"          // Minimum travel cost
                "Newyork\n"    // Origin city
                "Sydney\n"     // Destination city
                "3/12/2019\n"  // Date
                "Emirates\n"   // Airline
                "0\n"          // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("No Possible Flight"));
    }

    void testAdvancedMinimumTimeFlight_Found() {

            std::istringstream myInput(
                "2\n"              // Advanced search
                "2\n"              // Minimum travel time
                "Newyork\n"        // Origin city
                "Islamabad\n"      // Destination city
                "2/12/2019\n"      // Date
                "0\n"              // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("Enter Origin city: "));
            QVERIFY(output.contains("Enter Destination City: "));
            QVERIFY(output.contains("Enter date of departure: "));
            QVERIFY(output.contains("			\t\t\tAirLine:  ANA\n"
                                    "			\t\t\tTicket Price:  100000\n"
                                    "			\t\t\tDate:  2/12/2019\n"
                                    "			\t\t\tFlying Time:  11:00\n"
                                    "			\t\t\tLanding Time:  16:00\n"
                                    "			\t\t\tDuration Time:  5 hour(s) \n"));


    }

    void testAdvancedMinimumTimeFlight_FoundLater() {

            std::istringstream myInput(
                "2\n"           // Advanced search
                "2\n"           // Minimum travel time
                "Amsterdam\n"   // Origin city
                "Singapore\n"   // Destination city
                "1/12/2019\n"   // Date
                "0\n"           // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("			\t\t\tAirLine:  ANA\n"
                                    "			\t\t\tTicket Price:  65000\n"
                                    "			\t\t\tDate:  2/12/2019\n"
                                    "			\t\t\tFlying Time:  08:00\n"
                                    "			\t\t\tLanding Time:  01:00\n"
                                    "			\t\t\tDuration Time:  7 hour(s) \n"));

    }

    void testAdvancedConnectedFlight_Found() {

            std::istringstream myInput(
                "2\n"           // Advanced search
                "3\n"           // Connected flight
                "Newyork\n"      // Origin city
                "Amsterdam\n"   // Transit city
                "Singapore\n"    // Destination city
                "3/12/2019\n"   // Date
                "12\n"          // Stay duration hours
                "0\n"           // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("Enter Origin city: "));
            QVERIFY(output.contains("Enter Transit Location: "));
            QVERIFY(output.contains("Enter Destination City: "));
            QVERIFY(output.contains("Enter date of departure: "));
            QVERIFY(output.contains("Enter stay duration hours less than 12, enter 12 if you want to stay for more than 12 hours: "));
            QVERIFY(output.contains("			\t\t\tAirLine:  ANA\n"
                                    "			\t\t\tTicket Price:  75000\n"
                                    "			\t\t\tDate:  3/12/2019\n"
                                    "			\t\t\tFlying Time:  19:00\n"
                                    "			\t\t\tLanding Time:  01:00\n"
                                    "			\t\t\tDuration Time:  6 hour(s) \n"));
            QVERIFY(output.contains("			\t\t\tAirLine:  ANA\n"
                                    "			\t\t\tTicket Price:  65000\n"
                                    "			\t\t\tDate:  4/12/2019\n"
                                    "			\t\t\tFlying Time:  08:00\n"
                                    "			\t\t\tLanding Time:  01:00\n"
                                    "			\t\t\tDuration Time:  17 hour(s) \n"
                                    "\n"
                                    "			\t\t\tTransit Flight will fly on next day"));
            QVERIFY(output.contains("			\t\t\tAirLine:  ANA\n"
                                    "			\t\t\tTicket Price:  65000\n"
                                    "			\t\t\tDate:  5/12/2019\n"
                                    "			\t\t\tFlying Time:  08:00\n"
                                    "			\t\t\tLanding Time:  01:00\n"
                                    "			\t\t\tDuration Time:  17 hour(s) \n"
                                    "\n"
                                    "			\t\t\tTransit Flight will fly on next day"));

    }

    void testAdvancedConnectedFlight_NotFound() {

            std::istringstream myInput(
                "2\n"           // Advanced search
                "3\n"           // Connected flight
                "Hongkong\n"    // Origin cty
                "Berlin\n"      // Transit city
                "Islamabad\n"   // Destination city
                "2/12/2019\n"   // Date
                "5\n"           // Stay duration hours
                "0\n"           // exit
            );

            std::ostringstream programOutput;

            auto oldCin = std::cin.rdbuf(myInput.rdbuf());
            auto oldCout = std::cout.rdbuf(programOutput.rdbuf());

            ui.displayMenu(*g);

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            QString output = QString::fromStdString(programOutput.str());
            QVERIFY(output.contains("Origin city not found."));

    }
};

    test::test() {}
    test::~test() {}

QTEST_APPLESS_MAIN(test)

#include "tst_airline_reservation_system.moc"
