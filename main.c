#include "bookfunc.h"

/**
  Name: Niklas Martin Haiden
  Klasse / Katalognr.: 2BHIF / 8
  Aufnahmenummer: 20170023
  Abgabe-Datum: 18.11.2018
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


    char ein[4096];    ///Hilfs-Eingabestring für das Einlesen von Buchnummern,...

    int buchAnzahl = 0; ///Anzahl der eingelesenen Buecher
    int aktFeldSize = 10;  ///Anzahl der aktuellen Buchfelder

    char user;             ///Variable fuer User-Input
    char user2;            ///Variable fuer den User-Input in Unter-Menüs
    char dummy;

    buch_t *buecher;       ///Buchfeld
    buch_t *searchresult=NULL;  ///Pointer fuer die Rueckgabe Adresse von der Funktion sucheBuch()

    int quit = 1;          ///Variable, die auf 0 gesetzt wird, wenn der User aufhoert

    int ok = 0;     ///Variable die speichert, ob alles ok ist oder nicht



    int buchpos;    ///Variable um die Buecherposition speichern zu koennen

    ///Variablen fuer die Return Werte der Funktionen
    ///********************************************************************************
    int retmenu    = 0,      ///Variable fuer Return-Wert der Funktion menue()

        retgueltig = 0,   ///Variable fuer den Return-Wert der Funktion gueltigeBuchNummer

        retentf    = 0,  ///Variable fuer den Return-Wert der Funktion buchEntfernen

        retfilter  = 0; ///Variable fuer den Return-Wert der Funktion filtermenue

    double lagerwert = 0; ///Variable fuer das Speichern des gesamten Lagerwertes
    ///********************************************************************************

    ///Variablen fuer die Filter Funktionen
    ///********************************************************************************
    double preisAngabe = 0;




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
            system("cls");
            printf("\n\n\tNeues Buch / Buecher hinzufuegen");
            printf("\n\t==================================");
            printf("\n\n\t(1)Ein neues Buch hinzufuegen");
            printf("\n\t(2)Buecher aus csv Datei lesen");
            printf("\n\n\tIhre Auswahl --> ");
            user = getch();
            switch(user)
            {
            case '1':
                buchAnzahl+=buchZugang(buecher, buchAnzahl, &aktFeldSize); ///Aufrufen der Funktion und addieren zu buchAnzahl bei Erfolg
                break;
            case '2':
                system("cls");
                printf("\n\n\tNeue Buecher aus CSV Datei lesen");
                printf("\n\t==================================");

                printf("\n\n\tBitte geben Sie den Dateinamen ein --> ");
                gets(ein);
                buecher = fuegeBuecherFeldHinzu(ein, buecher, &buchAnzahl, &aktFeldSize); ///Aufrufen der Funktion um Feld hinzuzufuegen
                if(!buecher)
                {
                    printf("\n\n\tBeim Anfuegen der Werte ist ein Fehler aufgetreten!");
                    break;
                }
            }

            break;
        case 2:
            system("cls");
            printf("\n\n\tBuch loeschen");
            printf("\n\t===============");
            listeBuchbestand(buecher, buchAnzahl);

            printf("\n\n\tBitte geben Sie die Buchnummer des zu loeschenden Buches ein --> ");
            gets(ein);
            ok = gueltigeBuchNummer(ein);
            if(ok != 1)
            {
                fprintf(stderr, "\n\tSie haben keine gueltige Buchnummer eingegeben!\n");
                break;
            }
            retentf = buchEntfernen(buecher, buchAnzahl, ein);
            switch(retentf)
            {
            case 1:
                printf("\n\n\tDas Buch wurde erfolgreich geloescht!");
                buchAnzahl--;
                break;
            case 0:
                printf("\n\n\tBuch konnte nicht geloescht werden!");
                break;
            }
            break;
        case 3:
            system("cls");
            printf("\n\n\tTitel aendern");
            printf("\n\t===============");

            printf("\n\n\tVon welchem Buch moechten Sie den Titel aendern? \n\tGeben Sie bitte die Buchnummer ein --> ");
            gets(ein);
            ok = 0;
            if(gueltigeBuchNummer(ein))
            {
                buchpos = calcbookPos(buecher, buchAnzahl, ein);
                ok=1;
                aendereTitel(buecher+buchpos);
            }
            else
                fprintf(stderr, "\n\tDie Buchnummer ist ungueltig!");

            if(ok == 1)
            {
                printf("\n\tDer Titel dieses Buches wurde veraendert!");
                printf("\n\tNeue Daten:");
                printBuchList(buecher+buchpos);
                dummy = getch();
            }
            else
            {
                fprintf(stderr, "\n\tDas Buch wurde nicht gefunden!");
                dummy = getch();
                ok = 0;
            }
            break;
        case 4:
            system("cls"); ///Leeren des Konsolenfensters fuer bessere Lesbarkeit
            printf("\n\n\tNach einem Buch suchen / filtern");
            printf("\n\t==================================");

            ///Anzeigen der Auswahl
            printf("\n\n\t(1) Nach Titel suchen");
            printf("\n\t(2) Nach Buchnummer suchen");
            printf("\n\t(3) Filtern");
            printf("\n\t(4) Zurueck");
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
                    printf("\n\tDas Buch wurde gefunden!\n\tHier die Daten:\n"); ///Ausgabe der Erfolgsmeldung
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
            case '3':
                retfilter = filtermenue();

                switch(retfilter)
                {
                ///*********************************************************************************
                ///Nach Preis filtern
                ///*********************************************************************************
                case 1:
                    system("cls");
                    printf("\n\n\tFiltern nach Preis - Mehr als");
                    printf("\n\t===============================");
                    do
                    {
                        printf("\n\n\tBitte geben Sie den gewuenschten Preis ein --> "); ///Aufforderung zum Eingeben des Preises
                        ok = sscanf(gets(ein), "%lf%c", &preisAngabe, &dummy); ///Einlesen des Preises mittels sscanf und gets
                        if(ok != 1) ///Falls ein Eingabefehler aufgetreten ist, wird Meldung ausgegeben
                            fprintf(stderr, "\n\tEingabefehler. Bitte versuchen Sie es noch einmal.");
                    }
                    while(ok != 1);
                    printf("\n\n\tDiese Buecher haben einen Preis groesser als %.2lf Euro:\n", preisAngabe);
                    printTableHeader(); ///Ausgeben des Tabellen Headers
                    preisFilter(buecher, buchAnzahl, preisAngabe, 0); ///Aufrufen der Funktion preisFilter um nach gewuenschten Preis zu suchen
                    dummy = getch();
                    break;
                case 2:
                    system("cls");
                    do
                    {
                        printf("\n\n\tBitte geben Sie den gewuenschten Preis ein --> "); ///Aufforderung zum Eingeben des Preises
                        ok = sscanf(gets(ein), "%lf%c", &preisAngabe, &dummy); ///Einlesen des Preises mittels sscanf und gets
                        if(ok != 1) ///Falls ein Eingabefehler aufgetreten ist, wird Meldung ausgegeben
                            fprintf(stderr, "\n\tEingabefehler. Bitte versuchen Sie es noch einmal!");
                    }
                    while(ok != 1);
                    printf("\n\n\tDiese Buecher haben einen Preis kleiner als %.2lf Euro\n", preisAngabe);
                    printTableHeader();
                    preisFilter(buecher, buchAnzahl, preisAngabe, 1);
                    dummy = getch();
                    break;
                ///*********************************************************************************
                ///Nach Titel filtern
                ///*********************************************************************************
                case 3:
                    system("cls");

                    printf("\n\n\tFiltern nach Titel");
                    printf("\n\t====================");

                    printf("\n\n\tBitte geben Sie einen Text ein, nach dem Sie filtern wollen --> ");
                    gets(ein);

                    printf("\n\n\tDiese Buecher wurden gefunden:\n");
                    titelFilter(buecher, buchAnzahl, ein);
                    dummy = getch();
                    break;
                ///********************************************************************************
                ///Nach Buchnummer filtern
                ///********************************************************************************
                case 4:
                    system("cls");
                    printf("\n\n\tFiltern nach Buchnummer");
                    printf("\n\t=========================");
                    printf("\n\n\tBitte geben Sie einen Text ein, nach dem Sie filtern wollen --> ");
                    gets(ein);

                    system("cls");
                    nummerFilter(buecher, buchAnzahl, ein);
                    dummy = getch();
                    break;

                }
                break;
            }
            break;

        case 5:
            system("cls");
            buchEntnahme(buecher, buchAnzahl);
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
                    printf("\n\t=====================\n");
                    listeBuchbestandGeordnet(buecher, buchAnzahl, 1);
                    dummy = getch();
                    break;
                case '2':
                    system("cls");
                    printf("\n\n\tNach Titel sortiert");
                    printf("\n\t=====================\n");
                    listeBuchbestandGeordnet(buecher, buchAnzahl, 2);
                    dummy = getch();
                    break;

                case '3':
                    system("cls");
                    printf("\n\n\tNach Buchnummer sortiert");
                    printf("\n\t==========================\n");
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

        case 9:
            system("cls");
            printf("\n\n\tSpeichern von Buecherdaten in Datei");
            printf("\n\t=====================================");

            printf("\n\n\tBitte geben Sie den Namen der Datei ein (Ohne .csv!) --> "); //
            gets(ein); ///Einlesen des Dateinamens
            ok = speichereBuecher(ein, buecher, buchAnzahl); ///Aufrufen der Funktion
            switch(ok)
            {
            case 0:
                fprintf(stderr, "\n\tDie Datei konnte nicht erstellt werden!");
                break;
            case 1:
                printf("\n\tDatei wurde erfolgreich erstellt und gespeichert.");
                break;
            case 2:
                fprintf(stderr, "\n\tDie Datei konnte nicht geoeffnet werden!");
                break;
            case 3:
                printf("\n\tDatei wurde erfolgreich ueberschrieben.");
                break;
            }
            dummy = getch();
            break;

        case 10:
            printf("\n\tDanke, dass Sie da waren.\n\tAchtung! Alle nichtgespeicherten Daten gehen verloren!");
            freeData(buecher, buchAnzahl); ///Freigeben aller angeforderten Daten
            return (EXIT_SUCCESS);
            break;

        }

    }
    while(quit);
    return dummy;
}
