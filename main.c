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

    char ein[4096];    ///Hilfs-Eingabestring für das Einlesen von bestimmten Werten

    int buchAnzahl = 0; ///Anzahl der eingelesenen Buecher
    int aktFeldSize = 10;  ///Anzahl der aktuellen Buchfelder

    char user;             ///Variable fuer User-Input
    char user2;            ///Variable fuer den User-Input in Unter-Menüs
    char dummy;

    buch_t *buecher;       ///Buchfeld
    buch_t *searchresult=NULL;  ///Pointer fuer die Rueckgabe Adresse von der Funktion sucheBuch()

    int quit = 1;          ///Variable, die auf 0 gesetzt wird, wenn der User aufhoert

    int ok = 0;

    ///Variablen fuer die Return Werte der Funktionen
    ///********************************************************************************
    int retmenu    = 0,      ///Variable fuer Return-Wert der Funktion menue()
        retneu     = 0,      ///Variable fuer den Return-Wert der Funktion erstelleNeuesBuch
        retgueltig = 0,   ///Variable fuer den Return-Wert der Funktion gueltigeBuchNummer
        retzugang  = 0,  ///Variable fuer den Return-Wert der Funktion buchZugang
        retentf    = 0,  ///Variable fuer den Return-Wert der Funktion buchEntfernen
        retsave    = 0,  ///Variable fuer den Return-Wert der Funktion speichereBuecher
        retfilter  = 0, ///Variable fuer den Return-Wert der Funktion filtermenue
        rettitel   = 0; ///Variable fuer den Return-Wert der Funktion aendereTitel
    double lagerwert = 0; ///Variable fuer das Speichern des gesamten Lagerwertes
    ///********************************************************************************

    ///Variablen fuer die Filter Funktionen
    ///********************************************************************************
    int preisAngabe = 0,
        moreOrLess  = 0;




    if(argc != 2) ///Argc muss 2 sein, sonst kann das Programm nicht ausgefuehrt werden
    {
        printf("\n\tFalsche Ausfuehrung. Richtige Ausfuehrung:\n\t<programmname>.exe <dateiname>.csv\n(Ohne <> Klammern!)"); ///Ausgabe der Fehlermeldung
        return (EXIT_FAILURE);
    }

    buecher = (buch_t*) calloc(aktFeldSize, sizeof(buch_t));

    if(!buecher)
    {
        printf("\n\tBeim Anfordern des Initialspeichers hat es einen Fehler gegeben. Programm wird nun beendet.\n");
        return (EXIT_FAILURE);
    }

    buecher = fuegeBuecherFeldHinzu(argv[1], buecher, &buchAnzahl, &aktFeldSize);


    do
    {
        retmenu = menue();

        switch(retmenu)
        {
        case 1:
            // retneu = buchZugang(buecher, buchAnzahl);
            if(retneu)
            {

            }
            break;
        case 2:
            retentf = buchEntfernen(buecher, buchAnzahl, ein);
            if(retentf)
            {

            }
            break;
        case 3:
            //aendereTitel()
            break;
        case 4:
            system("cls");
            printf("\n\n\tNach einem Buch suchen");
            printf("\n\t========================");

            ///Anzeigen der Auswahl
            printf("\n\n\t(1) Nach Titel suchen");
            printf("\n\t(2) Nach Buchnummer suchen");
            printf("\n\n\tIhre Auswahl --> ");
            user = getche(); ///Einlesen der Auswahl mittels getch()

            switch(user)
            {
            case '1':
                system("cls");
                printf("\n\n\tNach Titel suchen");
                printf("\n\t===================");

                printf("\n\n\tBitte geben Sie den Titel ein, nach dem Sie suchen wollen -> "); ///Aufforderung zum Eingeben des Titels
                gets(ein);  ///Einlesen des Titels mittels gets

                searchresult = sucheBuch(buecher, buchAnzahl, ein, 1); ///Mittels Funktion wird mit eingegeben Titel gesucht

                if(searchresult != NULL) ///Ist etwas gefunden worden, wird if Block ausgefuehrt
                {
                    printf("\n\tDas Buch wurde gefunden!"); ///Ausgabe der Erfolgsmeldung
                    printBuchList(searchresult); ///Die Buecherdaten werden mittels Funktion in Listenform ausgegeben
                    dummy = getch();   ///Warten auf den User
                }
                else  ///Falls sucheBuch NULL zurueckgeliefert hat, wird else block ausgefuehrt
                {
                    fprintf(stderr, "\n\tDas Buch wurde nicht gefunden.");  ///Ausgabe der Fehlermeldung
                    dummy = getch();  ///Warten auf den User
                }
                break;

            case '2':

                system("cls");
                printf("\n\n\tNach Buchnummer suchen");
                printf("\n\t========================");

                printf("\n\n\tBitte geben Sie die Buchnummer ein, nach der Sie suchen wollen -> "); ///Aufforderung zum Eingeben der Buchnummer
                gets(ein);  ///Einlesen der Buchnummer mit gets

                retgueltig = gueltigeBuchNummer(ein);   ///Ueberpruefen, ob es sich um eine gueltige Buchnummer handelt
                if(retgueltig == 0) ///Falls Eingabe nicht gueltig, wird eine Fehlermeldung ausgegeben und abgebrochen mittels break
                {
                    fprintf(stderr, "\n\tSie haben eine ungueltige Buchnummer eingegeben."); ///Ausgabe der Fehlermeldung
                    dummy = getch(); ///Warten auf den User
                    break;  ///Abbrechen des case-Zweigs
                }

                searchresult = sucheBuch(buecher, buchAnzahl, ein, 2); ///Aufrufen der Funktion zum Suchen nach BuchNummer

                if(searchresult != NULL)  ///Falls sucheBuch nicht NULL zurueckgeliefert hat, wird if - Block ausgefuehrt
                {
                    printf("\n\tDas Buch wurde gefunden!");  ///Ausgabe der Erfolgsmeldung
                    printBuchList(searchresult);        ///Mittels printBuchList werden die Buchdaten ausgegeben
                    dummy = getch();   ///Warten auf den User
                }
                else
                {
                    fprintf(stderr, "\n\tDas Buch wurde nicht gefunden."); ///Falls Buch nicht gefunden wurde, ausgabe der Fehlermeldung
                    dummy = getch();  ///Warten auf den User
                }
                break;
            }



            break;
        case 5:
            retfilter = filtermenue();

            switch(retfilter)
            {
            case 1:
                system("cls");
                printf("\n\n\tFiltern nach Preis - Mehr als");
                printf("\n\t===============================");
                do{

                }while(ok != 1);
                preisFilter(buecher, buchAnzahl, preisAngabe, 0);
                break;
            case 2:
                system("cls");
                preisFilter(buecher, buchAnzahl, preisAngabe, 1);
                break;

            }
            break;

        case 6:
            system("cls");
            printf("\n\n\tAusgabe der Buchbestaende");
            printf("\n\t===========================");
            printf("\n\n\tWie moechten Sie die Buchbestaende ausgeben?");
            printf("\n\n\t(1)Unsortiert");
            printf("\n\t(2)Sortiert");
            printf("\n\n\tIhre Auswahl --> ");

            user = getch();

            switch(user)
            {
            case '1':
                system("cls");
                listeBuchbestand(buecher, buchAnzahl);
                dummy = getch();
                break;
            case '2':
                system("cls");
                printf("\n\n\tSortiert nach bestimmten Kriterien ausgeben");
                printf("\n\t=============================================");
                printf("\n\n\tNach welchem Kriterium soll das Feld sortiert ausgegeben werden?");
                printf("\n\t(1) Preis");
                printf("\n\t(2) Titel");
                printf("\n\t(3) Buchnummer");
                printf("\n\n\tIhre Auswahl --> ");
                user2 = getch();

                switch(user2)
                {
                case '1':
                    system("cls");
                    printf("\n\n\tNach Preis sortiert");
                    printf("\n\t=====================");
                    listeBuchbestandGeordnet(buecher, buchAnzahl, 1);
                    dummy = getch();
                    break;
                case '2':
                    system("cls");
                    printf("\n\n\tNach Titel sortiert");
                    printf("\n\t=====================");
                    listeBuchbestandGeordnet(buecher, buchAnzahl, 2);
                    dummy = getch();
                    break;

                case '3':
                    system("cls");
                    printf("\n\n\tNach Buchnummer sortiert");
                    printf("\n\t==========================");
                    listeBuchbestandGeordnet(buecher, buchAnzahl, 3);
                    dummy = getch();
                    break;
                }
            }
            break;
        case 7:
            system("cls");
            lagerwert = lagerWert(buecher, buchAnzahl);
            printf("\n\n\tLagerbestand");
            printf("\n\t==============");
            printf("\n\n\tGesamtwert des Lagerbestandes: %.2lf", lagerwert);
            dummy = getch();
            break;
        case 8:
            system("cls");
            printf("\n\n\tBestellliste");
            printf("\n\t==================\n");

            bestellListe(buecher, buchAnzahl);
            dummy = getch();
            break;

        case 11:
            printf("\n\tDanke, dass Sie da waren.\n\tAchtung! Alle nichtgespeicherten Daten gehen verloren!");
            return (EXIT_SUCCESS);
            break;

        }

    }
    while(quit);




    free(buecher);
    return dummy;
}
