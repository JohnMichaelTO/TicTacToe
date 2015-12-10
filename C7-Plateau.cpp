#include <iostream>
#include "C7-Plateau.h"
#include <windows.h>

using namespace std;

// Constructeur
Plateau::Plateau(unsigned int _n, unsigned int _m)
{
    this->setN(_n);
    this->setM(_m);

    // Allocation mémoire
    plateau = new char*[n];
    for(unsigned int i = 0; i < n; i++)
    {
        plateau[i] = new char[m];
    }

    this->init();
}

// Constructeur avec paramètres
Plateau::Plateau(unsigned int _n, unsigned int _m, unsigned int _X, unsigned int _O, char **_plateau)
{
    this->setN(_n);
    this->setM(_m);
    this->setX(_X);
    this->setO(_O);

    // Allocation mémoire
    plateau = new char*[n];
    for(unsigned int i = 0; i < n; i++)
    {
        plateau[i] = new char[m];
    }

    // Initialisation
    for(unsigned int i = 0; i < n; i++)
    {
        for(unsigned int j = 0; j < m; j++)
        {
            plateau[i][j] = _plateau[i][j];
        }
    }
}

// Destructeur
Plateau::~Plateau()
{
    for(unsigned int i = 0; i < n; i++)
    {
        delete[] plateau[i];
    }
    delete[] plateau;
    plateau = NULL;
}

// Initialisation plateau
void Plateau::init()
{
    this->setX(0);
    this->setO(0);

    // Initialisation
    for(unsigned int i = 0; i < n; i++)
    {
        for(unsigned int j = 0; j < m; j++)
        {
            plateau[i][j] = ' ';
        }
    }
}

// Affichage du plateau
void Plateau::afficher()
{
    cout << " ";
    for(unsigned int i = 0; i < n; i++)
    {
        cout << "  " << i << " ";
    }
    cout << endl;

    for(unsigned int j = 0; j < m; j++)
    {
        // Séparateur horizontale
        cout << " ";
        for(unsigned int i = 0; i < n; i++) cout << "+---";
        cout << "+" << endl;

        cout << j;

        for(unsigned int i = 0; i < n; i++)
        {
            cout << "| " << plateau[i][j] << " ";
        }
        cout << "|" << endl;
    }
    // Séparateur horizontale
    cout << " ";
    for(unsigned int i = 0; i < n; i++) cout << "+---";
    cout << "+" << endl;
}

// Place un pion sur le plateau
bool Plateau::placerPion(const unsigned int &x, const unsigned int &y, const char &piece)
{
    if(plateau[x][y] == ' ')
    {
        plateau[x][y] = piece;
        if(piece == 'X') X++;
        else O++;

        return true;
    }
    return false;
}

// Annule un coup / Retire un pion du plateau
bool Plateau::retirerPion(const unsigned int &x, const unsigned int &y)
{
    if(plateau[x][y] != ' ')
    {
        if(plateau[x][y] == 'X') X--;
        else O--;

        plateau[x][y] = ' ';
        return true;
    }
    return false;
}

/*
    Retourne un char en fonction des coordonnées de la pièce jouée
    - O : si alignement de O
    - X : si alignement de X
    - 0 : si aucun alignement
    - N : si match nul
*/
char Plateau::estGagnant(const int &x, const int &y, const int &p)
{
    // Cas où le nombre de pièces jouées à l'alignement p
    if(X < p && O < p) return '0';

    // Cas de détection d'un alignement
    char piece = plateau[x][y];

    // Horizontal
    int alignement = 1;
    int borneInf = x - p;
    int borneSup = x + p;
    borneInf = (borneInf < 0) ? 0 : borneInf;
    borneSup = (borneSup > n) ? n : borneSup;

    bool inf = true;
    bool sup = true;

    int i = x - 1;
    int j = x + 1;

    while((i >= borneInf && inf) || (j < borneSup && sup))
    {
        // Gauche
        if(inf && i >= borneInf && plateau[i][y] == piece)
        {
            alignement++;
            i--;
        }
        else inf = false;

        // Droite
        if(sup && j < borneSup && plateau[j][y] == piece)
        {
            alignement++;
            j++;
        }
        else sup = false;

        if(alignement >= p) return piece;
    }

    // Vertical
    alignement = 1;
    borneInf = y - p;
    borneSup = y + p;
    borneInf = (borneInf < 0) ? 0 : borneInf;
    borneSup = (borneSup > m) ? m : borneSup;

    inf = true;
    sup = true;

    i = y - 1;
    j = y + 1;

    while((i >= borneInf && inf) || (j < borneSup && sup))
    {
        // Haut
        if(inf && i >= borneInf && plateau[x][i] == piece)
        {
            alignement++;
            i--;
        }
        else inf = false;

        // Bas
        if(sup && j < borneSup && plateau[x][j] == piece)
        {
            alignement++;
            j++;
        }
        else sup = false;

        if(alignement >= p) return piece;
    }

    // Diagonale haut-gauche vers bas-droite
    alignement = 1;
    borneInf = x - p;
    borneSup = x + p;
    borneInf = (borneInf < 0) ? 0 : borneInf;
    borneSup = (borneSup > n) ? n : borneSup;
    int borneInf2 = y - p;
    int borneSup2 = y + p;
    borneInf2 = (borneInf2 < 0) ? 0 : borneInf2;
    borneSup2 = (borneSup2 > m) ? m : borneSup2;

    inf = true;
    sup = true;

    i = x - 1;
    j = x + 1;
    int k = y - 1;
    int l = y + 1;

    while((i >= borneInf && k >= borneInf2 && inf) || (j < borneSup && l < borneSup2 && sup))
    {
        // Haut-Gauche
        if(inf && i >= borneInf && k >= borneInf2 && plateau[i][k] == piece)
        {
            alignement++;
            i--;
            k--;
        }
        else inf = false;

        // Bas-Droite
        if(sup && j < borneSup && l < borneSup2 && plateau[j][l] == piece)
        {
            alignement++;
            j++;
            l++;
        }
        else sup = false;

        if(alignement >= p) return piece;
    }

    // Diagonale haut-droite vers bas-gauche
    alignement = 1;
    borneInf = x - p;
    borneSup = x + p;
    borneInf = (borneInf < 0) ? 0 : borneInf;
    borneSup = (borneSup > n) ? n : borneSup;
    borneInf2 = y - p;
    borneSup2 = y + p;
    borneInf2 = (borneInf2 < 0) ? 0 : borneInf2;
    borneSup2 = (borneSup2 > m) ? m : borneSup2;

    inf = true;
    sup = true;

    i = x - 1;
    j = x + 1;
    k = y + 1;
    l = y - 1;

    while((i >= borneInf && k < borneSup2 && inf) || (j < borneSup && l >= borneInf2 && sup))
    {
        // Bas-Gauche
        if(inf && i >= borneInf && k < borneSup2 && plateau[i][k] == piece)
        {
            alignement++;
            i--;
            k++;
        }
        else inf = false;

        // Haut-Droite
        if(sup && j < borneSup && l >= borneInf2 && plateau[j][l] == piece)
        {
            alignement++;
            j++;
            l--;
        }
        else sup = false;

        if(alignement >= p) return piece;
    }

    // Cas d'un match nul quand le plateau est rempli
    if(O + X == n * m) return 'N';

    // Cas d'un match nul général
    int nbAlignementX = 0;
    int nbAlignementO = 0;

    for(int x = 0; x < n; x++)
    {
        for(int y = 0; y < m; y++)
        {
            piece = plateau[x][y];

            // Horizontal
            alignement = 1;
            borneSup = x + p;
            borneSup = (borneSup > n) ? n : borneSup;

            j = x + 1;

            char pieceSaved = piece;

            while(j < borneSup)
            {
                // Droite
                if(pieceSaved == ' ' && plateau[j][y] != ' ') pieceSaved = plateau[j][y];

                if(plateau[j][y] == piece || plateau[j][y] == ' ' || plateau[j][y] == pieceSaved)
                {
                    alignement++;
                }
                j++;

                if(alignement == p)
                {
                    if(pieceSaved == 'X') nbAlignementX = nbAlignementX + 1;
                    else if(pieceSaved == 'O') nbAlignementO = nbAlignementO + 1;
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }

            // Vertical
            alignement = 1;
            borneSup = y + p;
            borneSup = (borneSup > m) ? m : borneSup;

            j = y + 1;

            pieceSaved = piece;

            while(j < borneSup)
            {
                // Bas
                if(pieceSaved == ' ' && plateau[x][j] != ' ') pieceSaved = plateau[x][j];

                if(plateau[x][j] == piece || plateau[x][j] == ' ' || plateau[x][j] == pieceSaved)
                {
                    alignement++;
                }
                j++;

                if(alignement == p)
                {
                    if(pieceSaved == 'X') nbAlignementX = nbAlignementX + 1;
                    else if(pieceSaved == 'O') nbAlignementO = nbAlignementO + 1;
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }

            // Diagonale haut-gauche vers bas-droite
            alignement = 1;
            borneSup = x + p;
            borneSup = (borneSup > n) ? n : borneSup;
            int borneSup2 = y + p;
            borneSup2 = (borneSup2 > m) ? m : borneSup2;

            j = x + 1;
            int l = y + 1;

            pieceSaved = piece;

            while(j < borneSup && l < borneSup2)
            {
                // Bas-Droite
                if(pieceSaved == ' ' && plateau[j][l] != ' ') pieceSaved = plateau[j][l];

                if(plateau[j][l] == piece || plateau[j][l] == ' ' || plateau[j][l] == pieceSaved)
                {
                    alignement++;
                }
                j++;
                l++;

                if(alignement == p)
                {
                    if(pieceSaved == 'X') nbAlignementX = nbAlignementX + 1;
                    else if(pieceSaved == 'O') nbAlignementO = nbAlignementO + 1;
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }

            // Diagonale haut-droite vers bas-gauche
            alignement = 1;
            borneSup = x + p;
            borneSup = (borneSup > n) ? n : borneSup;
            borneInf = y - p;
            borneInf = (borneInf < 0) ? 0 : borneInf;

            j = x + 1;
            l = y - 1;

            pieceSaved = piece;

            while(j < borneSup && l >= borneInf)
            {
                // Haut-Droite
                if(pieceSaved == ' ' && plateau[j][l] != ' ') pieceSaved = plateau[j][l];

                if(plateau[j][l] == piece || plateau[j][l] == ' ' || plateau[j][l] == pieceSaved)
                {
                    alignement++;
                }
                j++;
                l--;

                if(alignement == p)
                {
                    if(pieceSaved == 'X') nbAlignementX = nbAlignementX + 1;
                    else if(pieceSaved == 'O') nbAlignementO = nbAlignementO + 1;
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }
        }
    }
    if(nbAlignementO + nbAlignementX <= 0) return 'N';

    return '0';
}

// Retourne le nombre de cases vides
unsigned int Plateau::getNbCasesVides()
{
    return (n * m) - (X + O);
}
