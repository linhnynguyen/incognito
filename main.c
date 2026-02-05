#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define TAILLE 5
#define N  ((TAILLE - 1) * (TAILLE - 2) / 2 - 1)
#define taille_case 100

typedef enum _couleur {
    BLANC, 
    NOIR
    } Couleur;


typedef enum _type{
    CHEVALIER, 
    ESPION
    } Type; 


typedef struct _pion {
    Type type ;
    Couleur couleur ;
} Pion ;


typedef struct {
    int x , y ;
} Case , Direction; 


typedef struct _jeu {
    Pion *plateau [ TAILLE ] [ TAILLE ] ;
    Couleur joueur ;
} Jeu ;


typedef struct _mouvement {
    Case depart;
    Case arrivee;
} Mouvement;




void implement_grid(Pion *grid[TAILLE][TAILLE],  Case espion_w, Case espion_b){
    /*
        Initialise la grille de départ avec les pièces de chaque équipe

        Paramètres : 
            une matrice de Pion, 
            les coordonnées de l'espion blanc, 
            les coordonnées de l'espion noir

        Retour :
            void
    */
    int i = 0, j = 0;
    // taille_temp est le nombre de lignes nécessaires pour remplir N+1 valeurs
    int taille_temp = TAILLE - (-1 + sqrt(1+ 8 * (N+1))) / 2;
    // parcourt la grille pour placer les pièces
    for(i = 0; i < TAILLE; i++){
        for(j = 0; j < TAILLE; j++){
            // initialise l'espion et les chevaliers du joueur blanc
            if(i <= taille_temp && j >= taille_temp + i && j - i < TAILLE - 1){
                // vérifie si la case actuelle est un espion
                if(espion_b.x == i && espion_b.y == j){
                    Pion p1 = {ESPION, NOIR};
                    grid[i][j] = malloc(sizeof(Pion));
                    *grid[i][j] = p1;
                    // ajouter les coordonnées au fichier
                    // fprintf(incognito, "B %c%d\n", table_charac[j], i + 1);
                
                }
                // la case est un chevalier
                else{
                    Pion p1 = {CHEVALIER, NOIR};
                    grid[i][j] = malloc(sizeof(Pion));

                    *grid[i][j] = p1;
                }

            }else
                // initialise l'espion et les chevaliers du joueur noir
                if(i >= taille_temp && i - j >= taille_temp && i - j < TAILLE - 1){
                    if(espion_w.x == i && espion_w.y == j){
                        Pion p1 = {ESPION, BLANC};
                        grid[i][j] = malloc(sizeof(Pion));
                        *grid[i][j] = p1;
                        // ajouter les coordonnées au fichier
                        // fprintf(incognito, "N %c%d\n", table_charac[j], i+1);
                    }
                // la case est un chevalier
                    else{
                        Pion p1 = {CHEVALIER, BLANC};
                        grid[i][j] = malloc(sizeof(Pion));
                        *grid[i][j] = p1;
                    }
                }
                // la case est vide (NULL)
                else{
                    grid[i][j] = NULL;
                }

        }
    }

}



void draw_filled_circle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    /*
        Dessine un cercle plein sur la fenêtre SDL

        Paramètres : 
            SDL_Renderer,
            coordonnée x du centre,
            coordonnée y du centre,
            rayon du cercle

        Retour : 
            void
    */
    for (int y = -radius; y <= radius; y++) {
        // calcul de dx
        int dx = (int)sqrt(radius * radius - y * y);
        SDL_RenderDrawLine(renderer, centerX - dx, centerY + y, centerX + dx, centerY + y);
    }
}

void display_grid_graph(Pion *grid[TAILLE][TAILLE], SDL_Renderer *renderer) {
    /*
        Affiche la grille et les pièces sur la fenêtre SDL

        Paramètres : 
            une matrice de Pion et SDL_Renderer

        Retour : 
            void
    */
    
    SDL_Surface *castle = SDL_LoadBMP("DM/castle.bmp"); // Charge l'image
    if (!castle) {
        printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, castle);
    SDL_FreeSurface(castle);  // Libère la surface après la création de la texture

    if (!texture) {
        printf("Échec de la création de la texture à partir de la surface : %s\n", SDL_GetError());
        return;
    }

    SDL_Rect rect_castle1 = { taille_case * (TAILLE - 1), 0, taille_case, taille_case };
    SDL_Rect rect_castle2 = { 0, taille_case * (TAILLE - 1), taille_case, taille_case };
    SDL_SetRenderDrawColor(renderer, 0, 165, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int i = 0; i < TAILLE; i++) {
        // Dessine les lignes de la grille
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, i * taille_case, TAILLE * taille_case, i * taille_case);
        SDL_RenderDrawLine(renderer, i * taille_case, 0, i * taille_case, TAILLE * taille_case);

        for (int j = 0; j < TAILLE; j++) {
            // Dessine les pièces
            if (grid[i][j]) {
                if (grid[i][j]->couleur == BLANC) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                } else if (grid[i][j]->couleur == NOIR) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                }
                draw_filled_circle(renderer, j * taille_case + taille_case / 2, i * taille_case + taille_case / 2, taille_case / 2);
            }
        }
    }

    SDL_RenderCopy(renderer, texture, NULL, &rect_castle1);  // Dessine la texture
    SDL_RenderCopy(renderer, texture, NULL, &rect_castle2);  // Dessine la texture
    SDL_RenderPresent(renderer);  // Affiche le tout sur l'écran

    SDL_DestroyTexture(texture);  // Libère la texture à la fin
}




void display_grid(Pion *grid[TAILLE][TAILLE]){
    /*
        Affiche la grille dans le terminal

        Paramètres : 
            une matrice de Pion

        Retour : 
            void
    */
    int i, j;
    for(i = 0; i < TAILLE; i++){
        printf("---------------------------------------------------------------------\n");
        for(j = 0; j < TAILLE; j++){
            if(grid[i][j] && grid[i][j]->couleur == BLANC){
                printf("   |b|   ");
            }
            else if(grid[i][j] && grid[i][j]->couleur == NOIR){
                printf("   |n|   ");
            }else{
                printf("   | |   ");
            }
        }
        printf("\n");
    }
    printf("---------------------------------------------------------------------\n");
}



int move_piece(Pion *grid[TAILLE][TAILLE], Mouvement move, Couleur player){
    /*
        Déplace une pièce d'une case à une autre

        Paramètres : 
            une matrice de Pion,
            un Mouvement, 
            le joueur actuel

        Retour :
            0 : quand le mouvement est réussi
            1 : quand des pions bloquent le passage
            2 : quand le joueur essaie de déplacer un pion vers son propre château
            3 : quand le joueur essaie de déplacer une pièce qui ne lui appartient pas
            4 : quand le joueur essaie de déplacer une case vide
            -1 : quand le mouvement n'est pas autorisé
    */
    int i = 0, can_move=-1;
    int step_x, step_y;
    // vérifie si la case sélectionnée est valide
    if(grid[move.depart.x][move.depart.y] == NULL) return 4;
    // vérifie qu'on ne tente pas d'aller dans son propre château
    if((player == 1 && move.arrivee.x == 0 && move.arrivee.y == TAILLE - 1) || (player == 0 && move.arrivee.x == TAILLE - 1 && move.arrivee.y == 0)) return 2;
    // vérifie si la case sélectionnée appartient au joueur
    if(grid[move.depart.x][move.depart.y]->couleur == player){
        if(move.depart.x >= move.arrivee.x){
            step_x = -1;
        }else{
            step_x = 1;
        }
        if(move.depart.y >= move.arrivee.y){
            step_y = -1;
        }else{
            step_y = 1;
        }
        // signifie que les deux points sont sur la même ligne
        if(move.depart.x == move.arrivee.x){
            for(i = 1; i <= abs(move.depart.y - move.arrivee.y); i++){
                    if(grid[move.depart.x][move.depart.y + i*step_y] != NULL){
                            return 1;
                        }
            }
            can_move = 0;
                // signifie que les deux points sont sur la même colonne
        }else if(move.depart.y == move.arrivee.y){
                for(i = 1; i <= abs(move.depart.x - move.arrivee.x); i++){
                    if(grid[move.depart.x + i * step_x][move.depart.y] != NULL){
                            return 1;
                        }
                }
                can_move = 0;
                // signifie que les deux points forment une diagonale
            }else if(abs(move.depart.x - move.arrivee.x) == abs(move.depart.y - move.arrivee.y)){
                for(i = 1; i <= abs(move.depart.x - move.arrivee.x); i++){
                    if(grid[move.depart.x + i * step_x][move.depart.y + i*step_y] != NULL){
                            return 1;
                        }
                    }
                
                can_move = 0;
                }
            if(grid[move.depart.x][move.depart.y] != NULL && can_move == 0){
                return 0;
            }else{
                return -1;
            }

    }
    else{
        return 3;
    }
}




int interrogate_piece(Pion *grid[TAILLE][TAILLE], Couleur player, Case interrogator, Direction questioned){
    /*
        Interroge une pièce

        Paramètres : 
            une matrice de Pion (la grille),
            le joueur actuel, 
            les coordonnées de l'interrogateur, 
            la direction de la pièce interrogée

        Retour :
            0 : quand le joueur actuel (chevalier) interroge un autre chevalier
            1 : quand les deux cases ne sont pas adjacentes
            -1 : quand le joueur actuel interroge un espion
            -2 : quand le joueur actuel interroge un chevalier avec son espion
            3 : quand ce n'est pas le bon joueur
            4 : quand les deux cases ne sont pas valides
    */

    // vérifie si les cases sélectionnées sont valides
    if(grid[interrogator.x][interrogator.y] != NULL && grid[questioned.x][questioned.y] != NULL){
        // vérifie si les cases sélectionnées sont adjacentes
        if((abs(interrogator.x - questioned.x) == 1 && interrogator.y == questioned.y) || (abs(interrogator.y - questioned.y) == 1 && interrogator.x == questioned.x)){
            // vérifie si le joueur a choisi le bon pion pour interroger
            if(grid[interrogator.x][interrogator.y]->couleur == player && grid[questioned.x][questioned.y]->couleur != player){
                // vérifie si le pion ennemi est un chevalier ou un espion
                // CHEVALIER VS CHEVALIER
                if(grid[questioned.x][questioned.y]->type == CHEVALIER && grid[interrogator.x][interrogator.y]->type == CHEVALIER){
                    grid[interrogator.x][interrogator.y] = NULL;
                    return 0;
                }
                // CHEVALIER OU ESPION VS ESPION
                else if(grid[questioned.x][questioned.y]->type == ESPION){
                    grid[questioned.x][questioned.y] = NULL;
                    // à modifier
                    // gagnant
                    return -1;

                }
                // ESPION VS CHEVALIER
                else if(grid[questioned.x][questioned.y]->type == CHEVALIER && grid[interrogator.x][interrogator.y]->type == ESPION){
                    // gagnant
                    grid[interrogator.x][interrogator.y] = NULL;
                    return -2;
                }
            }else{
                // ce n'est pas le bon joueur
                return 3;
            }
        }else{
            // les cases sélectionnées ne sont pas adjacentes
            return 1;
        }
    }else{
        // les cases sélectionnées ne sont pas valides
        return 4;
    }
    // retour par défaut pour éviter les avertissements
    return 0;
}




int decide_in_castle(Pion *grid[TAILLE][TAILLE] , Mouvement move, Couleur player){
    /*
        Vérifie si un joueur tente de déplacer une pièce vers un château

        Paramètres : 
            une matrice de Pion (la grille),
            le joueur actuel, 
            les coordonnées du mouvement

        Retour :
            0 : quand le joueur tente de déplacer une pièce vers un château de manière orthogonale ou quand le pion ne va pas vers un château
            1 : quand le joueur tente de déplacer une pièce vers un château mais pas de manière orthogonale
    */
    // vérifie le joueur qui joue
    if(player == 1){
        // vérifie si la case d'arrivée est le château
        if(move.arrivee.x == TAILLE - 1 && move.arrivee.y == 0){
            // vérifie si l'accès se fait de manière orthogonale
            if(move.depart.x == move.arrivee.x || move.depart.y == move.arrivee.y){
                return 0;
            }
            return 1;

        }
    }
    else if(player == 0){
        // vérifie si la case d'arrivée est le château
        if(move.arrivee.x == 0 && move.arrivee.y == TAILLE - 1){
            // vérifie si l'accès se fait de manière orthogonale
            if(move.depart.x == move.arrivee.x || move.depart.y == move.arrivee.y){
                return 0;
            }
            return 1;

        }

    }
    return 0;
}


int is_win(Pion *grid[TAILLE][TAILLE], Mouvement move, Couleur player){
    /*
        Vérifie si un joueur a gagné la partie

        Paramètres : 
            une matrice de Pion (la grille),
            le joueur actuel, 
            les coordonnées du mouvement

        Retour :
            0 : le joueur est entré dans un château avec un espion
            1 : le joueur vient de faire un mouvement normal (pas d'entrée dans un château)
            2 : le joueur a déplacé un chevalier vers un château
    */
    if (player == 0){
        if(move.arrivee.x == 0 && move.arrivee.y == TAILLE - 1){
            // vérifie si la pièce est un espion
            if(grid[move.depart.x][move.depart.y]->type == ESPION) return 0;
            return 2;
        }
    }else{
        if(move.arrivee.x == TAILLE - 1 && move.arrivee.y == 0){
            // vérifie si la pièce est un espion
            if(grid[move.depart.x][move.depart.y]->type == ESPION) return 0;
            return 2;
        }
    }
    return 1;
}



void fill_table(char table_charac[TAILLE]){
    /*
        Remplit un tableau de lettres de 'a' à (a + TAILLE - 1)

        Paramètres :
            un tableau de caractères (sa taille est égale à TAILLE)

        Retour :
            void
    */
    for(int i = 0; i < TAILLE ; i++){
        table_charac[i] = (char)(i + 97);
    }
}

int search_in_table_char(char table_char[TAILLE], char c){
    /*
        Retourne l'indice d'une lettre donnée par la variable c dans le tableau de lettres

        Paramètres : 
            tableau de lettres, 
            une lettre

        Retour :
            l'indice de la lettre dans le tableau
    */
    for(int i = 0; i< TAILLE; i++){
        if(table_char[i] == c){
            return i;
        }
    }
    return 1;
}

void update_player(char *p, Couleur player){
    /*
        Donne la lettre correspondant au joueur

        Paramètres : 
            un pointeur vers un caractère, 
            le joueur actuel

        Retour :
            void
    */
    if(player == 0){
        *p = 'B';
    }else{
        *p = 'N';
    }
}



void read_file(FILE *incognito, Jeu *game, char table_char[TAILLE]){
    /*
        Lit un fichier (progression du jeu) et exécute les mouvements indiqués dans le fichier

        Paramètres : 
            un FICHIER, 
            un Jeu, 
            un tableau de lettres

        Retour :
            void
    */

    // déclare une variable joueur qui est un caractère du FICHIER, choix : 'D' || 'I', c1, c2 caractères temporaires
    char player, choice, c1, c2;
    // déclare une variable gamer dont la valeur est la couleur du joueur sous forme de chaîne
    char gamer[10];
    // déclare une variable indiquant si on est dans un château, et une autre pour les erreurs de mouvement
    int move_castle, error;
    // déclare un mouvement
    Mouvement move;
    // récupère le premier joueur depuis le FICHIER
    fscanf(incognito, "%c\n", &player);
    if(player ==  'B'){
        game->joueur = BLANC;
    }else{
        game->joueur = NOIR;
    }

    if(game->joueur == 0) strcpy(gamer, "White");
    else strcpy(gamer, "Black");

    // boucle qui s'arrête à la fin du FICHIER
    while (fscanf(incognito, "%c %c%d->%c%d\n", &choice, &c1, &move.depart.x, &c2, &move.arrivee.x) != EOF)
    {
        // move.depart.x est la ligne de départ, on fait -1 car l'affichage commence à 1
        move.depart.x --;
        // move.arrivee.x est la ligne d'arrivée, on fait -1 car l'affichage commence à 1
        move.arrivee.x --;
        // convertit la lettre de la colonne en nombre
        move.depart.y = search_in_table_char(table_char, c1);
        move.arrivee.y = search_in_table_char(table_char, c2);
        // si le choix est un déplacement
        if(choice == 'D'){        
            // vérifie si on est à l'intérieur d'un château
            move_castle = decide_in_castle(game->plateau, move, game->joueur);
                // on n'est pas dans un château
                if(move_castle == 0){
                    // tente de déplacer une pièce
                    error = move_piece(game->plateau, move, game->joueur);
                    switch (error)
                    {
                    // succès
                    case 0:
                    // vérifie la victoire
                        move_castle = is_win(game->plateau, move, game->joueur);
                        // victoire
                        if(move_castle == 0){
                            printf("Bravo, le gagnant est : %s\n", gamer);
                            fclose(incognito);
                        // le pion était un chevalier
                        }else if(move_castle == 2){
                            printf("Le pion interrogé n'est pas l'espion, votre propre pion a été empoisonné...\n");
                            game->plateau[move.depart.x][move.depart.y] = NULL;
                        }
                        // exécute le mouvement en changeant les coordonnées
                        game->plateau[move.arrivee.x][move.arrivee.y] = game->plateau[move.depart.x][move.depart.y];
                        game->plateau[move.depart.x][move.depart.y] = NULL;
                        printf("Joueur %s, votre mouvement est exécuté..\n", gamer);
                        break;
                    case 1:
                        printf("Mouvement illégal : des cases bloquent le passage.\n");
                        break;
                    case 2:
                        printf("Mouvement illégal : un joueur ne peut pas amener un pion dans son propre château.\n");
                        break;
                    case 3:
                        printf("Mouvement illégal : le pion sélectionné ne vous appartient pas.\n");
                        break;
                    case 4:
                        printf("Mouvement illégal : la case est vide\n");
                        break;
                    default:
                        printf("Ce mouvement n'est pas autorisé.\n");
                        break;
                    }
                }
                else{
                    printf("Ce mouvement n'est pas autorisé\n");
                    error = 1;
                }
        }
        // si le choix est une Interrogation
        else if(choice == 'I'){
                // effectue une interrogation
                error = interrogate_piece(game->plateau, game->joueur, move.depart, move.arrivee);
                // affiche un message selon le résultat
                switch (error)
                {
                    // interrogation réussie (chevalier vs chevalier)
                case 0:
                    printf("Joueur %s, vous n'avez pas trouvé l'espion adverse...\nEt en plus, votre chevalier a été empoisonné... \n", gamer);
                    break;
                case 1:
                    printf("Interrogation non autorisée car les cases ne sont pas adjacentes.\n");
                    break;
                // espion interrogé -> victoire
                case -1:
                    printf("Joueur %s, vous avez interrogé un espion...\n", gamer);
                    printf("Bravo, le gagnant est : %s\n", gamer);
                    fclose(incognito);
                    break;
                // interrogation d'un chevalier avec son propre espion -> défaite
                case -2:
                    printf("Joueur %s, vous avez interrogé un chevalier avec votre espion...\n", gamer);
                    printf("Bravo, le gagnant est : %s\n", (game->joueur == 0)?"Black": "White");
                    fclose(incognito);
                    break;
                case 3:
                    printf("Interrogation non autorisée : le joueur a sélectionné le mauvais pion.\n");
                    break;
                case 4:
                    printf("Interrogation non autorisée car les deux cases sont vides.\n");
                    break;
                default:
                    printf("Le mouvement n'est pas autorisé.\n");
                    break;
                }
            }
            // si le mouvement est valide, on passe le tour à l'autre joueur
            if(error == 0){
                game->joueur = (game->joueur + 1)%2;
                if(game->joueur ==  0){
                    strcpy(gamer, "White");
                }else{
                    strcpy(gamer, "Black");
                
            }   
            }

    }
}   

int main(int argc, char **argv){
    // déclare les variables pour le terminal
    // le fichier qu'on va écrire
    FILE *incoginito_write  = NULL;
    // le fichier qu'on va lire
    FILE *incoginito_read = NULL;
    // variable pour l'affichage graphique
    int *graphic_display = NULL;
    // variable pour l'affichage ascii
    int *ascii_display = NULL;
    // déclare la fenêtre et le rendu
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    // vérifie les arguments saisis dans le terminal
    for(int i = 0; i < argc; i++){
        // cas de l'affichage ascii
        if(strcmp(argv[i], "-a") == 0){ 
            ascii_display = malloc(sizeof(int));
            *ascii_display = 1;

        // cas de l'affichage graphique
        }else if(strcmp(argv[i], "-g") == 0){
            graphic_display = malloc(sizeof(int));
            *graphic_display = 1;
            // initialise SDL vidéo
            SDL_Init(SDL_INIT_VIDEO);
            // crée la fenêtre
            window = SDL_CreateWindow("INCOGNITO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE * taille_case, TAILLE * taille_case, 0);
            // crée le rendu
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

            // cas de sauvegarde de fichier
        }else if(strcmp(argv[i], "-s") == 0){
            incoginito_write = fopen(*(argv + i + 1), "w");
            // cas de chargement de fichier
        }else if(strcmp(argv[i], "-c") == 0){
            incoginito_read = fopen(*(argv + i + 1), "r");
        }
    }
    // l'affichage par défaut est ascii
    if(graphic_display == NULL && ascii_display == NULL){
        ascii_display = malloc(sizeof(int));
            *ascii_display = 1;
    }
    // vérifie si on doit à la fois lire et sauvegarder les mouvements
    // copie le contenu du premier fichier dans le second
    if(incoginito_read != NULL && incoginito_write != NULL){
        char choice, p, c;
        int a, b, n;
        fscanf(incoginito_read, "%c %c%d\n", &p, &c, &n);
        fprintf(incoginito_write, "%c %c%d\n", p, c, n);
        fscanf(incoginito_read, "%c %c%d\n", &p, &c, &n);
        fprintf(incoginito_write, "%c %c%d\n", p, c, n);
        fscanf(incoginito_read, "%c\n", &p);
        fprintf(incoginito_write, "%c\n", p);
        while (fscanf(incoginito_read, "%c %c%d->%c%d\n", &choice, &c, &a, &p, &b) != EOF){
            fprintf(incoginito_write, "%c %c%d->%c%d\n", choice, c, a, p, b);
        }
        rewind(incoginito_read);

    }
    // crée la variable de jeu
    Jeu game = {};
    // crée la variable de mouvement
    Mouvement move;
    // variables pour gérer la fin de partie, les erreurs de mouvement et les châteaux
    int game_on = 1, error, move_castle;
    // nombres aléatoires pour définir la position des espions
    srand(time(NULL));
    int sb = rand() % N;
    int sw = rand() % N;
    // déclare une variable joueur
    char player[10];
    // déclare une variable joueur pour le fichier
    char p, choice, c;
    // tableau de caractères pour l'indice des colonnes
    char table_charac[TAILLE];
    
    // remplit le tableau avec des lettres
    fill_table(table_charac);
    int taille_temp = TAILLE - (-1 + sqrt(1+ 8 * (N+1))) / 2;
    // déclare les deux espions
    Case spy_black, spy_white;
    // transforme les entiers aléatoires en coordonnées
    if(incoginito_read == NULL){
        for(int i = 0; i < TAILLE; i++){
            for(int j = 0; j < TAILLE; j++){
                // accède à la partie supérieure de la grille (joueur noir)
                if(i <= taille_temp && j >=  taille_temp + i && j - i < TAILLE - 1){
                    if(sb == 0){
                        spy_black.x = i;
                        spy_black.y = j;
                        c = table_charac[j];
                        if(incoginito_write != NULL)
                            fprintf(incoginito_write, "N %c%d\n", c, i+1);
                        sb--;
                    }else{
                        sb--;
                    }
                }  
                // accède à la partie inférieure de la grille (joueur blanc)
                if(i >= taille_temp && i - j >= taille_temp && i - j < TAILLE - 1){
                    if(sw == 0){
                        spy_white.x = i;
                        spy_white.y = j;
                        c = table_charac[j];
                        if(incoginito_write != NULL)
                            fprintf(incoginito_write, "B %c%d\n", c, i+1);
                        sw--;
                    }else{
                        sw--;  
                    }

                }
            }
        }
    }    
    
    if(incoginito_read != NULL){
        fscanf(incoginito_read, "%c %c%d\n", &p, &c, &spy_white.x);
        // la ligne est décalée de 1 pour l'utilisateur
        spy_white.x --;
        // convertit la lettre de la colonne en nombre
        spy_white.y = search_in_table_char(table_charac, c);
        fscanf(incoginito_read, "%c %c%d\n", &p, &c, &spy_black.x);
        // la ligne est décalée de 1 pour l'utilisateur
        spy_black.x--;
        // convertit la lettre de la colonne en nombre
        spy_black.y = search_in_table_char(table_charac, c);    
    }    
    // initialise la grille
    game.joueur = rand() % 2;;
    implement_grid(game.plateau, spy_white, spy_black);
    update_player(&p, game.joueur);
    if(incoginito_read == NULL && incoginito_write != NULL){
        fprintf(incoginito_write, "%c\n", p);
    } 
    printf("Bienvenue dans Incognito\n");
    // lit le FICHIER CHARGÉ pour continuer une partie
    if(incoginito_read != NULL)
        read_file(incoginito_read, &game, table_charac);
    // affiche la grille
    if(ascii_display != NULL)
        display_grid(game.plateau);
    else
        // affichage graphique
        display_grid_graph(game.plateau, renderer);
        
    printf("Rappel : (0, 0) désigne le coin supérieur gauche et (%d, %d) le coin inférieur droit\n", TAILLE - 1, TAILLE - 1);
    // met à jour le joueur
    update_player(&p, game.joueur);
    if(game.joueur == 0) strcpy(player, "White");
    else strcpy(player, "Black");
    while(game_on){
        do{
        printf("Joueur %s, voulez-vous effectuer un mouvement ou une interrogation ? ('d' ou 'i' ou 'E' pour quitter)\n", player);
        scanf(" %c", &choice);
        }while (choice != 'd' && choice != 'i' && choice != 'E');
        if(choice == 'd'){
            do{
                printf("Quel mouvement pour le joueur %s ?\n Saisir sous la forme (a, b) --> (c, d).\n", player);
                scanf(" (%d, %d) --> (%d, %d)", &move.depart.x, &move.depart.y, &move.arrivee.x, &move.arrivee.y);
                // vérifie si on est à l'intérieur d'un château
                move_castle = decide_in_castle(game.plateau, move, game.joueur);
                // on n'est pas dans un château
                if(move_castle == 0){
                    // tente de déplacer une pièce
                    error = move_piece(game.plateau, move, game.joueur);
                    // succès
                    switch (error)
                    {
                    case 0:
                    // vérifie la victoire
                        move_castle = is_win(game.plateau, move, game.joueur);
                        // victoire
                        if(move_castle == 0){
                            update_player(&p, game.joueur);
                            printf("Bravo, le gagnant est : %s\n", player);
                            game_on = 0;
                        // le pion était un chevalier
                        }else if(move_castle == 2){
                            printf("Le pion ne peut pas entrer dans le château...\n");
                            game.plateau[move.depart.x][move.depart.y] = NULL;
                        }
                        // exécute le mouvement
                        game.plateau[move.arrivee.x][move.arrivee.y] = game.plateau[move.depart.x][move.depart.y];
                        game.plateau[move.depart.x][move.depart.y] = NULL;
                        printf("Joueur %s, votre mouvement est exécuté..\n", player);
                        break;
                    case 1:
                        printf("Mouvement illégal : des cases bloquent le passage.\n");
                        break;
                    case 2:
                        printf("Mouvement illégal : un joueur ne peut pas amener un pion dans son château.\n");
                        break;
                    case 3:
                        printf("Mouvement illégal : le pion sélectionné ne vous appartient pas.\n");
                        break;
                    case 4:
                        printf("Mouvement illégal : la case est vide\n");
                        break;
                    default:
                        printf("Le mouvement n'est pas autorisé.\n");
                        break;
                    }
                }
                else{
                    printf("Ce mouvement n'est pas autorisé\n");
                    error = 1;
                }
                // ajout au FICHIER
                if(incoginito_write != NULL){
                    fprintf(incoginito_write, "D %c%d->%c%d\n", table_charac[move.depart.y], 
                                move.depart.x + 1, table_charac[move.arrivee.y], move.arrivee.x + 1);
                
                    // à la fin du jeu on ajoute le gagnant au FICHIER
                    if(game_on == 0){
                        fprintf(incoginito_write, "%c\n", p);
                }
                }
            }while(error != 0);

        }
        // effectue une interrogation
        else if(choice == 'i'){
            do{
                printf("Quel pion %s est l'interrogateur ?\nSaisir comme (a, b)\n", player);
                scanf(" (%d, %d)", &move.depart.x, &move.depart.y);
                printf("Quel pion est interrogé ?\n");
                scanf(" (%d, %d)", &move.arrivee.x, &move.arrivee.y);
                // effectue l'interrogation
                error = interrogate_piece(game.plateau, game.joueur, move.depart, move.arrivee);
                // affiche le résultat
                switch (error)
                {
                    // succès de l'action (chevalier vs chevalier)
                case 0:
                    printf("Joueur %s, vous n'avez pas trouvé l'espion adverse...\nEt en plus, votre chevalier a été empoisonné... \n", player);
                    break;
                case 1:
                    printf("Interrogation non autorisée car les cases ne sont pas adjacentes.\n");
                    break;
                // espion trouvé -> victoire
                case -1:
                    printf("Joueur %s, vous avez interrogé un espion...\n", player);
                    game_on = 0;
                    update_player(&p, game.joueur);
                    printf("Bravo, le gagnant est : %s\n", player);
                    break;
                // espion interroge chevalier -> défaite
                case -2:
                    update_player(&p, (game.joueur + 1) % 2);
                    printf("Joueur %s, vous avez interrogé un chevalier avec votre espion...\n", player);
                    printf("Bravo, le gagnant est : %s\n", (game.joueur == 0)?"Black": "White");
                    game_on = 0;
                    break;
                case 3:
                    printf("Interrogation non autorisée : le joueur a sélectionné les mauvais pions.\n");
                    break;
                case 4:
                    printf("Interrogation non autorisée car les deux cases sont vides.\n");
                    break;
                default:
                    printf("Le mouvement n'est pas autorisé.\n");
                    break;
                }
                if(incoginito_write != NULL){
                    // ajout au FICHIER
                    fprintf(incoginito_write, "I %c%d->%c%d\n", table_charac[move.depart.y], 
                                    move.depart.x + 1, table_charac[move.arrivee.y], move.arrivee.x + 1);
                    // à la fin du jeu on ajoute le gagnant au FICHIER
                    if(game_on == 0){
                        fprintf(incoginito_write, "%c\n", p);
                    }
                }
                
            }while(error == 3 ||error == 1 ||error == 4);

        }
        // Quitte le jeu
        else{
            game_on = 0;
        }
        if(ascii_display != NULL)
            display_grid(game.plateau);
        else
            // affichage graphique
            display_grid_graph(game.plateau, renderer);

        game.joueur = (game.joueur + 1) % 2;
        // passe le tour à l'autre joueur
        if(game.joueur == 0) strcpy(player, "White");
        else strcpy(player, "Black");
    }


    // affiche la grille finale et ferme le FICHIER
    if(ascii_display != NULL)
        display_grid(game.plateau);
    else
        // affichage graphique
        display_grid_graph(game.plateau, renderer);
    // ferme les fichiers
    if(incoginito_read != NULL)
        fclose(incoginito_read);
    if(incoginito_write != NULL)
        fclose(incoginito_write);
    // détruit le rendu et la fenêtre
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // ferme SDL
    SDL_Quit();
    // libère l'espace mémoire
    free(ascii_display);
    free(graphic_display);
    return 0;
}