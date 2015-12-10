#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>

class Plateau
{
    private:
        // Attributs
        unsigned int n, m; // Dimensions du plateau
        char** plateau;
        unsigned int X, O;

    public:
        // Constructeur/Destructeur
        Plateau(unsigned int _n, unsigned int _m);
        Plateau(unsigned int _n, unsigned int _m, unsigned int _X, unsigned int _O, char **_plateau);
        ~Plateau();

        // Getter/Setter
        unsigned int getN() { return n; }
        unsigned int getM() { return m; }
        unsigned int getX() { return X; }
        unsigned int getO() { return O; }
        char** getPlateau() { return plateau; }

        void setN(unsigned int _n)          { n = _n; }
        void setM(unsigned int _m)          { m = _m; }
        void setX(unsigned int _X)          { X = _X; }
        void setO(unsigned int _O)          { O = _O; }
        void setPlateau(char** _plateau)    { plateau = _plateau; }

        // Méthodes
        void init();
        void afficher();
        bool placerPion(const unsigned int &x, const unsigned int &y, const char &piece);
        bool retirerPion(const unsigned int &x, const unsigned int &y);
        char estGagnant(const int &x, const int &y, const int &p);
        unsigned int getNbCasesVides();
};

#endif // PLATEAU_H
