#include <stdio.h>
#include <string.h>

#define reset "\033[0m"

#define rouge "\033[;41m"
#define vert "\033[;42m"
#define bleu "\033[;44m"
#define blanc "\033[;47m"
#define noir "\033[;40m"


/* ordi windows
#define rouge "R"
#define vert "V"
#define bleu "B"
#define blanc "+"
#define noir "-"
#define reset ""
*/

#define VRAI 1
#define FAUX 0

#define N 5

typedef struct{
    int coordx, coordy;
}pion;

typedef struct{
    pion pionsrouge[N], pionsbleu[N];
    pion pionvert;
} plateau;

typedef struct{
    int joueur;
}cases;

typedef struct {
    int possible;
    pion positions[8];
}mouvement;

typedef struct {
    int possible;
    mouvement mouvements[N];
}coupspions;


plateau config_initiale(){
    int i;
    plateau pdj;
    for(i=0;i<N;i++){
        pdj.pionsrouge[i].coordx = 5;
        pdj.pionsrouge[i].coordy = i+1;
        pdj.pionsbleu[i].coordx = 1;
        pdj.pionsbleu[i].coordy = i+1;
    }
    pdj.pionvert.coordx = 3;
    pdj.pionvert.coordy = 3;
    return pdj;
}

void affichage_plateau(plateau pdj){
    int i,j,k,parite, typePion;
    // Aucunpion : typePion = 0
    // Rouge : typePion = 1
    // Bleu : typePion = 2
    // Vert : typePion = 3
    printf("\n");
    parite = FAUX;
    for(i=N;i>0;i--){
        printf("%d",i);
        for(j=1;j<=N;j++){
            //Recherche du type de case à afficher
            k=0;
            typePion = 0;
            while((k<N) && (typePion == 0)){
                if((pdj.pionsrouge[k].coordx == i) && (pdj.pionsrouge[k].coordy == j)){
                    typePion = 1;
                }else{
                    if((pdj.pionsbleu[k].coordx == i) && (pdj.pionsbleu[k].coordy == j)){
                        typePion = 2;
                    }
                }
                k +=1;
            }
            if((pdj.pionvert.coordx == i) && (pdj.pionvert.coordy == j)){
                typePion = 3;
            }

            //On affiche le pion correspondant
            switch(typePion){
                case 0:
                    if(parite){
                        printf("%s  %s",blanc, reset);
                    }else{
                        printf("%s  %s",noir, reset);
                    }
                    break;
                case 1:
                    printf("%s  %s",rouge, reset);
                    break;
                case 2:
                    printf("%s  %s",bleu, reset);
                    break;
                case 3:
                    printf("%s  %s",vert, reset);
                    break;
                default:
                    printf("Erreur d'affichage");
                    break;
            }


            if(parite){
                parite = FAUX;
            }else{
                parite = VRAI;
            }
        }
        printf("\n");
    }
    printf(" ");
    for(i=1;i<=N;i++){
        printf(" %d",i);
    }
    printf("\n");
}

void affichage_fin(int fin){
    if(fin == 1 ){
        printf("Le joueur Bleu a gagne.\n ****************FIN DU JEU****************\n");
    }else{
        printf("Le joueur Rouge a gagne.\n ****************FIN DU JEU****************\n");
    }
}

pion fausse_position() {
    pion faussePosition;
    faussePosition.coordx = -1;
    faussePosition.coordy = -1;
    return faussePosition;
}

int meme_position(pion position1,pion position2) {
    if (position1.coordx == position2.coordx && position1.coordy == position2.coordy)
        return VRAI;
    else
        return FAUX;
}

int occupe_position(pion position,plateau pdj) {
    int i,occupe;
    occupe = FAUX;
    if (1 > position.coordx || position.coordx > N || 1 > position.coordy || position.coordy > N)
        occupe = VRAI;
    i=0;
    while((i<N) && (occupe == FAUX)) {
        if (meme_position(position,pdj.pionsrouge[i]))
            occupe = VRAI;
        if (meme_position(position,pdj.pionsbleu[i]))
            occupe = VRAI;
        i +=1;
    }
    if (meme_position(position,pdj.pionvert))
        occupe = VRAI;
    return occupe;
}

pion deplacement_pion(pion select,int direction,plateau pdj) {
    int obstacle;
    obstacle = FAUX;
    pion futur;
    futur.coordx = select.coordx;
    futur.coordy = select.coordy;

    switch (direction) {
        case 1:
            while(!obstacle) {
                futur.coordx++;
                if (occupe_position(futur,pdj)) {
                    futur.coordx--;
                    obstacle = VRAI;
                }
            }
            break;

        case 2:
            while(!obstacle) {
                futur.coordx++;
                futur.coordy++;
                if (occupe_position(futur,pdj)) {
                    futur.coordx--;
                    futur.coordy--;
                    obstacle = VRAI;
                }
            }
            break;

        case 3:
            while(!obstacle) {
                futur.coordy++;
                if (occupe_position(futur,pdj)) {
                    futur.coordy--;
                    obstacle = VRAI;
                }
            }
            break;

        case 4:
            while(!obstacle) {
                futur.coordx--;
                futur.coordy++;
                if (occupe_position(futur,pdj)) {
                    futur.coordx++;
                    futur.coordy--;
                    obstacle = VRAI;
                }
            }
            break;

        case 5:
            while(!obstacle) {
                futur.coordx--;
                if (occupe_position(futur,pdj)) {
                    futur.coordx++;
                    obstacle = VRAI;
                }
            }
            break;

        case 6:
            while(!obstacle) {
                futur.coordx--;
                futur.coordy--;
                if (occupe_position(futur,pdj)) {
                    futur.coordx++;
                    futur.coordy++;
                    obstacle = VRAI;
                }
            }
            break;

        case 7:
            while(!obstacle) {
                futur.coordy--;
                if (occupe_position(futur,pdj)) {
                    futur.coordy++;
                    obstacle = VRAI;
                }
            }
            break;

        case 8:
            while(!obstacle) {
                futur.coordx++;
                futur.coordy--;
                if (occupe_position(futur,pdj)) {
                    futur.coordx--;
                    futur.coordy++;
                    obstacle = VRAI;
                }
            }
            break;
    }
    if (meme_position(futur,select))
        futur = fausse_position();
    return futur;
}

mouvement mouvement_possibles(pion select,plateau pdj) {
    mouvement futur;
    int i,compte;
    compte = 0;
    for(i=0;i<8;i++) {
        futur.positions[i] = deplacement_pion(select,i+1,pdj);
        if (meme_position(futur.positions[i],fausse_position()))
            compte++;
    }
    if (compte == 8)
        futur.possible = FAUX;
    else
        futur.possible = VRAI;
    return futur;
}

coupspions coups_pions_possibles(pion pionCouleur[N],plateau pdj) {
    coupspions futur;
    pion select;
    int i,compte;
    compte = 0;
    for(i=0;i<N;i++) {
        select = pionCouleur[i];
        futur.mouvements[i] = mouvement_possibles(select,pdj);
        compte = compte + futur.mouvements[i].possible;
    }
    if (compte == 0)
        futur.possible = FAUX;
    else 
        futur.possible = VRAI;
    return futur;
}

int gagnant_par_capture(plateau pdj) {
    int i;
    i = FAUX;
    if (pdj.pionvert.coordx == 1)
        i = 1;
    else
        if (pdj.pionvert.coordx == 5)
            i = 2;
    return i;
}

int autre_joueur(int joueur) {
    int j;
    if (joueur == 1)
        j = 2;
    else
        j = 1;
    return j;
}


void script() {
    /* initialisation du plateau de jeu */
        plateau pdj;
        pdj = config_initiale();

        int joueur,positionInvalide,pieceInvalide,x,y,selecti,direction,directionInvalide,fin,i;
        pion select,pionsCouleur[N];
        mouvement neutronMouvements;
        coupspions coupsPions;

    /* 1er tour bleu (juste l'un des pions à bouger et on ne peut pas finir la partie) */
        /* Initialisation et calculs de mouvements possibles des pieces */
            joueur = 1;
            coupsPions = coups_pions_possibles(pdj.pionsbleu,pdj);
            affichage_plateau(pdj);
            printf("Tour de bleu\n");

        /* Mouvement d'une piece */
            /* Choix d'une piece */
                positionInvalide = VRAI;
                while(positionInvalide) {
                    pieceInvalide = VRAI;
                    printf("Saisir une de vos pieces sous le format ligne,colonne : ");

                    select.coordx = -1; //rénitialisation des coordonnées pour éviter quelques erreurs de mauvais remplissage côté utilisateur
                    select.coordy = -1;

                    scanf("%d,%d",&x,&y);
                    select.coordx = x;
                    select.coordy = y;
                    selecti = 0;
                    while(pieceInvalide && (selecti < N)) { //Il existe au moins un deplacement pour chaque piece au 1er tour
                        if (meme_position(pdj.pionsbleu[selecti],select)) {
                            pieceInvalide = FAUX;
                            positionInvalide = FAUX;
                        }
                        else
                            selecti++;
                    }
                }

            /* Choix d'une direction */
                directionInvalide = VRAI;
                while(directionInvalide) {
                    printf("Saisir une direction de la piece (%d,%d) entre 1 et 8 : ",select.coordx,select.coordy);
                    scanf("%d",&direction);
                    if (0 < direction && direction < 9)
                        directionInvalide = meme_position(coupsPions.mouvements[selecti].positions[direction-1],fausse_position());
                }

            /* Modification du plateau de jeu */
                pdj.pionsbleu[selecti] = coupsPions.mouvements[selecti].positions[direction-1];
                affichage_plateau(pdj);

    /* creation d'une boucle de tours classiques avec possibilite de sortie en cours de jeu */
        fin = FAUX;
        while (fin == FAUX) {
            /* Nouveau tour */
                joueur = autre_joueur(joueur);
                printf("Tour de ");
                switch (joueur) {
                    case 1 :
                        printf("bleu\n");
                        break;
                    case 2 :
                        printf("rouge\n");
                        break;
                }


            /* Initialisation et calculs des mouvements possible du neutron */
                neutronMouvements = mouvement_possibles(pdj.pionvert,pdj);

            /* Mouvement du neutron */
                if (neutronMouvements.possible) {

                    /* Choix d'une direction */
                        directionInvalide = VRAI;
                        while(directionInvalide) {
                            printf("Saisir une direction du neutron entre 1 et 8 : ");
                            scanf("%d",&direction);
                            if (0 < direction && direction < 9)
                                directionInvalide = meme_position(neutronMouvements.positions[direction-1],fausse_position());
                        }

                    /* Modification du plateau de jeu */
                        pdj.pionvert = neutronMouvements.positions[direction-1];
                        fin = gagnant_par_capture(pdj);
                        affichage_plateau(pdj);

                }
                else
                    fin = autre_joueur(joueur);

            /* Initialisation et calculs de mouvements possibles des pieces */
                if (!fin) {
                    if (joueur == 1) {
                        coupsPions = coups_pions_possibles(pdj.pionsbleu,pdj);
                        for(i=0;i<N;i++)
                            pionsCouleur[i] = pdj.pionsbleu[i];
                    }
                    else {
                        coupsPions = coups_pions_possibles(pdj.pionsrouge,pdj);
                        for(i=0;i<N;i++)
                            pionsCouleur[i] = pdj.pionsrouge[i];
                    }

                /* Mouvement d'une piece */
                    if (coupsPions.possible) {

                        /* Choix d'une piece */
                            positionInvalide = VRAI;
                            while(positionInvalide) {
                                pieceInvalide = VRAI;
                                printf("Saisir une de vos pieces sous le format ligne,colonne : ");

                                select.coordx = -1;
                                select.coordy = -1;

                                scanf("%d,%d",&x,&y);
                                select.coordx = x;
                                select.coordy = y;
                                selecti = 0;
                                while(pieceInvalide && selecti < N)
                                    if (meme_position(pionsCouleur[selecti],select)) {
                                            pieceInvalide = FAUX;
                                            if (coupsPions.mouvements[selecti].possible)
                                                positionInvalide = FAUX;
                                            else
                                                printf("Vous avez selectionne une de vos pieces non deplacables\n");
                                    }
                                    else
                                        selecti++;
                            }

                        /* Choix d'une direction */
                            directionInvalide = VRAI;
                            while(directionInvalide) {
                                printf("Saisir une direction de la piece (%d,%d) entre 1 et 8 : ",select.coordx,select.coordy);
                                scanf("%d",&direction);
                                if (0 < direction && direction < 9)
                                    directionInvalide = meme_position(coupsPions.mouvements[selecti].positions[direction-1],fausse_position());
                            }

                        /* Modification du plateau de jeu */
                            if (joueur == 1)
                                pdj.pionsbleu[selecti] = coupsPions.mouvements[selecti].positions[direction-1];
                            else
                                pdj.pionsrouge[selecti] = coupsPions.mouvements[selecti].positions[direction-1];
                            affichage_plateau(pdj);

                    }
                    else
                        if (fin == FAUX) 
                            fin = autre_joueur(joueur);
                }
        }

    /* affichage de fin de jeu */
        affichage_fin(fin);
}

int main (){
    //Le script permet de mettre facilement et rapidement le programme principal en commentaire afin de tester les sous-programmes plus aisément.
    script();
    return 0;
}
