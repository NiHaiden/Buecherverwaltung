#include "bookfunc.h"

/*
  Name: Niklas Martin Haiden
  Klasse / Katalognr.: 2BHIF / 8
  Aufnahmenummer: 20170023
  Abgabe-Datum: 5.11.2018
  Programmname: POSHUE1_HAIDEN.c
  --------------------------------------------------------
  Beschreibung:
  Es ist ein Programm zu schreiben, welches Buecher aus einer CSV("comma seperated values")
  Datei ausliest und durch den Benutzer durch verschiedene Befehle und Kommandos verwaltet und bearbeitet
  werden kann.
*/

///*********************************
///Funkt.-Name: main
///Zweck: Ausfuehren der Funktionen
///zur Buchverwaltung und Verwaltung aller Buecher durch Usereingaben
///*********************************
///Return-Wert: EXIT_FAILURE(1): Das Programm wurde durch einen Fehler beendet
///             EXIT_SUCCESS(0): Das Programm wurde mit Erfolg beendet
///*********************************



int main(int argc, char *argv[])
{
    FILE *fp;           ///File-Pointer, für das Einlesen der Datei

    char ein[4096];    ///Hilfs-Eingabestring für das Einlesen der Buecher

    int buchAnzahl = 0; ///Anzahl der eingelesenen Buecher
    int aktFeldSize = 10;  ///Anzahl der aktuellen Buchfelder

    buch_t *buecher;       ///Buchfeld

    int quit = 1;          ///Variable, die auf 0 gesetzt wird, wenn der User aufhoert

    ///Variablen fuer die Return Werte der Funktionen
    ///********************************************************************************
    int retmenu = 0,      ///Variable fuer Return-Wert der Funktion menue()
        retneu  = 0,      ///Variable fuer den Return-Wert der Funktion erstelleNeuesBuch
        retgueltig = 0,   ///Variable fuer den Return-Wert der Funktion gueltigeBuchNummer
        retzugang  = 0,  ///Variable fuer den Return-Wert der Funktion buchZugang
        retentf    = 0,  ///Variable fuer den Return-Wert der Funktion buchEntfernen
        retsave    = 0;  ///Variable fuer den Return-Wert der Funktion speichereBuecher
    double lagerwert = 0; ///Variable fuer das Speichern des gesamten Lagerwertes
    ///********************************************************************************

    if(argc != 2) ///Argc muss 2 sein, sonst kann das Programm nicht ausgefuehrt werden
    {
        printf("\n\tFalsche Ausfuehrung. Richtige Ausfuehrung:\n\t<programmname>.exe <dateiname>.csv\n(Ohne <> Klammern!)"); ///Ausgabe der Fehlermeldung
        return (EXIT_FAILURE);
    }

    buecher = (buch_t*) calloc(aktFeldSize, sizeof(buch_t));

    if(!buecher){
        printf("\n\tBeim Anfordern des Initialspeichers hat es einen Fehler gegeben. Programm wird nun beendet.\n");
        return (EXIT_FAILURE);
    }

    buecher = fuegeBuecherFeldHinzu(argv[1], buecher, &buchAnzahl, &aktFeldSize);
    listeBuchbestand(buecher, buchAnzahl);
/*
    do
    {
        retmenu = menue();

        switch(retmenu)
        {
        case 9:
            break;

        }

    }while(quit);

*/

free(buecher);
return 0;
}
