#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define pi 3.14159265359

float** Gen_sin(int, float, int);
float* szum(int);
void DodajSzum(float**, float*, int);
void ZapisWykres(float**, int, char*);
float** OdczytWykres(char*);
float** Odszum(float**, int);
void RysujWykres(float**, int, char*,int);

int main(void){
    int i, N, okres, ile, nr=0, istnieje=0;
    float tp;
    float** tab=0;
    char nazwa[255];
    char rozszerzenie[5] = ".csv";

   
   while (1)
    {
        switch (nr)
        {
            case 0:
                printf(" 1. Generuj sygnal\n 2. Rysuj wykres\n 3. Zapisz do pliku\n 4. Wczytaj z pliku\n 5. Odszumiaj\n 6. Zakoncz\n\n ");
                scanf("%d", &nr);

                system("cls");
                break;
            case 1:
                printf("Generujesz funkcje\n\nPodaj wartosc tp: "); 
                scanf("%f", &tp);
                printf("Podaj okres: ");
                scanf("%d", &okres);

                ile = 10000 * tp;
                N = (okres * ile);
                tab = Gen_sin(N, tp, ile);

                printf("\nCzy dodac szum?\n1. tak\n2. nie\n");
                scanf("%d", &nr);

                nr += 10;

                system("cls");
                break;
            case 11:
                DodajSzum(tab, szum(N), N);

                nr = 0;
                istnieje = 1;

                break;
            case 12:
                nr = 0;
                istnieje = 1;

                break;
            case 2:
                if (istnieje == 0) {
                    printf("Nie podano funkcji\n\n");

                    nr = 0;
                    break;
                }
                else {
                    RysujWykres(tab, N, "wykres.html", 0);
                    system("wykres.html");

                    nr = 0;
                    break;
                }
            case 3:
                if (istnieje == 0) {
                    printf("Nie podano funkcji\n\n");

                    nr = 0;
                    break;
                }
                else {
                    printf("Podaj nazwe pliku: ");
                    scanf("%s", &nazwa);

                    ZapisWykres(tab, N, strcat(nazwa, rozszerzenie));

                    nr = 0;
                    system("cls");
                    break;
                }
            case 4:
                system("dir *.csv");
                printf("Podaj nazwe pliku: ");
                scanf("%s", &nazwa);

                if (OdczytWykres(nazwa)==0){
                    system("cls");
                    printf("Plik nie istnieje\n\n");

                    nr = 0;
                    break;
                }
                else{
                    RysujWykres(OdczytWykres(nazwa), (int)OdczytWykres(nazwa)[0][0], "wykres.html", 1);
                    system("wykres.html");

                    system("cls");
                    nr = 0;
                    break;
                }
            case 5:
                if (istnieje == 0) {
                    printf("Nie podano funkcji\n\n");

                    nr = 0;
                    break;
                }
                else {
                    RysujWykres(Odszum(tab, N), N, "wykres.html", 0);
                    system("wykres.html");

                    nr = 0;
                    system("cls");
                    break;
                }
            case 6:
                exit(1);

                break;
            default: 
                printf("Blad\n\n");

                nr = 0;
                break;
        }
    }
    return 0;
}

float** Gen_sin(int N, float tp,int ile){
    float** tab_sin;
    int i,cof = 0,j=0;

    tab_sin = calloc(sizeof(float*), 4);

    for (i = 0; i < 4; i++)
        tab_sin[i] = calloc(sizeof(float), N);

    for (i = 0; i < N; i++) {
        tab_sin[0][i] = tp * (i);
        tab_sin[1][i] = cos(20 * pi * tab_sin[0][i - ((ile*cof)+cof)]) * exp(-tab_sin[0][i - ((ile * cof)+cof)]);

        if (j == ile){
            j = 0;
            cof++;
        }
        else
            j++;
    }
    return tab_sin;
}

float* szum(int N){
    float* tab;
    int i;

    srand(time(NULL));
    tab = calloc(sizeof(float), N);

    for (i = 0; i < N; i++){
        if (i % 5 == 0)
            tab[i] = (rand() % 101)-50;

        else
            tab[i] = 0;
    }
    return tab;
}

void DodajSzum(float** tab_sin, float* tab, int N){
    int i;

    tab_sin[2] = tab;

    for (i = 0; i < N; i++) 
        tab_sin[3][i] = tab_sin[1][i] + (tab_sin[2][i]/1000)-2;
}

void ZapisWykres(float** dane, int l_linii, char* nazwa2){
    FILE* zapis;
    int i;

    zapis = fopen(nazwa2, "w");

    for (i = 0; i < l_linii; i++)
        fprintf(zapis, "%f;%f;%f\n", dane[0][i], dane[1][i], dane[3][i]);

    fclose(zapis);
}

float** OdczytWykres(char* nazwa3){
    FILE* odczyt;
    int i, j, liczba_linii=0;
    char znak;
    float** tab_sin2 = 0;

    if ((odczyt = fopen(nazwa3, "r")) == NULL)
        return 0;
    
        while (!feof(odczyt))
        {
            znak = fgetc(odczyt);

            if (znak == '\n')
                liczba_linii++;
        }

        rewind(odczyt);


        tab_sin2 = calloc(sizeof(float*), 4);

        for (i = 0; i < 4; i++)
            tab_sin2[i] = calloc(sizeof(float), liczba_linii+1);
    
        tab_sin2[0][0] = liczba_linii;

        for (j = 1; j < liczba_linii; j++)
            fscanf(odczyt, "%f;%f;%f", &tab_sin2[0][j], &tab_sin2[1][j], &tab_sin2[3][j]);

        fclose(odczyt);
    

    return tab_sin2;
}
float** Odszum(float** tab_sin3, int N){
    int i,j;
    float suma = 0;

    for ( i = 0; i < N-5; i++)
    {
        for ( j = 0; j < 5; j++)
            suma = suma + tab_sin3[3][i];
        
        suma = suma / 5;
        tab_sin3[3][i] = suma;
    }
    return tab_sin3;
}

void RysujWykres(float** dane, int l_linii, char* nazwa, int od) {

    FILE* Wsk_do_pliku;
    int i;

    Wsk_do_pliku = fopen(nazwa, "w");

    fprintf(Wsk_do_pliku, "<html>\n");
    fprintf(Wsk_do_pliku, "<head>\n");
    fprintf(Wsk_do_pliku, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
    fprintf(Wsk_do_pliku, "<script type=\"text/javascript\">\n");
    fprintf(Wsk_do_pliku, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
    fprintf(Wsk_do_pliku, "google.setOnLoadCallback(drawChart);\n");
    fprintf(Wsk_do_pliku, "function drawChart() {\n");
    fprintf(Wsk_do_pliku, "var data = google.visualization.arrayToDataTable([\n");
    fprintf(Wsk_do_pliku, "['t', 'cos','szum']");

    for (i = od; i < l_linii; i++)
        fprintf(Wsk_do_pliku, ",\n[%f, %f, %f]", dane[0][i], dane[1][i], dane[3][i]);

    fprintf(Wsk_do_pliku, "\n]);\n");
    fprintf(Wsk_do_pliku, "var options = {\n");
    fprintf(Wsk_do_pliku, "title: 'S19'\n");
    fprintf(Wsk_do_pliku, "};\n");
    fprintf(Wsk_do_pliku, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
    fprintf(Wsk_do_pliku, "chart.draw(data, {\n");
    fprintf(Wsk_do_pliku, "colors: ['red','blue','green','yellow']\n");
    fprintf(Wsk_do_pliku, "}\n");
    fprintf(Wsk_do_pliku, ");\n");
    fprintf(Wsk_do_pliku, "}\n");
    fprintf(Wsk_do_pliku, "</script>\n");
    fprintf(Wsk_do_pliku, "</head>\n");
    fprintf(Wsk_do_pliku, "<body>\n");
    fprintf(Wsk_do_pliku, "<div id=\"chart_div\" style=\"width: 1920px; height: 720px;\"></div>\n");
    fprintf(Wsk_do_pliku, "</body>\n");
    fprintf(Wsk_do_pliku, "</html>\n");
    fclose(Wsk_do_pliku);
}