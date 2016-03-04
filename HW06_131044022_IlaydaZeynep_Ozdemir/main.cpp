/* 
 * File:   main.cpp
 * Author: ilayda zeynep ozdemir
 *
 * Created on November 29, 2015, 3:50 PM
 */

#include <cstdlib>
#include"Reversi.h"
using namespace std;
using namespace Reversi__;

/*
 * 
 */
int main(int argc, char** argv) {
    Reversi Game1(8, 8);
    Reversi Game2(7);
    Reversi Game3(10);
    Reversi Game4(8, 16);
    Reversi Game5(10, 10);
    int sign = 1;
    while (sign != 3 && sign != 0) {
        if (sign == 1 || sign == 2) {
            cout << "Oyun 1" << endl;
            sign = Game1.playGame();
        }
        if (sign == 1 || sign == 2) {
            cout << "Oyun 2" << endl;
            sign = Game2.playGame();
        }
        if (sign == 1 || sign == 2) {
            cout << "Oyun 3" << endl;
            sign = Game3.playGame();
        }
        if (sign == 1 || sign == 2) {
            cout << "Oyun 4" << endl;
            sign = Game4.playGame();
        }
        if (sign == 1 || sign == 2) {
            cout << "Oyun 5" << endl;
            sign = Game5.playGame();
        }
    }
    cout<<"Yasayan Oyun Sayisi ="<<Reversi::getNumberOfLivingGames()<<endl;
    
    Game1.Test(Game2);
    return 0;
}

