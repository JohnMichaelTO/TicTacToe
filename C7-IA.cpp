#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "C7-IA.h"

using namespace std;

// Constructeur
IA::IA(const unsigned int &_profondeurLimite, const unsigned int &_alignement, const char &_piece)
{
    this->setNbFeuillesEvaluees(0);
    this->setNbBranchesCoupees(0);
    this->setProfondeurLimite(_profondeurLimite);
    this->setAlignement(_alignement);
    this->setPiece(_piece);
    this->setScorePiece(pow(INFINI, 1.0 / alignement));
}

// Destructeur
IA::~IA()
{

}

// Retourne la valeur min
double IA::valMin(Plateau *plateau, const unsigned int &profondeur, const unsigned int &x, const unsigned int &y, double *alpha, double *beta)
{
    char gagnant = plateau->estGagnant(x, y, alignement);
    if(gagnant != '0' || profondeur >= profondeurLimite)
    {
        return evalIA(plateau, gagnant);
    }

    double val = INFINI, valTemp;

    for(unsigned int i = 0; i < plateau->getN(); i++)
    {
        for(unsigned int j = 0; j < plateau->getM(); j++)
        {
            if(plateau->getPlateau()[i][j] == ' ')
            {
                plateau->placerPion(i, j, piece);

                valTemp = valMax(plateau, profondeur + 1, i, j, alpha, beta);

                if(valTemp > val || (val == valTemp && rand() % 2 == 0)) val = valTemp;

                plateau->retirerPion(i, j);

                if(val > *beta) *beta = val;

                if(val >= *alpha)
                {
                    this->setNbBranchesCoupees(nbBranchesCoupees + 1);
                    return val;
                }
            }
        }
    }
    return val;
}

// Retourne la valeur max
double IA::valMax(Plateau *plateau, const unsigned int &profondeur, const unsigned int &x, const unsigned int &y, double *alpha, double *beta)
{
    char gagnant = plateau->estGagnant(x, y, alignement);
    if(gagnant != '0' || profondeur >= profondeurLimite)
    {
        return evalIA(plateau, gagnant);
    }

    double val = -INFINI, valTemp;

    for(unsigned int i = 0; i < plateau->getN(); i++)
    {
        for(unsigned int j = 0; j < plateau->getM(); j++)
        {
            if(plateau->getPlateau()[i][j] == ' ')
            {
                if(piece == 'X') plateau->placerPion(i, j, 'O');
                else plateau->placerPion(i, j, 'X');

                valTemp = valMin(plateau, profondeur + 1, i, j, alpha, beta);

                if(valTemp > val || (val == valTemp && rand() % 2 == 0)) val = valTemp;

                plateau->retirerPion(i, j);

                if(val > *alpha) *alpha = val;

                if(val >= *beta)
                {
                    this->setNbBranchesCoupees(nbBranchesCoupees + 1);
                    return val;
                }
            }
        }
    }
    return val;
}

// Heuristique
double IA::evalIA(Plateau *plateau, const char &gagnant)
{
    this->setNbFeuillesEvaluees(nbFeuillesEvaluees + 1);

    if(gagnant == 'N')
    {
        return 0;
    }
    else if(gagnant == piece)
    {
        return INFINI + 1;
    }
    else if(gagnant != piece && gagnant != '0')
    {
        return -INFINI + 1;
    }

    int nbAlignementX = 0;
    int nbAlignementO = 0;
    double hX = 0.0;
    double hO = 0.0;

    for(int x = 0; x < plateau->getN(); x++)
    {
        for(int y = 0; y < plateau->getM(); y++)
        {
            char pieceT = plateau->getPlateau()[x][y];

            // Horizontal
            int pX = 0;
            int pO = 0;
            int alignementTest = 1;
            int borneSup = x + alignement;
            borneSup = (borneSup > plateau->getN()) ? plateau->getN() : borneSup;

            int j = x + 1;

            char pieceSaved = pieceT;

            while(j < borneSup)
            {
                // Droite
                if(pieceSaved == ' ' && plateau->getPlateau()[j][y] != ' ') pieceSaved = plateau->getPlateau()[j][y];

                if(plateau->getPlateau()[j][y] == pieceT || plateau->getPlateau()[j][y] == ' ' || plateau->getPlateau()[j][y] == pieceSaved)
                {
                    alignementTest++;
                    if(plateau->getPlateau()[j][y] == 'X') pX++;
                    if(plateau->getPlateau()[j][y] == 'O') pO++;
                }
                j++;

                if(alignementTest == alignement)
                {
                    if(pieceSaved == 'X') { nbAlignementX++; hX = hX + pX * scorePiece; }
                    else if(pieceSaved == 'O') { nbAlignementO++; hO = hO + pO * scorePiece; }
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }

            // Vertical
            pX = 0;
            pO = 0;
            alignementTest = 1;
            borneSup = y + alignement;
            borneSup = (borneSup > plateau->getM()) ? plateau->getM() : borneSup;

            j = y + 1;

            pieceSaved = pieceT;

            while(j < borneSup)
            {
                // Bas
                if(pieceSaved == ' ' && plateau->getPlateau()[x][j] != ' ') pieceSaved = plateau->getPlateau()[x][j];

                if(plateau->getPlateau()[x][j] == pieceT || plateau->getPlateau()[x][j] == ' ' || plateau->getPlateau()[x][j] == pieceSaved)
                {
                    alignementTest++;
                    if(plateau->getPlateau()[x][j] == 'X') pX++;
                    if(plateau->getPlateau()[x][j] == 'O') pO++;
                }
                j++;

                if(alignementTest == alignement)
                {
                    if(pieceSaved == 'X') { nbAlignementX++; hX = hX + pX * scorePiece; }
                    else if(pieceSaved == 'O') { nbAlignementO++; hO = hO + pO * scorePiece; }
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }

            // Diagonale haut-gauche vers bas-droite
            pX = 0;
            pO = 0;
            alignementTest = 1;
            borneSup = x + alignement;
            borneSup = (borneSup > plateau->getN()) ? plateau->getN() : borneSup;
            int borneSup2 = y + alignement;
            borneSup2 = (borneSup2 > plateau->getM()) ? plateau->getM() : borneSup2;

            j = x + 1;
            int l = y + 1;

            pieceSaved = pieceT;

            while(j < borneSup && l < borneSup2)
            {
                // Bas-Droite
                if(pieceSaved == ' ' && plateau->getPlateau()[j][l] != ' ') pieceSaved = plateau->getPlateau()[j][l];

                if(plateau->getPlateau()[j][l] == pieceT || plateau->getPlateau()[j][l] == ' ' || plateau->getPlateau()[j][l] == pieceSaved)
                {
                    alignementTest++;
                    if(plateau->getPlateau()[j][l] == 'X') pX++;
                    if(plateau->getPlateau()[j][l] == 'O') pO++;
                }
                j++;
                l++;

                if(alignementTest == alignement)
                {
                    if(pieceSaved == 'X') { nbAlignementX++; hX = hX + pX * scorePiece; }
                    else if(pieceSaved == 'O') { nbAlignementO++; hO = hO + pO * scorePiece; }
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }

            // Diagonale haut-droite vers bas-gauche
            pX = 0;
            pO = 0;
            alignementTest = 1;
            borneSup = x + alignement;
            borneSup = (borneSup > plateau->getN()) ? plateau->getN() : borneSup;
            int borneInf = y - alignement;
            borneInf = (borneInf < 0) ? 0 : borneInf;

            j = x + 1;
            l = y - 1;

            pieceSaved = pieceT;

            while(j < borneSup && l >= borneInf)
            {
                // Haut-Droite
                if(pieceSaved == ' ' && plateau->getPlateau()[j][l] != ' ') pieceSaved = plateau->getPlateau()[j][l];

                if(plateau->getPlateau()[j][l] == pieceT || plateau->getPlateau()[j][l] == ' ' || plateau->getPlateau()[j][l] == pieceSaved)
                {
                    alignementTest++;
                    if(plateau->getPlateau()[j][l] == 'X') pX++;
                    if(plateau->getPlateau()[j][l] == 'O') pO++;
                }
                j++;
                l--;

                if(alignementTest == alignement)
                {
                    if(pieceSaved == 'X') { nbAlignementX++; hX = hX + pX * scorePiece; }
                    else if(pieceSaved == 'O') { nbAlignementO++; hO = hO + pO * scorePiece; }
                    else
                    {
                        nbAlignementX++;
                        nbAlignementO++;
                    }
                }
            }
        }
    }

    hX = hX + nbAlignementX;
    hO = hO + nbAlignementO;

    if(piece == 'X') return hX - hO;
    else return hO - hX;
}

// Jouer un coup pour l'IA
char IA::jouer(Plateau *plateau)
{
    unsigned int x, y;
    double vMaxTemp, vMax = -INFINI; // Une valeur très grande pour représenter -oo
    double alpha = -INFINI, beta = INFINI;

    this->setNbFeuillesEvaluees(0);
    this->setNbBranchesCoupees(0);

    clock_t start = clock();
    {
        for(unsigned int i = 0; i < plateau->getN(); i++)
        {
            for(unsigned int j = 0; j < plateau->getM(); j++)
            {
                if(plateau->getPlateau()[i][j] == ' ')
                {
                    plateau->placerPion(i, j, piece);
                    vMaxTemp = valMax(plateau, 1, i, j, &alpha, &beta);

                    if(vMaxTemp > vMax || (vMaxTemp == vMax && rand() % 2 == 0))
                    {
                        vMax = vMaxTemp;
                        x = i;
                        y = j;
                    }
                    plateau->retirerPion(i, j);
                }
            }
        }
    }
    clock_t end = clock();
    clock_t duree = (end - start);
    dureeExecution = duree * 1.0 / CLOCKS_PER_SEC;

    // cout << "Heuristique choisie : " << vMax << endl;

    plateau->placerPion(x, y, piece);
    return plateau->estGagnant(x, y, alignement);
}
