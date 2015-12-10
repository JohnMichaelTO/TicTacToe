#ifndef IA_H
#define IA_H

#include <ctime>
#include "C7-Plateau.h"
#define INFINI 1000.0

class IA
{
    private:
        // Attributs
        unsigned int profondeurLimite;
        unsigned int alignement;
        char piece;
        double scorePiece;
        // Attributs pour stats
        unsigned int nbFeuillesEvaluees;
        unsigned int nbBranchesCoupees;
        double dureeExecution;

        // Méthodes
        double valMin(Plateau *plateau, const unsigned int &profondeur, const unsigned int &x, const unsigned int &y, double *alpha, double *beta);
        double valMax(Plateau *plateau, const unsigned int &profondeur, const unsigned int &x, const unsigned int &y, double *alpha, double *beta);
        double evalIA(Plateau *plateau, const char &gagnant);

    public:
        // Constructeur/Destructeur
        IA(const unsigned int &_profondeurLimite, const unsigned int &_alignement, const char &_piece);
        ~IA();

        // Getter/Setter
        unsigned int getNbFeuillesEvaluees()    { return nbFeuillesEvaluees; }
        unsigned int getNbBranchesCoupees()     { return nbBranchesCoupees; }
        unsigned int getProfondeurLimite()      { return profondeurLimite; }
        unsigned int getAlignement()            { return alignement; }
        char getPiece()                         { return piece; }
        double getDureeExecution()              { return dureeExecution; }
        double getScorePiece()                  { return scorePiece; }

        void setNbFeuillesEvaluees(unsigned int _nbFeuillesEvaluees)    { nbFeuillesEvaluees = _nbFeuillesEvaluees; }
        void setNbBranchesCoupees(unsigned int _nbBranchesCoupees)      { nbBranchesCoupees = _nbBranchesCoupees; }
        void setProfondeurLimite(unsigned int _profondeurLimite)        { profondeurLimite = _profondeurLimite; }
        void setAlignement(unsigned int _alignement)                    { alignement = _alignement; }
        void setPiece(char _piece)                                      { piece = _piece; }
        void setDureeExecution(double _dureeExecution)                  { dureeExecution = _dureeExecution; }
        void setScorePiece(double _scorePiece)                          { scorePiece = _scorePiece; }

        // Méthodes
        char jouer(Plateau *plateau);
};

#endif // IA_H
