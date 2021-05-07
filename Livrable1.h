#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* Largeur de la grille */
#define N 8

/* Pions du jeu */
#define VIDE ' '
#define NOIR 'X'  /* joueur 1 */
#define BLANC 'O' /* joueur 2 */

/* Type du plateau de jeu */
typedef char t_matrice[N][N];

/* Fonction pour initialiser la grille */
void init_matrice(t_matrice m)
{
    int i, j;

    /* On met tout a vide */
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            m[i][j] = VIDE;

    /* On place les 4 premiers pions */
    m[N / 2 - 1][N / 2 - 1] = NOIR;
    m[N / 2 - 1][N / 2] = BLANC;
    m[N / 2][N / 2 - 1] = BLANC;
    m[N / 2][N / 2] = NOIR;
}

/* Fonction pour afficher la grille */
void afficher_matrice(t_matrice m)
{
    int i, j;
    char a = 'A';

    /* Affichage des lettres */
    printf("\n  ");
    for (i = 0; i < N; i++)
    {
        printf("   %c  ", a);
        a++;
    }

    /* Affichage de la grille */
    printf("\n +");
    for (i = 0; i < N; i++)
        printf("-----+");
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf(" ");
        for (j = 0; j < N; j++)
            if (m[i][j] == BLANC)
                printf("|  %c  ", m[i][j]);
            else
                printf("|  %c  ", m[i][j]);
        printf("|");
        printf("  %d\n +", i + 1);
        for (j = 0; j < N; j++)
            printf("-----+");
        printf("\n");
    }
}

/* Fonction pour verifier qu'une case existe */

int case_existe(int lig, int col)
{
    return ((col >= 0) && (col < N) && (lig >= 0) && (lig < N));
}

/* Fonction pour verifier qu'un coup est valide */

int coup_valide(t_matrice m, int lig, int col, int joueur)
{

    int i, j, ok;
    char cj, ca;

    /* On definit la couleur du joueur et celle de l'adversaire */

    if (joueur == 1)
    {
        cj = NOIR;
        ca = BLANC;
    }
    else
    {
        cj = BLANC;
        ca = NOIR;
    }
    if (!case_existe(lig, col) || m[lig][col] != VIDE)
        return 0;

    /* Vertical vers le haut */

    i = lig - 1;
    ok = 0;
    while (case_existe(i, col) && m[i][col] == ca)
    {
        i--;
        ok = 1;
    }
    if (case_existe(i, col) && m[i][col] == cj && ok == 1)
        return 1;

    /* Vertical vers le bas */

    i = lig + 1;
    ok = 0;
    while (case_existe(i, col) && m[i][col] == ca)
    {
        i++;
        ok = 1;
    }
    if (case_existe(i, col) && m[i][col] == cj && ok == 1)
        return 1;

    /* Horizontal vers la gauche */

    j = col - 1;
    ok = 0;
    while (case_existe(lig, j) && m[lig][j] == ca)
    {
        j--;
        ok = 1;
    }
    if (case_existe(lig, j) && m[lig][j] == cj && ok == 1)
        return 1;

    /* Horizontal vers la droite */

    j = col + 1;
    ok = 0;
    while (case_existe(lig, j) && m[lig][j] == ca)
    {
        j++;
        ok = 1;
    }
    if (case_existe(lig, j) && m[lig][j] == cj && ok == 1)
        return 1;

    /* Diagonal \ vers le haut */

    i = lig - 1;
    j = col - 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i--;
        j--;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1)
        return 1;

    /* Diagonal \ vers le bas */

    i = lig + 1;
    j = col + 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i++;
        j++;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1)
        return 1;

    /* Diagonal / vers le haut */

    i = lig - 1;
    j = col + 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i--;
        j++;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1)
        return 1;

    /* Diagonal / vers le bas */

    i = lig + 1;
    j = col - 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i++;
        j--;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1)
        return 1;

    return 0;
}

/* Fonction qui determine si un joueur peut encore jouer */

int peut_jouer(t_matrice m, int joueur)
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (coup_valide(m, i, j, joueur))
                return 1; /* Le joueur peut encore jouer */

    /* Le joueur ne peut plus jouer */
    return 0;
}

/* Renvoie le numero du joueur suivant */
int joueur_suivant(int joueur)
{
    return (joueur % 2 + 1);
}

/* Permet au joueur de choisir un coup */
void choisir_coup(t_matrice m, int *lig, int *col, int joueur)
{
    char c;
    FILE *flot;
    FILE *fp;
    flot = fopen("les coups des parties.txt", "a");
    printf("\nC'est au tour du joueur %d de jouer\n", joueur);
    printf("Choisissez une case (ex: A1) :\n");
    scanf("\n%c", &c);

    /* On change les minuscules en majuscules */
    if ((c >= 'a') && (c < 'a' + N))
        c = c + 'A' - 'a';
    (*col) = c - 'A';

    scanf("%d", lig);

    // 	On ecrit dans les deux fichier "DETAIL"   et  "les coups des parties"  les coups choisit
    fprintf(flot, "%c", c);
    fprintf(flot, "%d", *lig);
    fclose(flot);

    fp = fopen("DETAIL.txt", "a");
    fprintf(fp, "%c", c);
    fprintf(fp, "%d ", *lig);
    fclose(fp);
    (*lig)--;

    /* On redemande de choisir tant que le coup n'est pas accepte */
    while (!coup_valide(m, *lig, *col, joueur))
    {
        printf("\nCe coup n'est pas valide\n");
        printf("Choisissez une autre case (ex: A1) :\n");
        scanf("\n%c", &c);
        /* On change les minuscules en majuscules */
        if ((c >= 'a') && (c < 'a' + N))
            c = c + 'A' - 'a';
        (*col) = c - 'A';
        scanf("%d", lig);
        (*lig)--;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void choisir_coup_CPU(t_matrice m, int *lig, int *col, int joueur)
{
    char c;

    printf("\nC'est au tour du joueur %d de jouer\n", joueur);
    printf("Choisissez une case (ex: A1) :\n");
    scanf("\n%c", &c);

    /* On change les minuscules en majuscules */
    if ((c >= 'a') && (c < 'a' + N))
        c = c + 'A' - 'a';
    (*col) = c - 'A';

    scanf("%d", lig);
    (*lig)--;

    /* On redemande de choisir tant que le coup n'est pas accepte */
    while (!coup_valide(m, *lig, *col, joueur))
    {
        printf("\nCe coup n'est pas valide\n");
        printf("Choisissez une autre case (ex: A1) :\n");
        scanf("\n%c", &c);
        /* On change les minuscules en majuscules */
        if ((c >= 'a') && (c < 'a' + N))
            c = c + 'A' - 'a';
        (*col) = c - 'A';
        scanf("%d", lig);
        (*lig)--;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/* Verifie si la partie est terminee */

int partie_terminee(t_matrice m)
{
    int i, j, nb_noir, nb_blanc, cpt;

    /* On compte les picns noirs et les blancs */
    nb_noir = 0;
    nb_blanc = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (m[i][j] == VIDE && (peut_jouer(m, 1) || peut_jouer(m, 2)))
            {
                return 0; /* La partie n'est pas finie */
            }
            else
            {
                if (m[i][j] == NOIR)
                    nb_noir++;
                else if (m[i][j] == BLANC)
                    nb_blanc++;
            }
        }
    }

    /* La partie est terminee, on affiche le gagnant */
    if (nb_noir > nb_blanc)
        printf("\nLe joueur 1 a gagne !!!\n");
    else if (nb_blanc > nb_noir)
        printf("\nLe joueur 2 a gagne !!!\n");
    else
        printf("\nLes deux joueurs sont a egalite\n");

    /* On range les pions par couleur et on affiche la grille */
    cpt = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            if (cpt < nb_noir)
                m[i][j] = NOIR;
            else if ((cpt >= nb_noir) && (cpt < nb_noir + nb_blanc - 1))
                m[i][j] = BLANC;
            else
                m[i][j] = VIDE;
            cpt++;
        }
    afficher_matrice(m);
    printf("\n");
    return 1;
}

/* Fonction qui permet de jouer un coup */
void jouer_coup(t_matrice m, int lig, int col, int joueur)
{
    int i, j;
    char cj, ca;

    if (joueur == 1)
    {
        cj = NOIR;
        ca = BLANC;
    }
    else
    {
        cj = BLANC;
        ca = NOIR;
    }
    m[lig][col] = cj;

    /* Vertical vers le haut */
    i = lig - 1;
    while (case_existe(i, col) && m[i][col] == ca)
        i--;
    if (case_existe(i, col) && m[i][col] == cj)
    {
        i = lig - 1;
        while (m[i][col] == ca)
        {
            m[i][col] = cj;
            i--;
        }
    }

    /* Vertical vers le bas */
    i = lig + 1;
    while (case_existe(i, col) && m[i][col] == ca)
        i++;
    if (case_existe(i, col) && m[i][col] == cj)
    {
        i = lig + 1;
        while (m[i][col] == ca)
        {
            m[i][col] = cj;
            i++;
        }
    }

    /* Horizontal vers la gauche */
    j = col - 1;
    while (case_existe(lig, j) && m[lig][j] == ca)
        j--;
    if (case_existe(lig, j) && m[lig][j] == cj)
    {
        j = col - 1;
        while (m[lig][j] == ca)
        {
            m[lig][j] = cj;
            j--;
        }
    }

    /* Horizontal vers la droite */
    j = col + 1;
    while (case_existe(lig, j) && m[lig][j] == ca)
        j++;
    if (case_existe(lig, j) && m[lig][j] == cj)
    {
        j = col + 1;
        while (m[lig][j] == ca)
        {
            m[lig][j] = cj;
            j++;
        }
    }

    /* Diagonal \ vers le haut */
    i = lig - 1;
    j = col - 1;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i--;
        j--;
    }
    if (case_existe(i, j) && m[i][j] == cj)
    {
        i = lig - 1;
        j = col - 1;
        while (m[i][j] == ca)
        {
            m[i][j] = cj;
            i--;
            j--;
        }
    }

    /* Diagonal \ vers le bas */
    i = lig + 1;
    j = col + 1;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i++;
        j++;
    }
    if (case_existe(i, j) && m[i][j] == cj)
    {
        i = lig + 1;
        j = col + 1;
        while (m[i][j] == ca)
        {
            m[i][j] = cj;
            i++;
            j++;
        }
    }

    /* Diagonal / vers le haut */
    i = lig - 1;
    j = col + 1;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i--;
        j++;
    }
    if (case_existe(i, j) && m[i][j] == cj)
    {
        i = lig - 1;
        j = col + 1;
        while (m[i][j] == ca)
        {
            m[i][j] = cj;
            i--;
            j++;
        }
    }

    /* Diagonal \ vers le bas */
    i = lig + 1;
    j = col - 1;
    while (case_existe(i, j) && m[i][j] == ca)
    {
        i++;
        j--;
    }
    if (case_existe(i, j) && m[i][j] == cj)
    {
        i = lig + 1;
        j = col - 1;
        while (m[i][j] == ca)
        {
            m[i][j] = cj;
            i++;
            j--;
        }
    }
}

/*Calcule de score*/
int p_score(t_matrice m, int s)
{
    int score = 0;
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (m[i][j] == s)
                score++;
        }
    }
    return score;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//************************************** Game Chargement */**********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void playgame_charge(char l[130])
{

    t_matrice m;
    int lig, col, joueur = 1, X;
    int j = 1, i = 0;
    int cp = 0;
    /* Initialisation du jeu */
    int k = 1;
    init_matrice(m);
    afficher_matrice(m);
    /* Deroulement d'une partie */
    while (k <= strlen(l) / 2)
    {
        lig = atoi(&l[j]) - 1;
        col = l[i] - 'A';
        jouer_coup(m, lig, col, joueur);
        afficher_matrice(m);
        joueur = joueur_suivant(joueur);
        X = peut_jouer(m, joueur);
        if (X == 0)
            joueur = joueur_suivant(joueur);
        printf("\t\t\t\t\t\t\t\t Score du joueur 1: %d\n", p_score(m, NOIR));
        printf("\t\t\t\t\t\t\t\t Score du joueur 2: %d\n", p_score(m, BLANC));
        j = j + 2;
        i = i + 2;
        k++;
    };
    printf("Press a key to exit ......\n");
    getchar();
}

// Le deroule�ent d'une partie de debut jusqau'a la fin
void playgame()
{

    int i, numero_partie;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *h = fopen("numeropartie.txt", "a");
    fclose(h);
    h = fopen("numeropartie.txt", "r+");
    if (NULL != h)
    {
        int size;
        fseek(h, 0, SEEK_END);
        size = ftell(h);
        fseek(h, 0, SEEK_SET);
        if (size == 0)
        {
            fprintf(h, "1_");
            numero_partie = 1;
        }

        else
        {

            fseek(h, 0, SEEK_SET);
            char var = fgetc(h);
            int temp = 0;
            fseek(h, 0, SEEK_SET);
            while (var != EOF)
            {
                fscanf(h, "%d", &numero_partie);

                var = fgetc(h);
                if (var == EOF)
                    temp = numero_partie;
            }
            numero_partie = temp + 1;

            fprintf(h, "%d_", numero_partie);
        }
    }
    fclose(h);

    // Demande des infos des joueurs
    char player1[20], player2[20];
    printf("Donner le nom du premier joueur: ");
    scanf("%s", player1);
    printf("Donner le nom du deuxieme joueur: ");
    scanf("%s", player2);

    /////////// Creation d'un fichier "DETAIL"  pour les details des coups (  avec la lettre demander entre chaque deux tours �
    ///////////  pour simplifier l'appel des coups en un seul clique.
    FILE *fp;
    fp = fopen("DETAIL.txt", "a");
    fprintf(fp, "\nPartie %d :\n", numero_partie);
    fclose(fp);

    ////////// Creation d'un fichier "les coups des parties "  qui contient les coups successivement de la partie.
    FILE *flot;
    flot = fopen("les coups des parties.txt", "a");
    fprintf(flot, "\nPartie %d \n", numero_partie);
    fclose(flot);

    ////////// Creation du fichier "info de joueur"  pour stocker les scores et leurs prenoms.
    FILE *f;
    f = fopen("Info de joueur.txt", "a");
    fprintf(f, "\n\nPartie %d %d-%02d-%02d %02d:%02d:%02d.", numero_partie, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(f);
    t_matrice m;
    int lig, col, joueur = 1;

    /* Initialisation du jeu */
    init_matrice(m);
    int etat_partie = partie_terminee(m);
    char c;
    afficher_matrice(m);

    /* Deroulement d'une partie */
    while (!etat_partie)
    {
        choisir_coup(m, &lig, &col, joueur);
        jouer_coup(m, lig, col, joueur);
        afficher_matrice(m);
        if (peut_jouer(m, joueur_suivant(joueur)))
            joueur = joueur_suivant(joueur);
        else
            printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player1, p_score(m, NOIR));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player2, p_score(m, BLANC));
        printf("Voulez vous recommencer? (o ou n)? ");
        scanf("%s", &c);
        fp = fopen("DETAIL.txt", "a");
        fprintf(fp, "%c ", c);
        fclose(fp);
        etat_partie = partie_terminee(m);
        if (c == 'o')
        {
            etat_partie = 1;
        };
    };
    /////// Ecriture des resultas dans les fichiers ( chaque fichier avec ces informations )
    flot = fopen("les coups des parties.txt", "a");
    f = fopen("Info de joueur.txt", "a");
    fprintf(flot, "\n");
    fprintf(f, "\n%s: %d", player1, p_score(m, NOIR));
    fprintf(f, "\n%s: %d", player2, p_score(m, BLANC));
    fclose(flot);
    fclose(f);
    FILE *g = fopen("Les scores.txt", "a");
    if (p_score(m, NOIR) >= p_score(m, BLANC))
        fprintf(g, "\n%s: %d", player1, p_score(m, NOIR));
    else
        fprintf(g, "\n%s: %d", player2, p_score(m, BLANC));
    fclose(g);
    if (c == 'o')
    {
        printf("\n\n\n\n\n\n\n\n Une nouvelle partie a commencee ! \n\n");
        playgame();
    }
}
