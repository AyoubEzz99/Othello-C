#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Livrable1.h"
#include "Livrable2.h"
#include <windows.h>

HANDLE wHnd; // Handle to write to the console.
HANDLE rHnd; // Handle to read from the console.

/* Largeur de la grille */
#define N 8

/* Pions du jeu */
#define VIDE ' '
#define NOIR 'X'  /* joueur 1 */
#define BLANC 'O' /* joueur 2 */

/* type du tableau des scores */
typedef struct score
{
    int s;
    char nom[20];
} sc;

int main()
{
    //Console options
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    //Change the window title:
    SetConsoleTitle("Othello - Projet C");
    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 114, 27};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    int i, z, k, j, x = 0, numero_partie, temp, y;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    t_matrice m;
    char player1[20], player2[20];
    sc T[100];
    char c, var, nom[10], l[130], P[130];
    FILE *fp;
    FILE *f;
    FILE *flot;
    FILE *h;
    do
    {

        printf("+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  MENU   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
        printf("|                                                                                                               |\n");
        printf("+                                                                                                               +\n");
        printf("|                Donner le mode de joue que vous voulez :                                                       |\n");
        printf("+                                          **** Les MODES ****                                                  +\n");
        printf("|                                                                                                               |\n");
        printf("+                                 1- Humain vs  Humain                                                          +\n");
        printf("|                                 2- Humain vs  Machine  :  Avec des positions aleatoires                       |\n");
        printf("+                                 3- Humain vs  Machine  :  Niveau  moyen                                       +\n");
        printf("|                                 4- Humain vs  Machine  :  Niveau avance                                       |\n");
        printf("+                                                                                                               +\n");
        printf("|                                                                                                               |\n");
        printf("+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
        printf("                                         Votre choix : ");
        scanf("%d", &y);

        switch (y)
        {

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////// ****** HUMAIN VS HUMAIN  ******* ///////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 1:
        {

            playgame();

            h = fopen("numeropartie.txt", "r+");
            if (h != NULL)
            {
                fseek(h, 0, SEEK_SET);
                var = fgetc(h);
                temp = 0;
                while (var != EOF)
                {
                    fscanf(h, "%d", &numero_partie);
                    var = fgetc(h);
                    if (var == EOF)
                        temp = numero_partie;
                }
            }
            fclose(h);

            flot = fopen("les coups des parties.txt", "r+");
            fseek(flot, 0, SEEK_SET);
            fscanf(flot, "\nPartie %d \n", &i);
            i++;
            fscanf(flot, "%s \n", P);
            while (i <= temp + 1)
            {
                fscanf(flot, "\nPartie %d \n", &i);
                fscanf(flot, "%s \n", P);
                i++;
            }
            printf("\n                                                     %d                                           \n", i);
            fclose(flot);
            printf("\n\n\n                  ************ Les coups de la partie ***********");
            printf("\n\n                   %s", P);
        }
        break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////// ****** AVEC POSITION ALEATOIRE ( Cas simple )******* ////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 2:
        {

            playgame_EASY();

            h = fopen("numeropartie.txt", "r+");
            if (h != NULL)
            {
                fseek(h, 0, SEEK_SET);
                var = fgetc(h);
                temp = 0;
                while (var != EOF)
                {
                    fscanf(h, "%d", &numero_partie);
                    var = fgetc(h);
                    if (var == EOF)
                        temp = numero_partie;
                }
            }
            fclose(h);

            flot = fopen("les coups des parties.txt", "r+");
            fseek(flot, 0, SEEK_SET);
            fscanf(flot, "\nPartie %d \n", &i);
            i++;
            fscanf(flot, "%s \n", P);
            while (i <= temp + 1)
            {
                fscanf(flot, "\nPartie %d \n", &i);
                fscanf(flot, "%s \n", P);
                i++;
            }
            printf("\n                                                     %d                                           \n", i);
            fclose(flot);
            printf("\n\n\n                  ************ Les coups de la partie ***********");
            printf("\n\n                   %s", P);
        }
        break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////// ****** AVEC POSITION ALEATOIRE ( niveau moyen )******* ////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 3:
        {

            playgame_RND();

            h = fopen("numeropartie.txt", "r+");
            if (h != NULL)
            {
                fseek(h, 0, SEEK_SET);
                var = fgetc(h);
                temp = 0;
                while (var != EOF)
                {
                    fscanf(h, "%d", &numero_partie);
                    var = fgetc(h);
                    if (var == EOF)
                        temp = numero_partie;
                }
            }
            fclose(h);

            flot = fopen("les coups des parties.txt", "r+");
            fseek(flot, 0, SEEK_SET);
            fscanf(flot, "\nPartie %d \n", &i);
            i++;
            fscanf(flot, "%s \n", P);
            while (i <= temp + 1)
            {
                fscanf(flot, "\nPartie %d \n", &i);
                fscanf(flot, "%s \n", P);
                i++;
            }
            printf("\n                                                     %d                                           \n", i);
            fclose(flot);
            printf("\n\n\n                  ************ Les coups de la partie ***********");
            printf("\n\n                   %s", P);
        }
        break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////// ****** AVANCE AVEC ALGO MIN_MAX******* ////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 4:
        {
            playgame_AI();

            h = fopen("numeropartie.txt", "r+");
            if (h != NULL)
            {
                fseek(h, 0, SEEK_SET);
                var = fgetc(h);
                temp = 0;
                while (var != EOF)
                {
                    fscanf(h, "%d", &numero_partie);
                    var = fgetc(h);
                    if (var == EOF)
                        temp = numero_partie;
                }
            }
            fclose(h);

            flot = fopen("les coups des parties.txt", "r+");
            fseek(flot, 0, SEEK_SET);
            fscanf(flot, "\nPartie %d \n", &i);
            i++;
            fscanf(flot, "%s \n", P);
            while (i <= temp + 1)
            {
                fscanf(flot, "\nPartie %d \n", &i);
                fscanf(flot, "%s \n", P);
                i++;
            }
            printf("\n                                                     %d                                           \n", i);
            fclose(flot);
            printf("\n\n\n                  ************ Les coups de la partie ***********");
            printf("\n\n                   %s", P);
        }
        break;
        }
        printf("\n\n\n\nVoulez vous jouer un nouveau jeu ? (o: oui ou autre caractere: non)? ");
        scanf("%s", &c);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    } while (c == 'o');

    /////////////////////////////// ********    Les meilleures scores   *********///////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    FILE *g = fopen("Les scores.txt", "r+");
    fseek(g, 0, SEEK_SET);
    fscanf(g, "\n%s %02d", T[0].nom, &T[0].s);
    x++;
    while (fscanf(g, "%s %02d", T[x].nom, &T[x].s) != '\n' && fscanf(g, "%s %02d", T[x + 1].nom, &T[x + 1].s) != EOF)
    {
        x = x + 2;
    }
    sc index;
    for (k = 0; k < x - 1; k++)
    {
        for (j = k + 1; j < x; j++)
        {
            if (T[j].s >= T[k].s)
            {
                index = T[j];
                T[j] = T[k];
                T[k] = index;
            }
        }
    }
    char b;

    printf("Voulez vous afficher les 10 meilleurs scores  ? (o: oui ou autre caractere: non)? \n\n ");
    scanf("%s", &b);
    if (b == 'o')
    {
        printf("\n\n\n                 *****les meilleurs scores*****\n");
        if (x >= 9)
        {

            printf("                    ========================\n");

            for (k = 0; k < 9; k++)
            {
                printf("                      %d-  %s %02d       \n", k + 1, T[k].nom, T[k].s);
            }
            printf("                     %d-  %s %02d       \n", 10, T[9].nom, T[9].s);
            printf("                    ========================\n\n\n");
        }
        else
        {
            printf("                    ========================\n");
            printf("                                          \n");
            for (k = 0; k < x; k++)
            {
                printf("                      %d-  %s %02d       \n", k + 1, T[k].nom, T[k].s);
            }
            printf("                    ========================\n\n\n");
        }
    }

    /////////////////////////////////////////*     Chargement de la partie sauvgarder *////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    char charger;
    printf("voulez vous charger une partie ? (o: oui     autre caractere: non ) :");
    fflush(stdin);
    scanf("%c", &charger);
    if (charger == 'o')
    {
        printf("Donner le numero de la partie que vous voulez charger :");
        scanf("%d", &z);
        flot = fopen("les coups des parties.txt", "r+");
        fseek(flot, 0, SEEK_SET);
        fscanf(flot, "\nPartie %d \n", &i);
        fscanf(flot, "%s \n", l);
        i++;
        while (i <= z)
        {
            fscanf(flot, "Partie %d \n", &i);
            fscanf(flot, "%s \n", l);
            i++;
        }
        playgame_charge(l);
        printf("%d", strlen(l));
        fclose(flot);
        printf("\n\n\n\n                                     *******FIN____Partie*******\n\n\n\n");
        printf("\n");
        getchar();
    }
    printf("\n\n\n\n                                     *******FIN____Programme*******\n\n\n\n");

    return 0;
}
