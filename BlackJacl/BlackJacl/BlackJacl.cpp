#include <iostream>
#include <Windows.h>
using namespace std;

//Variables de uso
int picas[13];
int diamantes[13];
int corazones[13];
int treboles[13];
bool gameOver = false;

string tipoPalo;

//Variables Jugador 1
string player1 = "Leo";
int pointsPlayer1 = 0;
bool surrender1 = false;
bool winnerP1 = false;
bool loserP1 = false;

//Variables Jugador 2x
string player2 = "Arnau";
int pointsPlayer2 = 0;
bool surrender2 = false;
bool winnerP2 = false;
bool loserP2 = false;


//Funciones

//Inicializa cualquier array con sus 13 posiciones a 1
//de esta forma, indicamos que todas las cartas están disponibles
//si una posición está a 0, esa carta ya está repartida y no se repite
void inicializaArray(int(&pArray)[13]) {
    for (int i = 0; i < 13; i++) {
        pArray[i] = 1;
    }
}

void exceptions(int& points, string player) {
    if (player == player1) {
        int option;
        cout << "Te ha tocado un AS "<< tipoPalo << " y tienes " << points << ", cuanto quieres que valga?" << endl;
        cout << "[1] - 1" << endl;
        cout << "[2] - 11" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            points += 1;
            break;
        case 2:
            points += 11;
            break;
        default:
            break;
        }
    }
    else {
        if (points <= 11) {
            points += 11;
        }
        else {
            points += 1;
        }
    }
}

void chooseCards(int& points, string player) {
    bool choosed = false;
    int indiceCarta = 0;

    while (!choosed) {
        //Elije una carta del 1 al 13
        indiceCarta = rand() % 13;
       
        //Comprueba las Copas
        if ((rand() % 4) == 0) {
            if (picas[indiceCarta] == 1) {
               
                //devuelve la carta
                picas[indiceCarta] = 0;
                choosed = true;
                tipoPalo = "copas";
            }
            //Comprueba los diamantes
        }
        else if ((rand() % 4) == 1)
            if (diamantes[indiceCarta] == 1) {
                //devuelve la tarjeta
                diamantes[indiceCarta] = 0;
                choosed = true;
                tipoPalo = "diamantes";
            }
            //Comprueba los corazones
            else if ((rand() % 4) == 2)
                if (corazones[indiceCarta] == 1) {
                    //devuelve la tarjeta
                    corazones[indiceCarta] = 0;
                    choosed = true;
                    tipoPalo = "corazones";
                }
                //Comprueba los treboles
                else {
                    if (treboles[indiceCarta] == 1) {
                        //devuelve la tarjeta
                        treboles[indiceCarta] = 0;
                        choosed = true;
                        tipoPalo = "treboles";
                    }
                }
    }
    if (indiceCarta >= 10) {
        points += 10;
        if (indiceCarta == 10) {
            cout << "El jugador " << player << " ha sacado una J de " << tipoPalo << " y tiene un total de " << points << endl;
        }
        else if (indiceCarta == 11) {
            cout << "El jugador " << player << " ha sacado una Q de " << tipoPalo << " y tiene un total de " << points << endl;
        }
        else {
            cout << "El jugador " << player << " ha sacado un K de " << tipoPalo << " y tiene un total de " << points << endl;
        }
    }
    else if (indiceCarta == 1) {
        if (player == player1) {
            exceptions(points, player);
        }
        else {
            exceptions(points, player);
            cout << "El jugador " << player << " ha sacado un AS de " << tipoPalo << " y tiene un total de " << points << endl;
        }
    }
    else {
        points += indiceCarta + 1;
        cout << "El jugador " << player << " ha sacado un " << indiceCarta + 1 << " de " << tipoPalo << " y tiene un total de " << points << endl;
    }
}



bool checkPoints(int& points, bool& winner, bool& loser) {
    if (points == 21) {
        winner = true;
        return true;
    }
    else if (points > 21) {
        loser = true;
        return true;
    }
    return false;
}

bool checkWhoWins(int points1, int points2, bool& winner2) {
    if (points2 > points1) {
        winner2 = true;
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    inicializaArray(picas);
    inicializaArray(diamantes);
    inicializaArray(corazones);
    inicializaArray(treboles);
    srand(time(NULL));
    //primer reparto de cartas
    chooseCards(pointsPlayer1, player1);
    Sleep(10);
    chooseCards(pointsPlayer1, player1);
    Sleep(10);
    //Puede pasar que ganemos o perdamos nada más comenzar
    surrender1 = checkPoints(pointsPlayer1, winnerP1, loserP1);
    Sleep(10);
    chooseCards(pointsPlayer2, player2);
    Sleep(10);
    while (!surrender1) {
        int choice = 0;
        //Comienza el juego con el jugador 1
        while (choice != 1 && choice != 2) {
            cout << "Tienes " << pointsPlayer1 << ".Quieres pedir carta?" << endl;
            cout << "1.- Si" << endl;
            cout << "2.- No" << endl;
            cin >> choice;
            if (choice != 1 && choice != 2) {
                cout << "Por favor, elije una opción válida." << endl;
            }
        }
        if (choice == 1) {
            chooseCards(pointsPlayer1, player1);
            surrender1 = checkPoints(pointsPlayer1, winnerP1, loserP1);
            //comprueba si se ha pasado o ha ganado la partida
        }
        else {
            //Si no quiere carta, es turno de la banca
            surrender1 = true;
        }
    }
    //Termina el turno del jugador 1. Hay que comprobar si ha ganado (winnerP1) o perdido ya (loserP1), o si la banca tiene que tirar
    if (winnerP1) {
        cout << "El jugador " << player1 << " gana y la banca pierde" << endl;
    }
    else if (loserP1) {
        cout << "El jugador " << player1 << " pierde y la banca gana" << endl;
    }
    else {
        //turno de la banca
        while (!surrender2) {
            chooseCards(pointsPlayer2, player2);
            Sleep(10);
            surrender2 = checkPoints(pointsPlayer2, winnerP2, loserP2);
            if (!surrender2) {
                //Comprueba si la banca ya gana por puntos
                surrender2 = checkWhoWins(pointsPlayer1, pointsPlayer2, winnerP2);
            }
        }
        if (winnerP2) {
            cout << "La banca gana y el jugador " << player1 << " pierde" << endl;
        }
        else if (loserP2) {
            cout << "La banca pierde y el jugador " << player1 << " gana" << endl;
        }
    }

}