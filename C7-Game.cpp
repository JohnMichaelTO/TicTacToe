#include <iostream>
#include "C7-Game.h"
#include "C7-IA.h"
#include <windows.h>

using namespace std;

// Constructeur avec paramètres
Game::Game(unsigned int _n, unsigned int _m, unsigned int _alignement, unsigned int _profondeur, bool _joueur)
{
    this->init(_n, _m, _alignement);
    this->setProfondeur(_profondeur);
    this->setJoueur(_joueur);
}

// Constructeur par défaut
Game::Game()
{
    unsigned int _n, _m, _alignement;

    cout << "\nSaisir N (> 1) : ";
    cin >> _n;

    cout << "\nSaisir M (> 1) : ";
    cin >> _m;

    cout << "\nSaisir l'alignement (> 1) : ";
    cin >> _alignement;

    this->init(_n, _m, _alignement);
}

// Destructeur
Game::~Game()
{
    delete plateau;
    plateau = NULL;
}

// Initialisation
void Game::init(unsigned int _n, unsigned int _m, unsigned int _alignement)
{
    this->setN(_n);
    this->setM(_m);
    this->setP(_alignement);

    plateau = new Plateau(n, m);
}

// Jouer
void Game::jouer()
{
    unsigned int _profondeur;
    bool _joueur;
    cout << "\nSaisir la profondeur d'analyse : ";
    cin >> _profondeur;

    cout << "\nVoulez-vous commencer la partie ? (0 = non/1 = oui) : ";
    cin >> _joueur;
    this->setProfondeur(_profondeur);
    this->setJoueur(_joueur);

    IA *ordi = new IA(profondeur, p, 'O');

    int x, y;
    char gagnant;

    do
    {
        plateau->afficher();
        if(this->getJoueur())
        {
            do
            {
                cout << "\nJoueur joue les X, saisir x puis y : ";
                cin >> x;
                cin >> y;
            } while(!plateau->placerPion(x, y, 'X'));
            cout << "Piece = (" << x << ", " << y << ")" << endl;
            gagnant = plateau->estGagnant(x, y, p);
        }
        else
        {
            cout << "\nOrdinateur joue les O" << endl;
            gagnant = ordi->jouer(plateau);
            cout << "NB feuilles : " << ordi->getNbFeuillesEvaluees() << endl;
            cout << "NB branches elagees : " << ordi->getNbBranchesCoupees() << endl;
            cout << "Duree d'execution : " << ordi->getDureeExecution() << " secondes " << endl;
        }

        this->setJoueur(!this->getJoueur());
    } while(gagnant == '0');

    plateau->afficher();

    switch(gagnant)
    {
        case 'X':
            cout << "Les X gagnent !" << endl;
            break;
        case 'O':
            cout << "Les O gagnent !" << endl;
            break;
        case 'N':
            cout << "Match nul !" << endl;
            break;
    }
}

// Confrontation entre deux IA
void Game::mode2IA(unsigned int IA1, unsigned int IA2)
{
    while(IA1 == 0)
    {
        cout << "\nSaisir la profondeur d'analyse de l'IA 1 : ";
        cin >> IA1;
    }
    while(IA2 == 0)
    {
        cout << "\nSaisir la profondeur d'analyse de l'IA 2 : ";
        cin >> IA2;
    }
    this->setJoueur(0);

    IA *ordiA = new IA(IA1, p, 'O');
    IA *ordiB = new IA(IA2, p, 'X');

    char gagnant;
    plateau->afficher();
    do
    {
        if(this->getJoueur())
        {
            cout << "\nIA1 profondeur " << IA1 << " joue les " << ordiA->getPiece() << endl;
            gagnant = ordiA->jouer(plateau);
            cout << "NB feuilles : " << ordiA->getNbFeuillesEvaluees() << endl;
            cout << "NB branches elagees : " << ordiA->getNbBranchesCoupees() << endl;
            cout << "Duree d'execution : " << ordiA->getDureeExecution() << " secondes " << endl;
        }
        else
        {
            cout << "\nIA2 profondeur " << IA2 << " joue les " << ordiB->getPiece() << endl;
            gagnant = ordiB->jouer(plateau);
            cout << "NB feuilles : " << ordiB->getNbFeuillesEvaluees() << endl;
            cout << "NB branches elagees : " << ordiB->getNbBranchesCoupees() << endl;
            cout << "Duree d'execution : " << ordiB->getDureeExecution() << " secondes " << endl;
        }
        plateau->afficher();
        system("pause");
        this->setJoueur(!this->getJoueur());
    } while(gagnant == '0');

    //plateau->afficher();

    switch(gagnant)
    {
        case 'X':
            cout << "Les X gagnent !" << endl;
            break;
        case 'O':
            cout << "Les O gagnent !" << endl;
            break;
        case 'N':
            cout << "Match nul !" << endl;
            break;
    }
}

// Tests statistiques sur un échantillon nb avec deux IA définis au préalable
void Game::simulationEchantillon(double nb, unsigned int IA1, unsigned int IA2)
{
    while(nb <= 0.0)
    {
        cout << "\nSaisir le nombre d'echantillon : ";
        cin >> nb;
    }
    while(IA1 == 0)
    {
        cout << "\nSaisir la profondeur d'analyse de l'IA 1 : ";
        cin >> IA1;
    }
    while(IA2 == 0)
    {
        cout << "\nSaisir la profondeur d'analyse de l'IA 2 : ";
        cin >> IA2;
    }

    cout << "Plateau : " << n << "x" << m << endl;
    cout << "Alignement a effectuer : " << p << "\n" << endl;

    double X = 0.0;
    double O = 0.0;
    double N = 0.0;

    IA *ordiA = new IA(IA1, p, 'O');
    IA *ordiB = new IA(IA2, p, 'X');

    for(unsigned int i = 0; i < nb; i++)
    {
        char gagnant;
        plateau->init();

        if(i % 2 == 0) this->setJoueur(true);
        else this->setJoueur(false);

        do
        {
            if(this->getJoueur())
            {
                gagnant = ordiA->jouer(plateau);
            }
            else
            {
                gagnant = ordiB->jouer(plateau);
            }

            this->setJoueur(!this->getJoueur());
        } while(gagnant == '0');

        if(gagnant == 'X') X++;
        else if(gagnant == 'O') O++;
        else N++;
    }

    cout << "\nStats\n--" << endl;
    cout << "IA1 profondeur " << ordiA->getProfondeurLimite() << " joue les " << ordiA->getPiece() << endl;
    cout << "IA2 profondeur " << ordiB->getProfondeurLimite() << " joue les " << ordiB->getPiece() << "\n" << endl;
    cout << "X : " << X << " (" << X / nb * 100.0 << "%)" << endl;
    cout << "O : " << O << " (" << O / nb * 100.0 << "%)" << endl;
    cout << "N : " << N << " (" << N / nb * 100.0 << "%)" << endl;
}
