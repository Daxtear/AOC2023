// AOC2023.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <vector>

#include "Days.h"
#include "Helpers.h"

using namespace std;

int main()
{
    //vector<string> day1Data;
    //ReadFile("Day1.txt",day1Data);
    //int day1_1 = Day1_1(day1Data);
    //int day1_2 = Day1_2(day1Data);

    //vector<string> day2Data;
    //ReadFile("Day2.txt",day2Data);
    //int day2_1 = Day2_1(day2Data);
    //int day2_2 = Day2_2(day2Data);

    vector<string> day3Data;
    ReadFile("Day3.txt",day3Data);
    //int day3_1 = Day3_1(day3Data);
    int day3_2 = Day3_2(day3Data);

    cout << to_string(day3_2) + "\r\n";
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
