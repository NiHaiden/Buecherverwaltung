#ifndef BOOKFUNC_H_INCLUDED
#define BOOKFUNC_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <strings.h>
#include <unistd.h>


///--------------------------------------
///In dieser Header-Datei befinden sich alle
///Funktionsprototypen sowie Strukturdefinitonen.
///Name: bookfunc.h
///--------------------------------------

///Strukturname: buch_t
///*************************************
///Zweck: enthaelt alle Informationen
///ueber ein Buch
///*************************************

typedef struct{
char buchNummer[11]; // Feld von 10 char und bin�re 0
char *titel; // dynamisches Textfeld geeigneter Gr��e
int bestand; // Lagerbestand - St�ckzahl
double preis; // Preis (in Euro)
} buch_t;


buch_t *fuegeBuecherFeldHinzu(char *dateipfad, buch_t *feld, int *n, int *maximal);
int erstelleNeuesBuch(char *textzeile, buch_t *buecher, int anzahlAkt);
int gueltigeBuchNummer(char *text);  ///Diese Funktion ueberprueft den uebergebenen Text auf eine gueltige Buchnummer
buch_t *sucheBuch(buch_t *buecher, int n, char *suchText,int titelOderNummer);  ///Diese Funktion dient zum Suchen nach einem Buch
int buchZugang(buch_t *buecher, int anzahlAkt);
void buchEntnahme(buch_t *buecher, int anzahl);
int buchEntfernen(buch_t *buecher, int anzahl, char *buchNummer);
void aendereTitel(buch_t *buchAdresse);
void listeBuchbestand(buch_t *buecher, int anzahl);
void listeBuchbestandGeordnet(buch_t *buecher, int anzahl, int ordnungNach);
void bestellListe(buch_t *buecher, int anzahl);
double lagerWert(buch_t *buecher, int anzahl);
void titelFilter(buch_t *buecher, int anzahl, char *suchText);
void nummerFilter(buch_t *buecher, int anzahl, char *suchText);
void preisFilter(buch_t *buecher, int anzahl, double vergleichsPreis,int mehrOderWeniger);
int speichereBuecher (char *dateipfad, buch_t *buecher, int anzahl);
void toCSVText(const buch_t* buch, char *csvText);
int cmpBuchNr(const void *a, const void *b);
int cmpPreis(const void *a, const void *b);
int cmpTitel(const void *a, const void *b);
int menue();   ///Funktion, welche das Menue anzeigt und gewaehlten Menuepunkt zurueckliefert
void freeData(buch_t *buecher, int anzahl); ///Funktion zum Freigeben aller dynamisch angeforderten Daten
void help(); ///Funktion zum Anzeigen der Hilfe
void printBuchData(buch_t *buch); ///Funktion zum Ausgeben der Daten in Tabellenform
void printBuchList(buch_t *buch); ///Funktion zum Ausgeben der Daten in Listenform
#endif // BOOKFUNC_H_INCLUDED
