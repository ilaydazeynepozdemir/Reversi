/* 
 * File:   Reversi.h
 * Author: ilayda zeynep ozdemir
 *
 * Created on November 29, 2015, 3:50 PM
 */

#ifndef REVERSI_H
#define	REVERSI_H

#include "Cell.h"
namespace Reversi__ {

    class Reversi {
    public:


        Reversi();
        Reversi(const int Coloum_and_Row);
        Reversi(const int Row, const int Coloum);
        /////////////////////////////////////////////////////////////
        Reversi(const Reversi& orig); //copy constructor            /
        Reversi& operator=(const Reversi& r_game); //r-value alir   /
        virtual ~Reversi(); //destructor                            /    
        /////////////////////////////////////////////////////////////
        void setSizesTable(const int row, const int col);
        void resizeBoard(); //resize yapildiginda bastan baslar
        //when the board resized,the game starts from the begining

        //call by value
        //test fonksiyonu
        void Test(Reversi other1);

        int getRow()const {
            return sizeOfRow;
        }

        int getCol()const {
            return sizeOfCol;
        }

        int getTurn()const {
            return turn;
        }
        void play();
        void play(int Y, std::string X);
        ///////////////////////////////////////////////////////////////////
        //eger bir sonraki oyuna geçilmek istenirse return ile maine doner/
        int playGame(); //tablo boyunu alir //oyun fonksiyonlarini cagirir/
        //oyunun genel fonksiyonudur                                      /
        ///////////////////////////////////////////////////////////////////

        static int getNumberOfLivingGames() {
            return NumberOfLivingGame;
        }
        //other iyiyse true,kotuyse false doner
        bool compare(const Reversi other)const;

        Reversi operator++(); //pre // oynar ve oynanmis hali dondurur 
        Reversi operator++(int sign); //post // oynar ama oynanmamis hali dondurur

        void setStartBoard(); //baslangic tablosu
        void displayCurrentBoard()const; //insertion operatoru cagiriliyor 
        //insertion operatoru
        friend std::ostream& operator<<(std::ostream& print, const Reversi game); // print game

        int Menu();
        void Report()const;

        //size boyutlarini alir
        //playGame fonksiyonu icin yardimci
        void takeTableSizes();
        //guncel dolu hucre sayisi

        int getCurrentCells()const {
            return currentCells;
        }

    private:
        static int NumberOfLivingGame;
        Cell computer;
        Cell *gameCells;
        int sizeOfCol; //width
        int sizeOfRow; //height

        int currentCells; //guncel kullanilan Cell'ler. LivingCell
        int minCapacity; //guncel Kullanilan Cell sayisinin 2 kati kadar 

        int turn;

        void setTurn(int whosTurn);

        void setMinCapacity(int min) {
            minCapacity = min;
        }

        int getMinCapacity() const {
            return minCapacity;
        }

        void take_fromMemory();//hafizadan yer alir
        //oncelikle currentCell'in iki kati kadar alir
        //sonra gerekli oldukca buyutur

        void setCurrentCells(int Curr_Cells) {
            currentCells = Curr_Cells;
        }

        int increaseCurrentCells() {
            ++currentCells;
        }

        void setRow(const int Row) {
            sizeOfRow = Row;
        }

        void setCol(const int Col) {
            sizeOfCol = Col;
        }

        //tam olarak calismiyor
        //turn'u degistirdigi icin const olamiyor
        bool endOfGame();
        
        //uygun olup olmadigi belirlenir //ortak fonksiyon
        bool available(int lengths[11], const Cell user, std::string rivalPlayer)const;

        Cell takeCoordinate_withUser();
        int Right(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int Left(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int Up(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int Down(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int RightUp(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int RightDown(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int LeftUp(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;
        int LeftDown(int lengths, const Cell player_, int col, int row, bool& sign, std::string rivalPlayer) const;

        //FindLength fonksiyonlari bilgisayar icin gerekli
        //oncekoyulan noktalar bu fonksiyonlar sayesinde belirleniyor
        //daha sonra Right-Left.. fonksiyonlari cagiriliyor ve ayni user gibi
        //tekrardan uzunluklar bulunup uygun taraflar seciliyor
        //Right,Left... fonksiyonlari varken bunlari tekrarlama sebebim
        //konulan noktayi secip sonra tum koselerine olan uygunlugu available 
        //fonksiyonuyla belirlemek
        int FindLengthOfRight_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfLeft_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfUp_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfDown_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfRightUp_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfRightDown_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfLeftUp_X(int lengths, int col, int row, int& sign) const;
        int FindLengthOfLeftDown_X(int lengths, int col, int row, int& sign) const;
        //uygun nokta belirlenmesi icin 8 tarafin uzunlugu belirlenir
        bool FindLogicalDecision_X(int lengths[11])const;
        //user ve computer icin tum koselerinde olan uygun uzunluk bulunup nokta uygunsa
        //available dondurulur
        bool available(const int lengths[11])const;
        void CreateAddedCell_ForComputer(int length, int side);


        void addNewCell(const Cell player_, const int lengths[11]);
        //Eger bir sonraki oyuna gecis yapilmasi istenirse True return eder;
    };
}


#endif	/* REVERSI_H */

