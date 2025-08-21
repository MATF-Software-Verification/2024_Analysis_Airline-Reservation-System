# 2024_Analysis_Airline-Reservation-System

# Informacije o projektu: 
Ovaj repozitorijum sadrži rezultate praktičnog seminarskog rada u okviru kursa *Verifikacija softvera*, na master studijama Matematičkog fakulteta u Beogradu. Izrada projekta obuhvata primenu alata za verifikaciju softvera na odabranom projektu i analizu dobijenih rezultata.

**Autor: Natalija Filipović 1013/2024**

# Informacije o projektu koji se analizira:

Projekat koji se analizira predstavlja sistem za pronalaženje letova. Sistem pruža mogućnost osnovne pretrage leta na osnovu datuma i kompanije, ali i naprednu pretragu najjeftinijeg leta, najkraćeg leta, kao i izbor letenja sa ili bez presedanja. 
Projekat je implementiran u programskom jeziku C++ i koristi se putem terminala.

**[Ovde](https://github.com/SameetAsadullah/Airline-Reservation-System)** možete pogledati odabrani projekat.
Analizirana je ```main``` grana i commit hash ```7e41ace```.

# Pokretanje projekta:

1. Pre pokretanja projekta potrebno je izmeniti fajlove:
   * *Airline-Reservation-System/src/List.h:linija 3*:
    <pre> <b>#include"Vector"</b> zameniti sa <b>#include "Vector.h"</b> </pre>
    
 Sledeće fajlove promeniti pre pokretanja jediničnih testova, a nakon pokretanja cppcheck-a:
   * *Airline-Reservation-System/src/Stack.h*:
    <pre> na kraj funkcije <i>pop</i> dodati <b>return T();</b> </pre> 
   * *Airline-Reservation-System/src/Graph.h*:
    <pre> na kraj funkcija <i>getCost</i> i <i>getCostArrayIndex</i> dodati <b>return -1;</b></pre> 
2. Prevodjenje aplikacije:
     ```g++ -o airline_reservation_system Main.cpp```
3. Pokrenuti dobijeni izvršni fajl:
     ```./airline_reservation_system```
     
     

# Primenjeni alati, instalacija i uputstvo za pokretanje:
Alati korišćeni za analizu koda:
* <i><b>QtTest</b></i> - za pisanje i izvršavanje jediničnih testova
* <i><b>Memcheck</b></i> - za pronalaženje grešaka u radu sa memorijom prilikom izvršavanja programa
* <i><b>Cppcheck</b></i> - statički analizator za detektovanje potencijalnih grešaka i rizičnih konstrukcija
* <i><b>Clang-format</b></i> - za formatiranje koda

Rezultati svakog alata mogu se reprodukovati pozicioniranjem u istoimeni direktorijum i pokretanjem skripte. Uputstvo za instalaciju i pokretanje alata na Linux sistemima:
1. <i><b>QtTest</b></i>:
     * instalacija: ```sudo apt-get install qtbase5-dev libqt5test5``` i ```sudo apt-get install lcov```
     * pokretanje iz direktorijuma *2024_Analysis_Airline-Reservation-System/unit_tests*: ```./run_unit_tests_with_coverage```
2. <i><b>Memcheck</b></i>:
     * instalacija: ```sudo apt-get install valgrind```
     * pokretanje iz direktorijuma *2024_Analysis_Airline-Reservation-System/memcheck*: ```./run_memcheck```
3. <i><b>Cppcheck</b></i>:
     * instalacija: ```sudo apt-get install cppcheck```
     * pokretanje iz direktorijuma *2024_Analysis_Airline-Reservation-System/cppcheck*: ```./run_cppcheck```
4. <i><b>Clang-format</b></i>:
     * instalacija: ```sudo apt-get install valgrind```
     * pokretanje iz direktorijuma *2024_Analysis_Airline-Reservation-System/clang*: ```./run_clang_format```

Zaključak
Primenom alata otkrivene su brojne greške i nedopustivi propusti. Nekoliko njih izazvalo je iznenadni prekid izvršavanja, a kod pojedinih alata problem je bio i samo kompajliranje. Stilski projekat ne prati nijedno pravilo. Takodje, sve funkcije deklarisane su u header fajlovima, pa je jedna od preporuka da se izvrši refaktorisanje fajlova.



