#include <stdio.h>
#include <stdlib.h>


#define MAXPRENOM  100

//lecture de la liste de prénoms

/*PRE: nb_prenoms est une variable entière déclarée et liste[MAXPRENOM][20] est un tableau de caractère déclaré.
*POST:liste est un tableau  de caractères qui reprend les prénoms entrés directement par l'utilisateur.
∀i : 0 ≤ i <  nb_prenoms ⇒ liste[MAXPRENOM][20] est initialisée
nb_prenoms est le nombre de prénoms entrés par l’utilisateur.

*/

void lirePrenoms(int *nb_prenoms, char liste[MAXPRENOM][20])
{
    int i;
    for(i=0;i<*nb_prenoms;i++)
    {
        printf("Entrez le prénom de la personne %d \n", i + 1);
        scanf("%s",liste[i]);
    }

}

//compte des voyelles

/*PRE: nbrVoyelles est déclaré.
Prenoms[][] et nb_prenoms sont initialisés.
*POST:nbrVoyelles est un tableau d’entier qui reprend le nombre de voyelle comprise dans chaque prénom.

*/


void fctCompteVoyelles(char prenoms[][20], int *nb_prenoms, int nbrVoyelles[])
{
    int c=0;
    int i;
    for( i=0 ; i< *nb_prenoms ; i++)
    {
        int j;
        for(j=0 ; prenoms[i][j] != '\0' ; j++)
        {
            switch (prenoms[i][j])
            {
                case 'a' :
                    c++;
                    break;
                case 'e' :
                    c++;
                    break;
                case 'i' :
                    c++;
                    break;

                case 'o' :
                    c++;
                    break;
                case 'u' :
                    c++;
                    break;
                case 'y' :
                {
                    if( (prenoms[i][j+1] != 'a') && (prenoms[i][j+1] != 'e') && (prenoms[i][j+1] != 'i') && (prenoms[i][j+1] != 'o') && (prenoms[i][j+1] != 'u'))
                        c++;
                }
                    break;
            }
        }
        nbrVoyelles[i]=c;
        c=0;
    }
}

//compatibilité couples

/*PRE: nbrVoyelles et nb_prenoms sont initialisés.
MatriceCouplesCompatibles est un tableau d’entiers déclaré (ou pointeur).
*POST:  MatriceCouplesCompatibles est un tableau à deux dimensions d’entiers qui contient  pour chaque éléments deux valeurs possibles 1 ou 0 (booléen) : 1 signifie que le couple d’indice (i,j) est compatible et 0 que le couple ne l’est pas.
*/

void initialisationMatrice( int nbrVoyelles[], int *nb_prenoms,int MatriceCouplesCompatibles[*nb_prenoms][*nb_prenoms])
{

    int i,j;
    for(i=0 ; i < *nb_prenoms ; i++)
        for( j=0 ; j < *nb_prenoms ; j++)
        {
            if(nbrVoyelles[i] == nbrVoyelles[j] && i < j)
            {
                MatriceCouplesCompatibles[i][j]=1;
            }
            else
                MatriceCouplesCompatibles[i][j]=0;
        }

}



/*PRE: str est une chaine de caractère (se termine par '\0') initialisée
*POST: renvoie la taille de str (le nombre de caractères avant '\0')
*/

int strlength(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }

    return i;
}


/*PRE: str  et score ont la même taille, str est une chaine de caractère (donc se termine par '\0'), ce sont des tableaux initialisés.
 *POST: remplit score avec les valeurs correspondants aux lettres de str (de 1 à 9)
 * */

int lettersToVal (char* str, int* score)
{
    int i = 0;
    while(*str){
        score[i] = ((*str)-'a')%9+1;
        i++;
        str++;
    }
    return i;
}		/* -----  end of function lettersToVal  ----- */

/*PRE: taille est la taille de chiffresIn.  chiffresIn est un tableau initialise, chiffresOut aussi
 *     la taille de chiffresOut est la moitie de celle de chiffresIn (si taille est pair) ou la moitie arrondie superieur sinon
 *POST: chiffresOut est rempli de la somme des chiffres deux à deux de chiffresIn, en laissant le dernier intact (si chiffresIn est impair)
 *
 *Exemple: chiffresIn = 1,2,5,9,3,4,2; chiffreOut = 3,14,7,2
 ** */


void add2chiffres (int* chiffresIn,int taille,int* chiffresOut)
{


    int i;
    if( (taille%2) == 0)
    { for(i=0; i<taille/2; i++)
        {
            chiffresOut[i]=chiffresIn[2*i]+chiffresIn[2*i+1];
        }
    }

    else
    { for(i=0; i < ((taille-1)/2) ;  i++)
        {
            chiffresOut[i]=chiffresIn[2*i]+chiffresIn[2*i+1];
        }
        chiffresOut[(taille-1)/2]=chiffresIn[taille-1];
    }

}


/*PRE: numbers est un tableau initialisé contenant des nombres de 0 à 18
 * taille est la taille de numbers
 *
 * POST: tous les nombres de numbers contenant deux chiffres sont remplacés
 * par la somme de leurs chiffres.  Les autres sont inchangés
 *
 * */
void numbers2Chiffres (int* numbers, int taille)
{
    int i;
    for( i=0; i<taille; i++)
    {
        if (numbers[i] > 9)
        {
            numbers[i]= 1 + (numbers[i]%10);
        }
    }

}



/*PRE: prenom est une chaine de caractères initialisée et non vide
 *POST: renvoie la valeur numérologique de prenom telle que présentée
 *      par l'algorithme de
 * http://compatibilite-prenoms.fr/description-algorithme-numerologie.php
 * */

int score (char* prenom)
{
    int score[strlength(prenom)];
    //Transformation de chaque lettre du prenom en chiffre de 1 Ã?Â  9, et copie de ces chiffres dans score
    //taille = la taille de score
    int taille = lettersToVal(prenom,score);
    while(taille>1){
        int tailleNew;//Taille du tableau contenant le prochain score
        if(taille%2==0){
            tailleNew = taille/2;
        }
        else{
            tailleNew = (taille-1)/2+1;
        }
        //Tableau contenant le prochain score
        int scoreNew[tailleNew];
        //Addition des chiffres de score 2 Ã?Â  2.  Copie du rÃ?Â©sultat dans scoreNew
        add2chiffres(score,taille,scoreNew);
        //Transformation des nombres de scoreNew en chiffres de 1 Ã?Â  9
        numbers2Chiffres(scoreNew,tailleNew);
        taille=tailleNew;
        int i;
        //Copie du contenu de scoreNew dans score
        for(i=0;i<tailleNew;i++){
            score[i] = scoreNew[i];
        }
    }

    return score[0];
}		/* -----  end of function score  ----- */

/*
 * PRE: prenom1 et prenom2 sont des chaines de caracteres initialisees
 * POST: renvoie la compatibilite entre prenom1 et prenom2 selon l'algorithme
 * presente par http://compatibilite-prenoms.fr
 *       cette compatibilite est exprimee sous la forme d'une valeur reelle entre 0 et 1.
 *
 **/

float compatibilite(char* prenom1,char* prenom2)
{
    float resultat;
    int delta;
    delta= score(prenom2)-score(prenom1);
    if(delta <0)
        delta = -delta;
    resultat= 1-0.125*delta;

    return resultat;

}

/*
* PRE: prenoms[][] est un tableau de caractères contenant la liste des prénoms et est initialisé. nb_prenoms est initialisé. MatriceCouplesCompatibles est un tableau à deux dimensions d’entiers qui contient pour chaque élément deux valeurs possibles 1 ou 0 (booléen) : 1 signifie que le couple d’indice (i,j) est compatible et 0 qu’il ne l’est pas. MatriceCouplesCompatibles est initialisé.
* POST: Les couples compatibles sont affichés avec leurs compatibilités respectives.
*/


void affichageCouples(char prenoms[][20], int* nb_prenoms, int MatriceCouplesCompatibles[*nb_prenoms][*nb_prenoms])
{
    int i,j;
    printf("Les couples compatibles sont : \n");
    for(i=0 ; i < *nb_prenoms ; i++)
        for(j=0 ; j < *nb_prenoms ; j++)
            if(MatriceCouplesCompatibles[i][j]==1)
            {
                printf("%20s et %20s :  %.2f \n" , prenoms[i], prenoms[j], compatibilite(prenoms[i],prenoms[j]));
            }
}


int main(void)
{

    char prenomsStr[3];
    int nb_prenoms;
    char prenoms[MAXPRENOM][20];
    int nbrVoyelles[MAXPRENOM];
    int MatriceCouplesCompatibles[MAXPRENOM][MAXPRENOM];



    printf("Combien de prenoms compte votre liste (maximum 100)?\n");
    scanf("%s", prenomsStr);
    nb_prenoms = atoi(prenomsStr);
    while (nb_prenoms < 1 || nb_prenoms > MAXPRENOM)
    {
        printf("Erreur ! Entrez une valeur comprise entre 1 et 100.\n");
        scanf("%s", prenomsStr);
        nb_prenoms = atoi(prenomsStr);
    }

    lirePrenoms(&nb_prenoms, prenoms);
    fctCompteVoyelles(prenoms, &nb_prenoms, nbrVoyelles);
    initialisationMatrice(nbrVoyelles, &nb_prenoms, MatriceCouplesCompatibles);
    affichageCouples(prenoms, &nb_prenoms, MatriceCouplesCompatibles);


    return EXIT_SUCCESS;
}
