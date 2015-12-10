#ifndef GAME_H
#define GAME_H

#include "C7-Plateau.h"

class Game
{
    private:
        // Attributs
        unsigned int p;             // Alignement à effectuer
        unsigned int n, m;          // Dimensions du plateau
        unsigned int profondeur;    // Profondeur d'analyse
        Plateau *plateau;           // Plateau de jeu
        bool joueur;                // Joueur en cours

    public:
        // Constructeur/Destructeur
        Game(unsigned int _n, unsigned int _m, unsigned int _alignement, unsigned int _profondeur, bool _joueur);
        Game();
        ~Game();

        // Getter/Setter
        unsigned int getP()             { return p; }
        unsigned int getN()             { return n; }
        unsigned int getM()             { return m; }
        unsigned int getProfondeur()    { return profondeur; }
        Plateau* getPlateau()           { return plateau; }
        unsigned int getJoueur()        { return joueur; }

        void setP(unsigned int _p)                      { p = _p; }
        void setN(unsigned int _n)                      { n = _n; }
        void setM(unsigned int _m)                      { m = _m; }
        void setProfondeur(unsigned int _profondeur)    { profondeur = _profondeur; }
        void setPlateau(Plateau *_plateau)              { plateau = _plateau; }
        void setJoueur(bool _joueur)                    { joueur = _joueur; }

        // Méthodes
        void init(unsigned int _n, unsigned int _m, unsigned int _alignement);
        void jouer();
        void mode2IA(unsigned int IA1 = 0, unsigned int IA2 = 0);
        void simulationEchantillon(double nb = 0.0, unsigned int IA1 = 0, unsigned int IA2 = 0);
};

#endif // GAME_H
