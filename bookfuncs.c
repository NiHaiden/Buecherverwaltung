#include "bookfunc.h"
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
int filtermenue()
{
    char user;
    char dummy;
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
        printf("\n\t(?) Ausgabe der Hilfe");
        printf("\n\t(E) Das Programm beenden");

        printf("\n\n\tIhre Auswahl --> ");
        user = getch();

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
        case '?':
            ok = 1;
            return 10;
            break;
        case 'E':
            return 11;
            ok = 1;
            break;
        default: ///Falls ein nicht vorhandene Option ausgewaehlt wurde, wird der default Block ausgefuehrt
            system("cls");
            fprintf(stderr, "\n\tDiese Option gibt es nicht!");
            dummy = getch();
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
    int fcloseok;


    fp = fopen(dateipfad, "r");

    if(!fp)
    {
        printf("\n\tBeim Oeffnen der Datei %s ist ein Fehler aufgetreten! Stellen Sie sicher, dass sich die Datei am angegebenen Ort befindet!\n", dateipfad);
        return NULL;
    }

    while(fgets(ein, sizeof(ein), fp))
    {
        ein[strlen(ein)] = '\0';   ///Abschneiden von "\n" Escape Sequenz
        (*n)+=erstelleNeuesBuch(ein, feld, *n);
        if((((*n)*100) / (*maximal)) >= 80)     ///Ueberpruefen, ob die aktuelle Feldgroesse groesser oder gleich 80 ist
        {
            (*maximal)+=10; ///Um mehr Speicher anzufordern, wird zur maximalen Feldgroesse 10 dazu addiert
            feld = (buch_t*) realloc(feld, (*maximal)*sizeof(buch_t));  ///Anfordern von mehr Speicher mittels realloc
            if(!feld) ///Falls realloc NULL zurueckliefert, wird feld freigegeben und Programm beendet
            {
                printf("\n\tBeim Erweitern des Speichers ist ein Fehler aufgetreten! Programm wird nun beendet!\n");
                exit(0);
                free(feld);

            }
        }

    }
    rewind(fp);
    fcloseok = fclose(fp);
    if(fcloseok==1)
    {
        return feld;
    }
    else
    {
        printf("Beim Schliessen der Datei ist ein Fehler aufgetreten!");
        return feld;
    }

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
///           preis
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
    hstr = strtok(textzeile, delimiter);
    if(!hstr)
        return 0;


    if(gueltigeBuchNummer(hstr))  ///Ueberpruefen der Buchnummer mittels Funktion
    {
        strcpy((buecher+anzahlAkt)->buchNummer, hstr);  ///Wenn Buchnummer gueltig ist, wird sie an entsprechende Position kopiert
        richtigcounter++;
    }
    else
        return 0;
    ///******************************************
    ///Einspeichern des Buchtitels
    ///******************************************
    hstr = strtok(NULL, delimiter);  ///Abschneiden des Titels
    if(!hstr)
        return 0;

    (buecher+anzahlAkt)->titel = (char*) calloc((strlen(hstr)+1), sizeof(char));  ///Anfordern von Speicher fuer Buechertitel

    if(!((buecher+anzahlAkt)->titel))  ///Wenn Calloc NULL returned, wird abgebrochen
        return 0;

    strcpy((buecher+anzahlAkt)->titel, hstr);
    richtigcounter++;

    ///***************************************
    ///Einspeichern des Bestands
    ///****************************************
    hstr = strtok(NULL, delimiter);
    if(!hstr)
        return 0;


    ok = sscanf(hstr, "%d", &bestand);
    if(ok != 1 || bestand <= 0)
        return 0;
    else
    {
        (buecher+anzahlAkt)->bestand = bestand;
        richtigcounter++;
    }
    ///******************************************
    ///Einspeichern des Preises
    ///******************************************
    hstr = strtok(NULL, delimiter);
    if(!hstr)
        return 0;

    ok = sscanf(hstr, "%lf", &preis);
    if(ok != 1 || preis < 0)
        return 0;
    else
    {
        (buecher+anzahlAkt)->preis = preis;
        richtigcounter++;
    }
    ///****************************************
    ///Ueberpruefen, ob noch mehr Dinge in String stehen
    hstr = strtok(NULL, delimiter);


    if(hstr != NULL)
        richtigcounter++;
    ///****************************************

    if(richtigcounter==4)       ///Uebepruefen, ob 4 Sachen in der Zeile gestanden sind
    {
        for(i = 0; i < anzahlAkt; i++) ///In Schleife bis anzahlAkt durchgehen
        {
            ///Falls buchNummer und Titel gleich sind, werden sie zusammengefasst
            if((strcmp((buecher+i)->buchNummer, (buecher+anzahlAkt)->buchNummer) == 0)
                    &&(strcmp((buecher+i)->titel, (buecher+anzahlAkt)->titel) == 0))     ///Ueberpruefen ob buchNr und Titel gleich sind
            {
                (buecher+i)->bestand += (buecher+anzahlAkt)->bestand;
                (buecher+i)->preis = (buecher+anzahlAkt)->preis;
                free((buecher+anzahlAkt)->titel);
                free(&buecher[anzahlAkt]);
                return 0;
            }
            else if((strcmp((buecher+i)->buchNummer, (buecher+anzahlAkt)->buchNummer) == 0))
            {
                free((buecher+anzahlAkt)->titel);
                free(&buecher[anzahlAkt]);
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

buch_t *sucheBuch(buch_t *buecher, int n, char *suchText,int titelOderNummer)
{
    size_t i;
    switch(titelOderNummer)
    {
    case 1:
        for(i = 0; i < n; i++)
        {
            if(strcmp(((buecher+i)->titel),suchText)==0)
                return (buecher+i);


        }
        break;
    case 2:
        for(i = 0; i < n; i++)
        {
            if(strcmp(((buecher+i)->buchNummer),suchText)==0)
                return (buecher+i);

        }
        break;
    }

    return NULL;
}

int buchZugang(buch_t *buecher, int anzahlAkt)
{
    FILE *fp;
    char ein[4096];
    char buchnummer[4096];
    char titel[4096];
    double preis=0;
    int bestand=0;
    int ok;
    char dummy;
    char user;
    size_t i;

    system("cls");
    printf("\n\n\tEinlesen eines neuen Buches / neuer Buecher");
    printf("\n\t=============================================");

    do
    {
        printf("\n\n\tMoechten Sie ein neues Buch oder Buecher aus einer Datei einlesen?");
        printf("\n\t(1)Ein neues Buch einlesen");
        printf("\n\t(2)Buecher aus CSV Dateien einlesen");
        printf("\n\n\tIhre Auswahl -> ");
        user = getch();
        if(user != '1')
        {
            fprintf(stderr, "\n\tDiese Option gibt es nicht!");
            ok = 0;
        }
        else if(user != '2')
            {
            fprintf(stderr, "\n\tDiese Option gibt es nicht!");
            ok = 0;
            }
            else
                ok = 1;

    }while(ok != 1);

    ok = 0;

    switch(user){
case '1':
    system("cls");
    printf("\n\n\tNeues Buch einlesen");
    printf("\n\t=====================");

    do
    {
        printf("\n\n\tBitte geben Sie eine Buchnummer ein --> ");
        gets(buchnummer);
        ok = gueltigeBuchNummer(buchnummer);
        if(ok != 1)
        {
            fprintf(stderr, "\n\tDie Buchnummer ist nicht gueltig.");
            ok = 0;
        }

    }while(ok != 1);

   do
   {
        printf("\n\n\Bitte geben Sie einen Bestand fuer das Buch ein --> ");
        ok = liesInt();

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
   }while(ok == 0);
   ok = 0;
   do
   {
       printf("\n\tBitte geben Sie einen Preis fuer das neue Buch ein --> ");
       ok = sscanf(gets(ein), "%lf%c", &preis, &dummy);
       if(ok != 1)
        fprintf(stderr, "\n\tEingabefehler. Bitte wiederholen Sie ihre Eingabe.");
   }while(ok != 1);

   printf("\n\tBitte geben Sie einen Titel fuer das neue Buch ein --> ");
    break;
    }
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

        ok = gueltigeBuchNummer(buchnr);
    if(ok != 1)
    {
        fprintf(stderr, "Sie haben keine gueltige Buchnummer eingegeben!");
        return;
    }
        for(i = 0; i < anzahl; i++)
        {
            if(strcmp((buecher+i)->buchNummer, buchnr) == 0)
            {
                buchpos = i;
                ok = 1;
            }
            else
            {
                fprintf(stderr, "\n\tDas Buch konnte nicht gefunden werden.\n\tBitte wiederholen Sie ihre Eingabe!");
                ok = 0;
            }
        }
    }
    while(ok != 1);

    ok = 0;

    do
    {
        printf("\n\tWieviele Buecher wollen Sie entnehmen?");
        printf("\n\tGeben Sie bitte die Anzahl ein -->");
        ok = sscanf(gets(eingabe), "%d%c", &wieviele, &dummy);

        if(ok != 1)
            fprintf(stderr, "Eingabefehler. Bitte wiederholen Sie Ihre Eingabe.");

    }
    while(ok != 1);

    if((buecher+buchpos)->bestand < wieviele)
    {
        fprintf(stderr, "\n\tDer Bestand darf nicht unter 0 sinken! Abbruch!");
        return;
    }


    (buecher+buchpos)->bestand-=wieviele;
    printf("\n\tDer Bestând des Buches mit der Buchnummer %s und Titel %s wurde auf %d veraendert.", (buecher+buchpos)->buchNummer,
           (buecher+buchpos)->titel, (buecher+buchpos)->bestand);
    return;

}

int buchEntfernen(buch_t *buecher, int anzahl, char *buchNummer)
{
    int i, j = 0;

    if(gueltigeBuchNummer(buchNummer))
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

    printf("\n\tBitte geben Sie einen neuen Titel ein!");
    gets(eingabe);
    strilenneu =  strlen(eingabe);
    (buchAdresse->titel) = (char*)realloc((buchAdresse->titel),strilenneu+1*sizeof(char)); ///Reallokieren des Speichers fuer neuen String
    if(!(buchAdresse->titel)) ///Wenn etwas schiefgelaufen ist, gibt er eine Fehlermeldung aus;
    {
        fprintf(stderr,"\n\tBeim Anfordern von Speicher fuer den Titel ist ein Fehler aufgetreten!");
        return;
    }
    strcpy(buchAdresse->titel, eingabe);
    return;
}


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
    printf("\t%10s  |     %30s         |        %2d           |        %.2lf        \n",(buch->buchNummer), (buch->titel), (buch->bestand), (buch->preis));
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

    copy = (buch_t*) calloc(anzahl+1, sizeof(buch_t));

    if(!copy)
    {
        fprintf(stderr, "Beim Anlegen des Speichers fuer die Kopie ist ein Fehler aufgetreten. Es wird nun abgebrochen.");
        return;
    }



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
        qsort(copy, anzahl, sizeof(buch_t), cmpPreis);
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
            printBuchData(buecher+i);
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
void nummerFilter(buch_t *buecher, int anzahl, char *suchText)
{
    size_t i;
    char *returnstring;

    for(i = 0; i < anzahl; i++)
    {
        returnstring = strstr((buecher+i)->buchNummer, suchText);

        if(returnstring != NULL)
            printBuchData(buecher+i);
    }
}
void preisFilter(buch_t *buecher, int anzahl, double vergleichsPreis,int mehrOderWeniger)
{
    size_t i;
    switch(mehrOderWeniger)
    {
    case 0:
        for(i = 0; i < anzahl; i++)
        {
            if((buecher+i)->preis >= vergleichsPreis)
                printBuchData(buecher+i);
        }
        break;
    case 1:
        for(i = 0; i < anzahl; i++)
        {
            if((buecher+i)->preis <= vergleichsPreis)
                printBuchData(buecher+i);
        }
        break;
    }

}
int speichereBuecher (char *dateipfad, buch_t *buecher, int anzahl)
{

}


void toCSVText(const buch_t* buch, char *csvText)
{
    sprintf(csvText, "%s; %s; %d; %.2lf", (buch->buchNummer), (buch->titel), (buch->bestand), (buch->preis));
    return;
}

void freeData(buch_t *buecher, int anzahl)
{
    size_t i;

    for(i = 0; i < anzahl; i++)
    {
        free((buecher+i)->titel);
        free((buecher+i));
    }
}


int cmpTitel(const void *a, const void *b)
{
    buch_t *e1 = (buch_t*) a;
    buch_t *e2 = (buch_t*) b;


    return strcmp((e1->titel),(e2->titel));
}

int cmpPreis(const void *a, const void *b)
{
    buch_t *e1 = (buch_t*) a;
    buch_t *e2 = (buch_t*) b;

    return ((e1->preis) < (e2->preis) ? -1 : ((e1->preis) > (e2->preis)) ? 1 : 0);
}

int cmpBuchNr(const void *a, const void *b)
{
    buch_t *e1 = (buch_t*) a;
    buch_t *e2 = (buch_t*) b;

    return strcmp((e1->buchNummer),(e2->buchNummer));
}

void help()
{
    system("cls");
    printf("\n\n\tHilfe");
    printf("\n\t=======");
    printf("\n\tMittels verschiedenen Funktionen koennen Sie\n");
    printf("\n\t\t");

}
