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

///////// Une structure qui contient les deux composantes d'un coup
typedef struct Coups_
{
    int ligne;
    int colonne;
} C_CPU;

/////////////// fonction qui renvoit  les coups legales du CPU
C_CPU *legal_coups(int joueur, t_matrice m)
{
    C_CPU *moves;
    moves = (C_CPU *)malloc(65 * sizeof(C_CPU));
    int lig, i = 0;
    int col;
    moves[0].ligne = 0;
    moves[0].colonne = 0;
    for (lig = 0; lig <= 7; lig++)
    {
        for (col = 0; col <= 7; col++)
        {

            if (coup_valide(m, lig, col, joueur))
            {
                i++;
                moves[i].ligne = lig;
                moves[i].colonne = col;
            }
        }
    }

    moves[0].ligne = i;
    moves[0].colonne = i;

    return moves;
}

////////// Deroule�ent d'un jeu contre CPU avec des coups aleatoires.
void playgame_EASY()
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

    /////////// Demande des infos des joueurs
    char player1[20], player2[20];
    printf("Donner le nom du premier joueur: ");
    scanf("%s", player1);
    strcpy(player2, "CPU");

    /////////Ouvrir le fichier des infos et l'ecriture de la date et l'heure  courante et le num de la partie.
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
    C_CPU *coup_CPU; // coup valide de CPU
    int rnd;
    afficher_matrice(m);
    /* Deroulement d'une partie */

    while (!etat_partie)
    {
        if (joueur == 1)
        {
            choisir_coup_CPU(m, &lig, &col, joueur);
            jouer_coup(m, lig, col, joueur);
            afficher_matrice(m);
        }
        else
        {
            coup_CPU = legal_coups(2, m);
            jouer_coup(m, coup_CPU[1].ligne, coup_CPU[1].colonne, 2);
            afficher_matrice(m);
            printf("Voulez vous recommencer? (o ou n)? ");
            scanf("%s", &c);
        }

        if (peut_jouer(m, joueur_suivant(joueur)))
            joueur = joueur_suivant(joueur);
        else
            printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player1, p_score(m, NOIR));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player2, p_score(m, BLANC));
        etat_partie = partie_terminee(m);
        if (c == 'o')
        {
            etat_partie = 1;
        };
    };

    /////// L'ecriture des donnees demander par chaque fichier.
    f = fopen("Info de joueur.txt", "a");

    fprintf(f, "\n%s: %d", player1, p_score(m, NOIR));
    fprintf(f, "\n%s: %d", player2, p_score(m, BLANC));

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
        playgame_EASY();
    }
}
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////// **** FONCTION PLAYGAME_RND **** /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//  Jouer une partie contre CPU avec rand() //
void playgame_RND()
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
    strcpy(player2, "CPU");
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
    C_CPU *coup_CPU; // coup valide de CPU
    int rnd;
    afficher_matrice(m);
    /* Deroulement d'une partie */

    while (!etat_partie)
    {
        if (joueur == 1)
        {
            choisir_coup_CPU(m, &lig, &col, joueur);
            jouer_coup(m, lig, col, joueur);
            afficher_matrice(m);
        }
        else
        {
            coup_CPU = legal_coups(2, m);
            //generation d'un coup aleatoire parmi la liste coup_CPU :
            rnd = (rand() % coup_CPU[0].ligne) + 1;
            jouer_coup(m, coup_CPU[rnd].ligne, coup_CPU[rnd].colonne, 2);
            afficher_matrice(m);
            printf("Voulez vous recommencer? (o ou n)? ");
            scanf("%s", &c);
        }

        if (peut_jouer(m, joueur_suivant(joueur)))
            joueur = joueur_suivant(joueur);
        else
            printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player1, p_score(m, NOIR));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player2, p_score(m, BLANC));

        etat_partie = partie_terminee(m);
        if (c == 'o')
        {
            etat_partie = 1;
        };
    };

    f = fopen("Info de joueur.txt", "a");

    fprintf(f, "\n%s: %d", player1, p_score(m, NOIR));
    fprintf(f, "\n%s: %d", player2, p_score(m, BLANC));

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
        playgame_RND();
    }
}

////////////////////////////////////////////////////////////////////////
////////////////////////Algorithm de MINMAX/////////////////////////////
////////////////////////////////////////////////////////////////////////

// fonction qui permet de creer une copie de la grille actuelle :
void copier_table(t_matrice *m, t_matrice *temp)
{

    int i = 0, j = 0;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            strcpy(temp[i][j], m[i][j]);
        }
    }
}

//////////////////////// Fonction d'evaluation de l'algorithme minmax.
int diffeval(t_matrice m, int joueur)
{
    int oppenent = 1;
    if (joueur == 1)
    {
        oppenent = joueur_suivant(joueur);
    }
    int ourscore = p_score(m, NOIR);
    int oppenentscore = p_score(m, BLANC);
    return (ourscore - oppenentscore);
}

//////////////////////// Fonction minmax de decision
void minmaxDecision(t_matrice m, int joueur, int *lig, int *col)
{

    C_CPU *mo_ve;
    int i;
    int oppenent = 1;
    if (joueur == 1)
    {
        oppenent = joueur_suivant(joueur);
    }

    mo_ve = legal_coups(joueur, m);
    if (mo_ve[0].ligne == 0)
    {

        lig = -1;
        col = -1;
    }
    else
    {

        int bestMoveVal = -99999;

        int BestLig = mo_ve[1].ligne, BestCol = mo_ve[1].colonne;

        for (i = 1; i < mo_ve[0].ligne; i++)
        {

            t_matrice temp_table[8][8];

            copier_table(m, temp_table);

            jouer_coup(temp_table, mo_ve[i].ligne, mo_ve[i].colonne, joueur);

            // Avoir la valeur minmax de l'adversaire.
            int val = minmaxValue(temp_table, joueur, oppenent, 1);
            // Se rappeler du coup meilleur
            if (val > bestMoveVal)
            {
                bestMoveVal = val;
                BestLig = mo_ve[i].ligne;
                BestCol = mo_ve[i].colonne;
            }
        }

        jouer_coup(m, BestLig, BestCol, 2);

        afficher_matrice(m);
    };
}

int partie_terminee_AI(t_matrice m)
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
    return 1;
}

//////////////////////////// Fonction minmax value( les meilleurs coups)
int minmaxValue(t_matrice m, int joueur, int curr_joueur, int profondeur)
{
    if ((profondeur == 5) || partie_terminee_AI(m))
    {
        return diffeval(m, joueur);
    }
    C_CPU *mo_ve;
    int oppenent = 1;
    if (curr_joueur == 1)
    {
        oppenent = joueur_suivant(joueur);
    }
    mo_ve = legal_coups(curr_joueur, m);
    if (mo_ve[0].ligne == 0)
    {
        return minmaxValue(m, joueur, oppenent, profondeur + 1);
    }
    else
    {
        // Best move
        int bestMoveVal = -99999;
        int i;
        if (joueur != curr_joueur)
        {
            bestMoveVal = 99999;
        }

        for (i = 1; i < mo_ve[0].ligne; i++)
        {
            // Teste de tous les mouvement possible
            t_matrice temp_table[N][N];
            copier_table(m, temp_table);
            jouer_coup(temp_table, mo_ve[i].ligne, mo_ve[i].colonne, curr_joueur);
            // Avoir la valeur minmax de l'adversaire.
            int val = minmaxValue(temp_table, joueur, oppenent, profondeur + 1);
            // Se rappeler du mouvement meilleur
            if (joueur == curr_joueur)
            {
                // se rappeler du max
                if (val > bestMoveVal)
                {
                    bestMoveVal = val;
                }
            }
            else
            {
                // se rappeler du min
                if (val < bestMoveVal)
                {
                    bestMoveVal = val;
                }
            }
        }
        return bestMoveVal;
    }
    return -1;
}

void playgame_AI()
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
    strcpy(player2, "SMART CPU");

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
    C_CPU *coup_CPU;
    // coup valide de CPU

    afficher_matrice(m);
    /* Deroulement d'une partie */

    while (!etat_partie)
    {
        if (joueur == 1)
        {
            choisir_coup_CPU(m, &lig, &col, joueur);
            jouer_coup(m, lig, col, joueur);
            afficher_matrice(m);
        }
        else
        {
            minmaxDecision(m, joueur, lig, col);
            printf("Voulez vous recommencer? (o ou n)? ");
            scanf("%s", &c);
        }

        if (peut_jouer(m, joueur_suivant(joueur)))
        {

            joueur = joueur_suivant(joueur);
        }

        else
            printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player1, p_score(m, NOIR));
        printf("\t\t\t\t\t\t\t\t Score du %s: %d\n", player2, p_score(m, BLANC));

        etat_partie = partie_terminee(m);
        if (c == 'o')
        {
            etat_partie = 1;
        };
    };

    f = fopen("Info de joueur.txt", "a");

    fprintf(f, "\n%s: %d", player1, p_score(m, NOIR));
    fprintf(f, "\n%s: %d", player2, p_score(m, BLANC));

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
        playgame_AI();
    }
}
