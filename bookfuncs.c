#include "bookfunc.h"
///********************************************
///Funk.-Name: filtermenue
///Zweck:      Anzeigen des Auswahlmenues, wo der User auswählen kann, nach was er filtern will
///********************************************
///Variablen: eingabe....Hilfsstring fuer die Eingabe
///           ok.........Variable, die ueberprueft ob alles ok ist
///           dummy......Hilfsvariable fuer die Eingabepruefung bei sscanf
///           zahl.......Zahl, welche eingelesen wird
///********************************************
///Return-Wert: Wert der Zahl wenn alles OK ist
///             0 wenn ein Fehler aufgetreten ist
///********************************************
int liesInt()
{
    char eingabe[4096];
    int ok;
    char dummy;
    int zahl;

    do
    {
        ok = sscanf(gets(eingabe), "%d%c", &zahl, &dummy);
        if(ok != 1)
            return 0;

    }
    while(ok != 1);
    return zahl;
}
///********************************************
///Funk.-Name: filtermenue
///Zweck:      Anzeigen des Auswahlmenues, wo der User auswählen kann, nach was er filtern will
///********************************************
///Variablen: user.......Variable, wo die User-Auswahl gespeichert wird
///           ok.........Variable, die ueberprueft ob alles ok ist
///           dummy......Variable, die nur als Wartespeicher fuer getch dient
///           userpreis..Variable, die speichert, nach welchem Preiskriterium der Nutzer sortieren will
///********************************************
///Return-Wert: gewaehlter Menuepunkt des Users
///********************************************
int filtermenue()
{
    char user;
    char dummy=0;
    char userpreis;
    int ok = 0;

    do
    {
        system("cls");
        printf("\n\n\tFiltern");
        printf("\n\t=========");
        printf("\n\n\tNach welchen Kriterien moechten Sie filtern?");
        printf("\n\t(1)Preis");
        printf("\n\t(2)Titel");
        printf("\n\t(3)Buchnummer");

        printf("\n\n\tIhre Auswahl --> ");
        user = getch();

        switch(user)
        {
        case '1':
            system("cls");
            printf("\n\n\tMoechten Sie nach mehr oder weniger angegebenem Preis filtern?");
            printf("\n\t(1)Mehr");
            printf("\n\t(2)Weniger");
            printf("\n\tIhre Auswahl -->");

            userpreis = getch();

            switch(userpreis)
            {
            case '1':
                return 1;
                break;
            case '2':
                return 2;
            }

            break;
        case '2':
            ok = 1;
            return 3;
            break;
        case '3':
            ok = 1;
            return 4;
            break;
        default:
            system("cls");
            fprintf(stderr, "Diese Option gibt es nicht. Bitte versuchen Sie es nochmal.");
            Sleep(3000);
            system("cls");
            ok = 0;
            break;
        }

    }
    while(ok != 1);
    return dummy;
}
///********************************************
///Funk.-Name: menue
///Zweck:      Anzeigen des Auswahlmenues, wo der User auswählen kann, wass er tun will
///********************************************
///Variablen: user.......Variable, wo die User-Auswahl gespeichert wird
///           ok.........Variable, die ueberprueft ob alles ok ist
///           dummy......Variable, die nur als Wartespeicher fuer getch dient
///********************************************
///Return-Wert: gewaehlter Menuepunkt des Users
///********************************************
int menue()
{
    char user;  ///Variable um User-Auswahl zu speichern
    int ok; ///Wie lange die Schleife laufen soll, bis alles ok ist
    char dummy;
    system("cls");
    do
    {
        ///Ausgabe aller Optionen
        printf("\n\n\tWillkommen! Bitte waehlen Sie einen der folgenden Menuepunkte aus!");
        printf("\n\t===================================================================");
        printf("\n\n\t(1) Neues Buch hinzufuegen");
        printf("\n\t(2) Ein Buch entfernen");
        printf("\n\t(3) Buchtitel aendern");
        printf("\n\t(4) Nach Buechern suchen / filtern");
        printf("\n\t(5) Buch entnehmen");
        printf("\n\t(6) Ausgabe aller Buecher");
        printf("\n\t(7) Ausgabe des gesamten Lagerwertes");
        printf("\n\t(8) Ausgabe der Bestelllisten");
        printf("\n\t(9) Speichern in einer neuen Datei");
        printf("\n\t(E) Das Programm beenden");

        printf("\n\n\tIhre Auswahl --> "); ///Aufforderung zum Eingeben
        user = getch(); ///Einlesen der gewuenschten Option mit getch()

        switch(user)
        {
        case '1':
            return 1;
            ok = 1;
            break;
        case '2':
            return 2;
            ok = 1;
            break;
        case '3':
            return 3;
            ok = 1;
            break;
        case '4':
            return 4;
            ok = 1;
            break;
        case '5':
            return 5;
            ok = 1;
            break;
        case '6':
            return 6;
            ok = 1;
            break;
        case '7':
            return 7;
            ok = 1;
            break;
        case '8':
            return 8;
            ok = 1;
            break;
        case '9':
            return 9;
            ok = 1;
            break;

        case 'E':
            return 10;
            ok = 1;
            break;
        default: ///Falls ein nicht vorhandene Option ausgewaehlt wurde, wird der default Block ausgefuehrt
            system("cls");
            fprintf(stderr, "\n\tDiese Option gibt es nicht!"); ///Ausgabe der Fehlermeldung
            dummy = getch();///Warten auf den User
            system("cls");
            ok = 0;
            break;
        }



    }
    while(ok != 1);

    return dummy;

}

///********************************************
///Funk.-Name: fuegeBuecherFeldHinzu
///Zweck:      Anlegen des Feldes von Buechern beim Start des Programms
///********************************************
///Parameter: dateipfad..Ort, wo die Datei, aus der gelesen wird, steht
///           feld.......Das Feld von Buechern
///           n..........Anzahl der Buecher
///           maximal....-
///********************************************
///Variablen: fp......FILE Pointer
///           i.......Laufvariable fuer Schleife
///           maximal.Groesse des Buecherfeldes
///********************************************
///Return-Wert: Startadresse des Buecherfeldes
///             NULL bei Fehler
///********************************************

buch_t *fuegeBuecherFeldHinzu(char *dateipfad, buch_t *feld, int *n, int *maximal)
{
    FILE *fp;

    char ein[4096];



    fp = fopen(dateipfad, "r"); ///Oeffnen der Datei

    if(!fp) ///Ueberpruefen ob man was bekommen hat
    {
        printf("\n\tBeim Oeffnen der Datei %s ist ein Fehler aufgetreten! Stellen Sie sicher, dass sich die Datei am angegebenen Ort befindet!\n", dateipfad);
        return NULL;
    }

    while(fgets(ein, sizeof(ein), fp)) ///Einlesen der Zeilen der CSV Dateien mit fgets
    {
        ein[strlen(ein)] = '\0';   ///Abschneiden von "\n" Escape Sequenz
        (*n)+=erstelleNeuesBuch(ein, feld, *n); ///Aufrufen der erstelleNeuesBuch-Funktion und bei erfolgreichen Datensätzen wird 1 addiert, bei anderen 0
        if((((*n)*100) / (*maximal)) >= 80)     ///Ueberpruefen, ob die aktuelle Feldgroesse groesser oder gleich 80 ist
        {
            (*maximal)+=10; ///Um mehr Speicher anzufordern, wird zur maximalen Feldgroesse 10 dazu addiert
            feld = (buch_t*) realloc(feld, (*maximal)*sizeof(buch_t));  ///Anfordern von mehr Speicher mittels realloc
            if(!feld) ///Falls realloc NULL zurueckliefert, wird feld freigegeben und Programm beendet
            {
                printf("\n\tBeim Erweitern des Speichers ist ein Fehler aufgetreten! Programm wird nun beendet!\n");
                exit(0); ///Beenden des Programms
                freeData(feld, *maximal); ///Freigeben des jetzigen Feldes

            }
        }

    }
    rewind(fp); ///SPI auf Anfangsposition setzen
    fclose(fp); ///Schließen des File-Pointers
   return feld; ///Zurueckgeben des Feldes

}
///********************************************
///Funk.-Name: erstelleNeuesBuch
///Zweck:      Anlegen der Daten für ein neues Buch & Kopieren auf Bücherfeld
///********************************************
///Parameter: buecher....Feld, in dem die Daten fuer Buecher gespeichert werden
///           anzahlAlkt.Aktuelle Anzahl der Buecher
///           textzeile..String, wo alle Daten in CSV Form stehen
///
///********************************************
///Variablen: hstr........Hilfsstring zum Speichern des Rückgabewertes von strtok()
///           i...........Laufvariable fuer Schleife
///           delimiter...In diesem String steht das Zeichen, nach welchem strtok trennen soll
///           preis.......In dieser Variable wird der Preis gespeichert
///           bestand.....In dieser Variable wird der Bestand gespeichert
///           ok..........Variable fuer sscanf um zu ueberpruefen, ob aus Datensatz rausgelesen werden kann
///********************************************
///Return-Wert: 0: ein Fehler ist aufgetreten / ungueltiger Datensatz
///             1: alles OK
///********************************************
int erstelleNeuesBuch(char *textzeile, buch_t *buecher, int anzahlAkt)
{

    char *hstr;
    char *delimiter = ";";
    int richtigcounter = 0;
    double preis=0;
    int bestand=0;
    int ok = 0;
    size_t i = 0;



    ///Einspeichern und Ueberpruefen der Buch-Nr.
    ///******************************************
    hstr = strtok(textzeile, delimiter); ///Abschneiden der Buchnummer
    if(!hstr)
        return 0;


    if(gueltigeBuchNummer(hstr))  ///Ueberpruefen der Buchnummer mittels Funktion
    {
        strcpy((buecher+anzahlAkt)->buchNummer, hstr);  ///Wenn Buchnummer gueltig ist, wird sie an entsprechende Position kopiert
        richtigcounter++;   ///Rchtigcounter auf 1 setzen
    }
    else
        return 0;
    ///******************************************
    ///Einspeichern des Buchtitels
    ///******************************************
    hstr = strtok(NULL, delimiter);  ///Abschneiden des Titels
    if(!hstr)       ///Wenn strtok NULL returned, wird abgebrochen
        return 0;

    (buecher+anzahlAkt)->titel = (char*) calloc((strlen(hstr)+1), sizeof(char));  ///Anfordern von Speicher fuer Buechertitel

    if(!((buecher+anzahlAkt)->titel))  ///Wenn Calloc NULL returned, wird abgebrochen
        return 0;

    strcpy((buecher+anzahlAkt)->titel, hstr); ///Kopieren des Titels auf entsprechenen Platz
    richtigcounter++; ///Richtigcounter auf 2 setzen

    ///***************************************
    ///Einspeichern des Bestands
    ///****************************************
    hstr = strtok(NULL, delimiter); ///Abschneiden des Bestands
    if(!hstr)
        return 0;


    ok = sscanf(hstr, "%d", &bestand); ///Einscannen des Bestands
    if(ok != 1 || bestand <= 0) ///Ueberpruefen ob Preis < 0 oder ein Eingabefehler aufgetreten ist
        return 0;
    else
    {
        (buecher+anzahlAkt)->bestand = bestand; ///Kopieren des Bestands an die richtige Stelle
        richtigcounter++;   ///Richtigcounter auf 3 setzen
    }
    ///******************************************
    ///Einspeichern des Preises
    ///******************************************
    hstr = strtok(NULL, delimiter); ///Abschneiden des Preises
    if(!hstr)
        return 0;

    ok = sscanf(hstr, "%lf", &preis); ///Einscannen des Preises
    if(ok != 1 || preis < 0)    ///Ueberpruefen ob der Preis < 0 ist oder ein Eingabefehler aufgetreten ist, dann wird abgebrochen
        return 0;
    else
    {
        (buecher+anzahlAkt)->preis = preis; ///Kopieren des Preises
        richtigcounter++;   ///Richtigcounter auf 4 setzten
    }
    ///****************************************
    ///Ueberpruefen, ob noch mehr Dinge in String stehen
    hstr = strtok(NULL, delimiter);


    if(hstr != NULL)
        richtigcounter++; ///Falls es noch etwas gibt, wir
    ///****************************************

    if(richtigcounter==4)       ///Uebepruefen, ob 4 Sachen in der Zeile gestanden sind
    {
        for(i = 0; i < anzahlAkt; i++) ///In Schleife bis anzahlAkt durchgehen
        {
            ///Falls buchNummer und Titel gleich sind, werden sie zusammengefasst
            if((strcmp((buecher+i)->buchNummer, (buecher+anzahlAkt)->buchNummer) == 0)
                    &&(strcmp((buecher+i)->titel, (buecher+anzahlAkt)->titel) == 0))     ///Ueberpruefen ob buchNr und Titel gleich sind, wenn ja wird if-Block ausgefuehert
            {
                (buecher+i)->bestand += (buecher+anzahlAkt)->bestand; ///Aufaddieren des Bestandes
                (buecher+i)->preis = (buecher+anzahlAkt)->preis;   ///Ueberschreiben mit neuem Preis
                free((buecher+anzahlAkt)->titel);  ///Freigeben des Speichers fuer Titel
                free(&buecher[anzahlAkt]);        ///Freigeben des Speichers fuer den entsprechenden Platz des Buecherfeldes
                return 0;
            }
            else if((strcmp((buecher+i)->buchNummer, (buecher+anzahlAkt)->buchNummer) == 0)) ///Ueberpruefen, ob buchNr gleich ist, aber nicht zu Titel passt -> Datensatz wird verworfen
            {
                free((buecher+anzahlAkt)->titel); ///Freigeben von Titel-Speicher
                free(&buecher[anzahlAkt]);  ///Freigeben von
                return 0;
            }
        }

        return 1;
    }
    else
        return 0;

}
///********************************************
///Funk.-Name: gueltigeBuchNummer
///Zweck:      Zum Überprüfen, ob der übergebene
///            Text eine gültige Buchnummer darstellt.
///********************************************
///Parameter: buch....Adresse, wo das auszugebende Buch steht
///********************************************
///Variablen / Arrays: text....Char Pointer wo Buchnummer
///                    steht
///                    i.......Laufvariable für die for-Schleife
///                    size...Variable um Größe des text-Arrays
///                    zu speichern
///********************************************
///Return-Wert: 0: keine gueltige Buchnummer
///             1: gueltige Buchnummer
///********************************************
int gueltigeBuchNummer(char *text)
{
    int i = 0;

    int size = strlen(text);
    if(size != 10) ///Ueberpruefen, ob eine Buchnummer 10 Zeichen lang ist, sonst ist sie nicht gueltig
        return 0;


    for(i = 0; i < size-7; i++)
    {
        if(!isupper(text[i])) ///Es wird ueberprueft, ob das uebergebene Zeichen ein Großbuchstabe ist
            return 0;   ///Falls richtig, wird Fehlerwert zurueckgeliefert
    }

    for(i = 3; i < size; i++)
    {
        if(!isdigit(text[i])) ///Es wird überprüft, ob das uebergebene Zeichen eine Ziffer ist
            return 0;         ///Falls richtig, wird Fehlerwert zurueckgeliefert
    }

    return 1;
}
///********************************************
///Funk.-Name: sucheBuch
///Zweck:      Zum Überprüfen, ob der übergebene
///            Text eine gültige Buchnummer darstellt.
///********************************************
///Parameter: buecher...Buecherfeld
///           n.........Anzahl der Buecher
///           suchText..Text nach dem gesucht werden soll
///           titelOderNummer... Ob nach Titel oder Nummer gesucht werden soll
///********************************************
///Variablen / Arrays:
///                    i.......Laufvariable für die for-Schleife
///********************************************
///Return-Wert: NULL wenn kein Buch gefunden wurde
///             Adresse des Buches bei Fund
///********************************************
buch_t *sucheBuch(buch_t *buecher, int n, char *suchText,int titelOderNummer)
{
    size_t i;
    switch(titelOderNummer)
    {
    case 1:
        for(i = 0; i < n; i++)
        {
            if(strcmp(((buecher+i)->titel),suchText)==0) ///Wenn strstr etwas findet, wird zurueckgegeben
                return(buecher+i);
        }
        break;
    case 2:
        for(i = 0; i < n; i++)
        {
            if(strcmp(((buecher+i)->titel),suchText)==0)///Wenn strstr etwas findet, wird zurueckgegeben
               return(buecher+i);

        }
        break;
    }

    return NULL;
}
///********************************************
///Funk.-Name: sucheBuch
///Zweck:      Zum Überprüfen, ob der übergebene
///            Text eine gültige Buchnummer darstellt.
///********************************************
///Parameter: buecher...Buecherfeld
///           anzahlAkt.Aktuelle Anzahl der Buecher
///           suchText..Text nach dem gesucht werden soll
///           maximal...Feldgroesse
///********************************************
///Variablen / Arrays:
///                    ein,buchnummer,titel...Eingabestrings fuer Zahlen, Buchnummer & Titel
///                    preis, bestand.........Hierauf werden jeweils Preis und Bestand gespeichert
///                    ok, dummy..............fuer Eingabeueberpruefung
///********************************************
///Return-Wert: 0 wenn ein Fehler aufgetreten ist
///             1 wenn Buch erfolgreich hinzugefuegt wurde
///********************************************
int buchZugang(buch_t *buecher, int anzahlAkt, int *maximal)
{

    char ein[4096];
    char buchnummer[4096];
    char titel[4096];
    double preis=0;
    int bestand=0;
    int ok;
    char dummy;

    size_t i;
    if((((anzahlAkt)*100) / (*maximal)) >= 80)     ///Ueberpruefen, ob die aktuelle Feldgroesse groesser oder gleich 80 ist
        {
            (*maximal)+=10; ///Um mehr Speicher anzufordern, wird zur maximalen Feldgroesse 10 dazu addiert
            buecher = (buch_t*) realloc(buecher, (*maximal)*sizeof(buch_t));  ///Anfordern von mehr Speicher mittels realloc
            if(!buecher) ///Falls realloc NULL zurueckliefert, wird feld freigegeben und Programm beendet
            {
                printf("\n\tBeim Erweitern des Speichers ist ein Fehler aufgetreten! Programm wird nun beendet!\n");
                exit(0); ///Beenden des Programms
                freeData(buecher, *maximal); ///Freigeben des jetzigen Feldes

            }
        }

    system("cls");
    printf("\n\n\tNeues Buch einlesen");
    printf("\n\t=====================");

    do
        ///Einlesen der Buchnummer
    {
        printf("\n\n\tBitte geben Sie eine Buchnummer ein --> ");
        gets(buchnummer);  ///Einlesen der Buchnummer
        ok = gueltigeBuchNummer(buchnummer); ///Ueberpruefen der Buchnummer
        if(ok != 1)
        {
            fprintf(stderr, "\n\tDie Buchnummer ist nicht gueltig.");
            ok = 0;
        }

    }
    while(ok != 1);

    do
    {
        printf("\n\n\tBitte geben Sie einen Bestand fuer das Buch ein --> ");
        ok = liesInt(); ///Einlesen des Bestands

        if(ok == 0)
        {
            fprintf(stderr, "\n\tEingabefehler. Bitte wiederholen Sie ihre Eingabe.");
            bestand = 0;
        }

        if(ok <= 0)
        {
            fprintf(stderr,"Der Bestand darf nicht kleiner oder gleich 0 sein!");
            ok = 0;
        }

        bestand = ok;
    }
    while(ok == 0);
    ok = 0;
    do
    {
        printf("\n\tBitte geben Sie einen Preis fuer das neue Buch ein --> ");
        ok = sscanf(gets(ein), "%lf%c", &preis, &dummy); ///Einlesen des Preises
        if(ok != 1)
            fprintf(stderr, "\n\tEingabefehler. Bitte wiederholen Sie ihre Eingabe.");

        if(preis <= 0) ///Darf nicht kleiner oder gleich 0 sein
        {
            fprintf(stderr,"\n\tDer Preis darf nicht kleiner oder gleich 0 sein!");
            ok = 0;
        }
    }
    while(ok != 1);
    do{
    printf("\n\tBitte geben Sie einen Titel fuer das neue Buch ein --> ");
    gets(titel);
    if(strlen(titel)==0)
    {
        fprintf(stderr, "\n\tSie muessen einen Titel eingeben!");
        ok = 0;
    }
    else
        ok = 1;
    }while(ok != 1);
    ///Bei gleicher Buchnummer und Titel werden Buchnummer und Titel aufeinander kopiert
    for(i = 0; i < anzahlAkt; i++)
    {
        if(strcmp(((buecher+i)->buchNummer), buchnummer) == 0 && strcmp(((buecher+i)->titel), titel) == 0)
        {
            (buecher+i)->bestand+=bestand;
            (buecher+i)->preis = preis;
            return 2;

        }
    }



    strcpy(((buecher+anzahlAkt)->buchNummer), buchnummer);

    ((buecher+anzahlAkt)->titel) = (char*) calloc(strlen(titel)+1, sizeof(char)); ///Anfordern von Speicher fuer Calloc
    if(!((buecher+anzahlAkt)->titel))
    {
        fprintf(stderr, "\n\tSpeicher fuer den Titel des neuen Buches konnte nicht angefordert werden.");
        return 0;
    }

    strcpy(((buecher+anzahlAkt)->titel), titel);

    ((buecher+anzahlAkt)->preis) = preis;
    ((buecher+anzahlAkt)->bestand) = bestand;

    return 1;

}
void buchEntnahme(buch_t *buecher, int anzahl)
{
    size_t i = 0;
    int wieviele;
    int ok;
    int buchpos;
    char dummy, eingabe[4096];
    char buchnr[4096];
    printf("\n\n\tBuchentnahme");
    printf("\n\t==============");
    listeBuchbestand(buecher, anzahl);

    do
    {
        printf("\n\tWelches Buch wollen Sie entnehmen?");
        printf("\n\tBitte geben Sie die Buchnummer ein --> ");
        gets(buchnr);

        ok = gueltigeBuchNummer(buchnr); ///Einlesen der Buchnummer
        if(ok != 1)
        {
            fprintf(stderr, "\n\tSie haben keine gueltige Buchnummer eingegeben!");
            return;
        }
        for(i = 0; i < anzahl; i++)
        {
            if(strcmp((buecher+i)->buchNummer, buchnr) == 0)
            {
                buchpos = i;
                ok = 1;
            }
        }

    }

    while(ok != 1);
     if(ok == 0)
            fprintf(stderr, "\n\tDas Buch konnte nicht gefunden werden!Bitte wiederholen Sie Ihre Eingabe!");



    ok = 0;

    do
    {
        printf("\n\tWieviele Buecher wollen Sie entnehmen?");
        printf("\n\tGeben Sie bitte die Anzahl ein -->");
        ok = sscanf(gets(eingabe), "%d%c", &wieviele, &dummy);

        if(ok != 1)
            fprintf(stderr, "\n\tEingabefehler. Bitte wiederholen Sie Ihre Eingabe.");

    }
    while(ok != 1);

    if(wieviele<=0)
    {
         fprintf(stderr, "\n\tSie duerfen keine Minus-Werte eingeben! Abbruch!");
        dummy = getch();
        return;
    }
    if((buecher+buchpos)->bestand <= wieviele)
    {


        fprintf(stderr, "\n\tDer Bestand darf nicht unter 0 sinken oder gleich 0 sein! Abbruch!");
        dummy = getch();
        return;
    }


    (buecher+buchpos)->bestand-=wieviele; ///Subtrahieren des Bestandes
    printf("\n\tDer Bestand des Buches mit der Buchnummer %s und Titel \"%s\" wurde auf %d veraendert.", (buecher+buchpos)->buchNummer,
           (buecher+buchpos)->titel, (buecher+buchpos)->bestand);
    dummy = getch(); ///warten auf User
    return;

}

int buchEntfernen(buch_t *buecher, int anzahl, char *buchNummer)
{
    int i, j = 0;

    if(gueltigeBuchNummer(buchNummer)==1) ///Ueberpruefen auf neue Buchnummer
    {
        for(i = 0; i < anzahl; i++)
        {
            if(strcmp((buecher+i)->buchNummer, buchNummer) == 0)
            {
                for(j = i; j < anzahl; j++)
                    buecher[j] = buecher[j+1]; ///Kopieren der Daten auf neue Position, damit Buch ueberschrieben wird bzw. geloescht wird

                return 1; ///Funktion beenden und 1 für erfolgreich zurückgeben
            }
        }
    }

    return 0; ///Falls nichts passiert ist, wird 0 als nicht geloescht zurückgegeben

}

void aendereTitel(buch_t *buchAdresse)
{
    char eingabe[4096];

    size_t strilenneu=0;

    printf("\n\tBitte geben Sie einen neuen Titel ein --> ");
    gets(eingabe); ///Einlesen des neuen Titels
    strilenneu =  strlen(eingabe); ///Berecnen
    (buchAdresse->titel) = (char*)realloc((buchAdresse->titel),strilenneu+1*sizeof(char)); ///Reallokieren des Speichers fuer neuen String
    if(!(buchAdresse->titel)) ///Wenn etwas schiefgelaufen ist, gibt er eine Fehlermeldung aus;
    {
        fprintf(stderr,"\n\tBeim Anfordern von Speicher fuer den Titel ist ein Fehler aufgetreten!");
        return;
    }
    strcpy(buchAdresse->titel, eingabe); ///Kopieren des neuen Titels auf den alten Titel
    return;
}

///********************************************
///Funk.-Name: printBuchData
///Zweck:      Ausgeben des Tabellenheaders
///********************************************
///Parameter: -
///********************************************
///Variablen: -
///********************************************
///Return-Wert: -
///********************************************
void printTableHeader()
{
    puts("\n\t  Buch-Nr.  |                     Titel                  |       Bestand       |       Preis      ");
    puts("\t==========================================================================================================");
}
void listeBuchbestand(buch_t *buecher, int anzahl)
{
    size_t i;
    printTableHeader();
    for(i = 0; i < anzahl; i++)
    {
        printBuchData(buecher+i);
    }
}

///********************************************
///Funk.-Name: printBuchData
///Zweck:      Ausgeben der Daten eines Buches
///********************************************
///Parameter: buch....Adresse, wo das auszugebende Buch steht
///********************************************
///Variablen: -
///********************************************
///Return-Wert: -
///********************************************
void printBuchData(buch_t *buch)
{
    printf("\t%10s  |     %30s         |        %5d           |        %.2lf        \n",(buch->buchNummer), (buch->titel), (buch->bestand), (buch->preis));
}
///********************************************
///Funk.-Name: printBuchList
///Zweck:      Ausgeben der Daten eines Buches in Listenform
///********************************************
///Parameter: buch....Adresse, wo das auszugebende Buch steht
///********************************************
///Variablen: -
///********************************************
///Return-Wert: -
///********************************************
void printBuchList(buch_t *buch)
{
    printf("\n\tBuch-Nummer: %s", buch->buchNummer);
    printf("\n\tTitel:       %s", buch->titel);
    printf("\n\tBestand:     %d", buch->bestand);
    printf("\n\tPreis:       %.2lf", buch->preis);
}
///********************************************
///Funk.-Name: listeBuchBestandGeordnet
///Zweck:      Ausgeben der Daten eines Buches in einer sortierten Form (nach ordnungNach)
///********************************************
///Parameter: buecher......Adresse wo die Buecher stehen
///           anzahl.......Anzahl der Buecher
///           ordnungNach..Wonach sortiert werden soll (wählbar von User)
///********************************************
///Variablen: buch_t copy..Kopie des Buecherfeldes
///                     i..Laufvariable fuer die For-Schleife
///********************************************
///Return-Wert: -
///********************************************
void listeBuchbestandGeordnet(buch_t *buecher, int anzahl, int ordnungNach)
{
    buch_t *copy;
    int i;

    copy = (buch_t*) calloc(anzahl+1, sizeof(buch_t)); ///allkieren von speicher fuer Copy

    if(!copy)
    {
        fprintf(stderr, "Beim Anlegen des Speichers fuer die Kopie ist ein Fehler aufgetreten. Es wird nun abgebrochen.");
        return;
    }


    ///Allokieren von Speicher fuer Titel und kopieren von Daten auf Kopie-FEld
    for(i=0; i < anzahl; i++)
    {
        strcpy(((copy+i)->buchNummer), (buecher+i)->buchNummer);
        (copy+i)->titel = (char*) calloc(strlen((buecher+i)->titel)+1, sizeof(char));

        if((copy+i)->titel == NULL)
        {
            fprintf(stderr, "Beim Allokieren von Speicher fuer den titel der Kopie ist ein Fehler aufgetreten.");
            return;
        }

        strcpy(((copy+i)->titel),(buecher+i)->titel);

        (copy+i)->bestand = (buecher+i)->bestand;
        (copy+i)->preis   = (buecher+i)->preis;
    }

    switch(ordnungNach)
    {
    case 1:
        qsort(copy, anzahl, sizeof(buch_t), cmpPreis); ///Aufrufen von Q-Sort
        listeBuchbestand(copy, anzahl);
        break;
    case 2:
        qsort(copy, anzahl, sizeof(buch_t), cmpTitel);
        listeBuchbestand(copy, anzahl);
        break;
    case 3:
        qsort(copy, anzahl, sizeof(buch_t), cmpBuchNr);
        listeBuchbestand(copy, anzahl);
        break;
    }

    for(i=0; i < anzahl; i++)
    {
        free((copy+i)->titel);
        free((copy+i));
    }
}


///********************************************
///Funk.-Name: bestellListe
///Zweck:      Ausgeben aller Buecher, deren Bestand kleiner  5 Stueck ist
///********************************************
///Parameter: buecher.....Buecherfeld wo die Daten stehen
///           anzahl......Anzahl der Buecher
///********************************************
///Variablen: i...........Laufvariable fuer die Schleife
///********************************************
///Return-Wert: -
void bestellListe(buch_t *buecher, int anzahl)
{
    size_t i;
    printTableHeader();
    for(i = 0; i < anzahl; i++)
    {
        if((buecher+i)->bestand < 5)
            printBuchData(buecher+i); ///Wenn bestand < 5, Ausgabe
    }
}

///********************************************
///Funk.-Name: lagerWert
///Zweck:      Berechnen des gesamten Wertes des Lagerbestandes
///********************************************
///Parameter: buecher....Buecherfeld wo Daten stehen
///           anzahl.....Anzahl der Buecher
///********************************************
///Variablen: wert....Variable, worauf die Preise raufaddiert werden
///           i.......Laufvariable fuer Schleife
///********************************************
double lagerWert(buch_t *buecher, int anzahl)
{
    size_t i;          ///Laufvariable fuer Schleife
    double wert = 0;///Hierauf werden die Preise addiert

    for(i = 0; i < anzahl; i++)
        wert+=(((buecher+i)->preis)*((buecher+i)->bestand)); ///Addieren von Preis * Bestand zu Variable wert
    return wert;
}

///********************************************
///Funk.-Name: titelFilter
///Zweck:      Filtern nach Titeln mit einem benutzerdefinierten Suchstring
///********************************************
///Parameter: buecher....Buecherfeld, wo die Daten stehen
///           anzahl.....Anzahl der Buecher
///           suchText...Der Text, nach welchem gesucht werden soll
///********************************************
///Variablen:   returnstring....Dynamischer Pointer fuer den Return-String von strstr()
///             i...............Laufvariable fuer die Schleife
///********************************************
///Return-Wert: keiner
///********************************************
void titelFilter(buch_t *buecher, int anzahl, char *suchText)
{
    size_t i;
    char *returnstring;

    for(i = 0; i < anzahl; i++)
    {
        returnstring = strstr((buecher+i)->titel, suchText);

        if(returnstring != NULL)
            printBuchData(buecher+i);
    }


}
///********************************************
///Funk.-Name: nummerFilter
///Zweck:      Filtern nach Nummer mit einem benutzerdefinierten Suchstring
///********************************************
///Parameter: buecher....Buecherfeld, wo die Daten stehen
///           anzahl.....Anzahl der Buecher
///           suchText...Der Text, nach welchem gesucht werden soll
///********************************************
///Variablen:   returnstring....Dynamischer Pointer fuer den Return-String von strstr()
///             i...............Laufvariable fuer die Schleife
///********************************************
///Return-Wert: keiner
///********************************************
void nummerFilter(buch_t *buecher, int anzahl, char *suchText)
{
    size_t i;
    char *returnstring;

    for(i = 0; i < anzahl; i++)
    {
        returnstring = strstr((buecher+i)->buchNummer, suchText); ///Einspeichern von returnstirng

        if(returnstring != NULL)
            printBuchData(buecher+i);
    }
}
///********************************************
///Funk.-Name: preisFilter
///Zweck:      Filtern nach Preis mit einem benutzerdefinierten Preisangabe
///********************************************
///Parameter: buecher....Buecherfeld, wo die Daten stehen
///           anzahl.....Anzahl der Buecher
///           vergleichsPreis...Preis mit dem verglichen werden soll
///           mehrOderWeniger...Ob mehr oder Weniger gesucht werden soll
///********************************************
///Variablen:
///             i...............Laufvariable fuer die Schleife
///********************************************
///Return-Wert: keiner
///********************************************
void preisFilter(buch_t *buecher, int anzahl, double vergleichsPreis,int mehrOderWeniger)
{
    size_t i;
    switch(mehrOderWeniger)
    {
    case 0:
        for(i = 0; i < anzahl; i++)
        {
            if((buecher+i)->preis >= vergleichsPreis) ///Wird gefunden --> Ausgabe
                printBuchData(buecher+i);
        }
        break;
    case 1:
        for(i = 0; i < anzahl; i++)
        {
            if((buecher+i)->preis <= vergleichsPreis) ///Wird gefunden --> Ausgabe
                printBuchData(buecher+i);
        }
        break;
    }

}
///********************************************
///Funk.-Name: speichereBuecher
///Zweck:      Speichert Daten von Buecherfeld in Datei
///********************************************
///Parameter: buecher....Buecherfeld, wo die Daten stehen
///           anzahl.....Anzahl der Buecher
///           dateipfad...Pfad der Datei
///***********************************************
///Return-Wert: -
///********************************************
int speichereBuecher (char *dateipfad, buch_t *buecher, int anzahl)
{
    FILE *fp,///File-Pointer fuer erstes Mal oeffnen, um zu schauen, ob es datei noch gibt
         *output;///File-Pointer um neue oder "alte" Datei zu oeffnen und hinzuschreiben
    char user;  ///Variable um die Wahl des Nutzers zu speichern
    int i;
    char csvTEXT[4096]; ///Array um Pointer von toCSVText zu speichern
    char neuName[4096];
    strcat(dateipfad, ".csv"); ///.csv an Dateinamen anhaengen

    fp = fopen(dateipfad, "r"); ///Oeffnen der Datei
    system("cls");
    printf("\n\n\tDaten in Datei speichern");
    printf("\n\t==============================");

    if(fp != NULL)
    {
        printf("\n\tDie Datei %s exisitiert bereits!", dateipfad);
        printf("\n\n\t(1)Neue Datei anlegen");
        printf("\n\t(2)Existierende Datei ueberschreiben");
        printf("\n\n\tIhre Auswahl --> ");
        user = getch();

        switch(user)
        {
        case '1':
            system("cls");
            printf("\n\n\tBitte geben Sie den Namen der neuen Datei ein (ohne .csv!) --> ");
            gets(neuName);
            strcat(neuName, ".csv");
            output = fopen(neuName, "at");
            if(!output)
            {

                return 0;
            }
            fprintf(output, "Buchnummer;Titel;Bestand;Preis\n"); ///Reinschreiben der Ueberschriften wie in orig. CSV-Datei
            for(i = 0; i < anzahl; i++)
            {
                toCSVText(buecher+i, csvTEXT); ///Konvertieren von Buecherdaten in CSV-Text und rueckschreiben auf Char Array
                fputs(csvTEXT, output);  ///Schreiben von CSV-Zeile in Datei
            }
            return 1; ///Zurueckgeben, dass Datei erfolgreich neu erstellt und gespeichert wurde
            fclose(fp);         ///Schließen des File-Pointers
            fclose(output);    ///Schließen des File-Pointers
            break;
        case '2':
            output = fopen(dateipfad, "wt");
            if(!output)
            {

                return 2;
            }

            fprintf(output, "Buchnummer;Titel;Bestand;Preis\n");
            for(i = 0; i < anzahl; i++)
            {
                toCSVText(buecher+i, csvTEXT); ///Konvertieren von Buecherdaten in CSV-Text und rueckschreiben auf Char Array
                fputs(csvTEXT, output);  ///Schreiben von CSV-Zeile in Datei
            }
            return 3; ///Zurueckgeben, dass Datei erfolgreich ueberschrieben wurde
            fclose(fp);         ///Schließen des File-Pointers
            fclose(output);    ///Schließen des File-Pointers
            break;

        }
    }

    else
    {
        output = fopen(dateipfad, "wt");
        if(!output)
        {
            return 2;
        }

        fprintf(output, "Buchnummer;Titel;Bestand;Preis\n");
        for(i = 0; i < anzahl; i++)
        {
            toCSVText(buecher+i, csvTEXT); ///Konvertieren von Buecherdaten in CSV-Text und rueckschreiben auf Char Array
            fputs(csvTEXT, output);  ///Schreiben von CSV-Zeile in Datei
        }
        return 1; ///Zurueckgeben, dass Datei erfolgreich neu erstellt und gespeichert wurde
        fclose(fp);         ///Schließen des File-Pointers
        fclose(output);    ///Schließen des File-Pointers


    }
    return 0;
}

///********************************************
///Funk.-Name: toCSVText
///Zweck:      Buecherdaten in CSV Form verwandeln
///********************************************
///Parameter: buch.......Buchfeld, wo Daten stehen
///           csvText....Pointer, in dem Text reingeschrieben wird
///********************************************
///Return-Wert: keiner
///********************************************
void toCSVText(const buch_t* buch, char *csvText)
{
    sprintf(csvText, "%s; %s; %d; %.2lf\n", (buch->buchNummer), (buch->titel), (buch->bestand), (buch->preis)); ///Verwandeln in CSV Text
    return;
}
///********************************************
///Funk.-Name: freeData
///Zweck:      Freigeben aller dynamisch angeforderten Daten
///********************************************
///Parameter: buecher.......Buecherfeld, wo Daten stehen
///           anzahl........Anzahl der Daten
///********************************************
///Return-Wert: keiner
///********************************************
void freeData(buch_t *buecher, int anzahl)
{
    size_t i;

    for(i = 0; i < anzahl; i++)
    {
        free((buecher+i)->titel);
        free((buecher+i));
    }
}
///********************************************
///Funk.-Name: cmpTitel
///Zweck:      CMP-Funktion fuer Q-Sort
///********************************************
///Parameter: *a...erster Wert
///           *b...zweiter Wert
///********************************************
///Return-Wert: -1 a kommt vor b
///              0 beide gleich
///              1 b vor a
///********************************************

int cmpTitel(const void *a, const void *b)
{
    buch_t *e1 = (buch_t*) a;
    buch_t *e2 = (buch_t*) b;


    return stricmp((e1->titel),(e2->titel));
}
///********************************************
///Funk.-Name: cmpPreis
///Zweck:      CMP-Funktion fuer Q-Sort
///********************************************
///Parameter: *a...erster Wert
///           *b...zweiter Wert
///********************************************
///Return-Wert: -1 a kommt vor b
///              0 beide gleich
///              1 b vor a
///********************************************
int cmpPreis(const void *a, const void *b)
{
    buch_t *e1 = (buch_t*) a;
    buch_t *e2 = (buch_t*) b;

    return ((e1->preis) < (e2->preis) ? -1 : ((e1->preis) > (e2->preis)) ? 1 : 0);
}
///********************************************
///Funk.-Name: cmpBuchNr
///Zweck:      CMP-Funktion fuer Q-Sort
///********************************************
///Parameter: *a...erster Wert
///           *b...zweiter Wert
///********************************************
///Return-Wert: -1 a kommt vor b
///              0 beide gleich
///              1 b vor a
///********************************************
int cmpBuchNr(const void *a, const void *b)
{
    buch_t *e1 = (buch_t*) a;
    buch_t *e2 = (buch_t*) b;

    return stricmp((e1->buchNummer),(e2->buchNummer));
}

///********************************************
///Funk.-Name: calcbookPOS
///Zweck:      Berechnet Buchposition und gibt sie zurueck
///********************************************
///Parameter: buecher.......Buecherfeld
///           anzahl........Anzahl der Buecher
///           buchnr.......Buchnummer, mit der verglichen wird
///********************************************
///Return-Wert: position des Buches
///********************************************
int calcbookPos(buch_t *buecher, int anzahl, char *buchnr)
{
    size_t i;
    for(i = 0; i < anzahl; i++)
    {
        if(strcmp(((buecher+i)->buchNummer), buchnr) == 0)
            return i;
    }
    return 0;
}

