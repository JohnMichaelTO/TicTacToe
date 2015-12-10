#include <iostream>
#include <cstdlib>
#include <ctime>
#include "C7-Game.h"
#include "C7-Plateau.h"
#include "C7-IA.h"

using namespace std;

int main()
{
    srand(time(NULL));
    char selection = '0', run = 1;

    do
    {
        cout << "Tic-Tac-Toe - Equipe numero C7" << endl;
        cout << "------------------------------" << endl;

        cout << "1. Jouer contre l'IA" << endl;
        cout << "2. IA vs IA" << endl;
        cout << "3. Statistiques" << endl;
        cout << "0. Quitter" << endl;
        do
        {
            cout << "\nSelection : ";
            cin >> selection;
            cin.ignore();
            if (selection < '0' || selection > '3')
            {
                cout << "Erreur dans la saisie" << endl;
            }
        } while(selection < '0' || selection > '3');

        Game *game = new Game();

        switch (selection)
        {
            case '1':
                game->jouer();
                break;
            case '2':
                game->mode2IA();
                break;
            case '3':
                game->simulationEchantillon();
                break;
            case '0':
                run = 0;
                break;
        }
        delete game;
        system("pause");
        cout << "\n" << endl;
    } while(run != 0);

    return 0;
}
