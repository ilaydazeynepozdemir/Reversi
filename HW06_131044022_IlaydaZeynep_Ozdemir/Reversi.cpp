/* 
 * File:   Reversi.cpp
 * Author: ilayda zeynep ozdemir
 * 
 * Created on November 29, 2015, 3:50 PM
 */

#include "Reversi.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int Reversi__::Reversi::NumberOfLivingGame = 0;
namespace {
    std::string myItoa(int IntNum);
    int FindMaxNum_InArray(const int array[11], int size);

    std::string myItoa(int IntNum) {
        std::string stringNum;
        while (IntNum > 0) {
            int last_digit = IntNum % 10;
            IntNum /= 10;
            char i = '0'; //'0' int degeri 48 oldugu icin bunu kullaniyorum
            i = i + last_digit;
            stringNum = i + stringNum; //her yeni basamagi sayinin string haline ekliyor
        }
        return stringNum;
    }

    int FindMaxNum_InArray(const int array[11], int size) {
        int max = 0;
        int index;
        for (int i = 0; i < size; ++i) {
            if (max <= array[i]) {
                max = array[i];
                index = i;
            }
        }
        return index;
    }


}


namespace Reversi__ {

    Reversi::Reversi() : currentCells(4), sizeOfRow(4), sizeOfCol(4), minCapacity(0) {

        setSizesTable(4, 4);
        take_fromMemory();
        setStartBoard();
        ++(Reversi::NumberOfLivingGame);
    }

    Reversi::Reversi(const int Coloum_and_Row) : currentCells(4), sizeOfRow(Coloum_and_Row), sizeOfCol(Coloum_and_Row), minCapacity(0) {
        //take_fromMemory();
        setSizesTable(Coloum_and_Row, Coloum_and_Row);
        take_fromMemory();
        setStartBoard();
        ++(Reversi::NumberOfLivingGame);
    }

    Reversi::Reversi(const int Row, const int Coloum) : currentCells(4), sizeOfRow(Row), sizeOfCol(Coloum), minCapacity(0) {
        //take_fromMemory();
        setSizesTable(Row, Coloum);
        take_fromMemory();
        setStartBoard();
        ++(Reversi::NumberOfLivingGame);
    }

    Reversi::Reversi(const Reversi& original)//copy constructor
    : sizeOfCol(original.getCol()), sizeOfRow(original.getRow()),
    computer(original.computer), currentCells(original.getCurrentCells()), minCapacity(original.getMinCapacity()) {

        gameCells = new Cell[getRow() * getCol()]; //tekrar bak
        for (int i = 0; i < getCurrentCells(); ++i)
            gameCells[i] = original.gameCells[i];
    }

    Reversi &Reversi::operator=(const Reversi & r_game) {//r-value alir // assignment operatoru

        if (getCurrentCells() != r_game.getCurrentCells()) {
            delete [] gameCells;
            gameCells = new Cell[r_game.getMinCapacity()];
        }

        for (int i = 0; i < r_game.getCurrentCells(); ++i)
            gameCells[i] = r_game.gameCells[i];


        computer.setPointX_O(r_game.computer.getPointX_O());
        computer.setX(r_game.computer.getX());
        computer.setY(r_game.computer.getY());
        setCurrentCells(r_game.getCurrentCells());
        setMinCapacity(r_game.getMinCapacity());

        setRow(r_game.getRow());
        setCol(r_game.getCol());
        return (*this);
    }

    void Reversi::Test(Reversi other1) {
        cout << "~~~~~ TEST FONKSIYONU ~~~~~" << endl;

        cout << "other1 Oyunu" << endl;
        cout << other1;
        cout << "Ana Oyun" << endl;
        cout << (*this);
        cout << "-------------Karsilastirma----------" << endl;
        cout << "İki oyunu karsilastirirsak :" << endl;
        bool goodGame = compare(other1);
        if (goodGame == true)
            cout << "other1 Oyunu ana oyundan daha basarili" << endl;
        else if (goodGame == false)
            cout << "Ana oyun diger oyundan daha basarili" << endl;
        cout << "---------------Atama-----------------" << endl;
        cout << "assignment operatoru ile diger oyunu ana oyuna atarsak (other = game)" << endl;
        other1 = (*this);
        cout << "other1 Oyunu" << endl;
        cout << other1;
        cout << "Ana Oyun" << endl;
        cout << (*this);
        cout << "-------------------copy constructor--------------------" << endl;
        cout << "other1 Oyunu" << endl;
        cout << other1;
        Reversi other2(other1);
        cout << "other2 Oyunu" << endl;
        cout << other2;
        cout << "----------------------operator++(pre)---------------------" << endl;
        cout << "++pre operatoru cagirilmadan once" << endl;
        cout << other1;
        cout << "++pre operatoru cagirilinca" << endl;
        cout << (++other1);
        cout << "----------------------operator++(post)---------------------" << endl;
        cout << "post++ operatoru cagirilmadan once" << endl;
        cout << other2;
        cout << "post++ operatoru cagirilinca" << endl;
        cout << other2++;



    }

    int Reversi::Menu() {
        string decide;
        int dec;

        do {
            cout << "1-Oyunu basa almak isterseniz 1'i" << endl;
            cout << "2-Diger oyuna geçmek isterseniz 2'i" << endl;
            cout << "3-Butun oyunlardan cikmak isterseniz 3'u" << endl;
            cout << "4-Oyuna devam etmek isterseniz 4'u tuslayin" << endl;

            cin>>decide;
        } while (decide != "1" && decide != "2" && decide != "3" && decide != "4");
        dec = atoi(decide.c_str());
        switch (dec) {
            case 1:
                resizeBoard();
                displayCurrentBoard();
                return 1;
                break;
            case 2:
                return 2; //diger oyuna gecmek isteniyor
                break;
            case 3: return 3; //butun oyunlardan cikilmak isteniyor
                break;
            case 4: return 4; //devam etmek
                break;
        }

    }

    void Reversi::Report()const {
        int score_X = 0, score_O = 0;
        for (int i = 0; i < getCurrentCells(); ++i) {
            if (gameCells[i].getPointX_O() == "X")
                ++score_X;
            else if (gameCells[i].getPointX_O() == "O")
                ++score_O;
        }
        cout << "Oyuncu = " << score_O << "   Bilgisayar = " << score_X << endl;
        if (score_X > score_O)
            cout << "Bilgisayar Kazandi !!" << endl;
        else if (score_O > score_X)
            cout << "Siz Kazandiniz!! Tebrikler ~~~ " << endl;
        else if (score_O == score_X)
            cout << "Berabere kaldiniz !!" << endl;
    }

    Reversi Reversi::operator++() {//pre
        this->play();
        return (*this);
    }

    Reversi Reversi::operator++(int sign) {//post
        Reversi post;
        post = (*this);
        this->play();
        return post;
    }

    int Reversi::playGame() {
        Cell user;
        int count = 0;
        bool end;
        //set start ve display koy
        int decide = 0;
        if (getCurrentCells() == 4) {//ilk constructorla olusturuldugunda 4 ile basladigi icin
            takeTableSizes();
            take_fromMemory();
            setStartBoard();
            cout << "Bilgisayar baslasin isterseniz 0'i Siz baslamak isterseniz 1'i tuslayin" << endl;
            do {
                cin>>decide;
            } while (!cin.good());
            if (decide == 0) {
                turn = 0;
            } else turn = 1;
            displayCurrentBoard();
        }
        do {
            if (turn == 1) {
                user = takeCoordinate_withUser();
                play(user.getY(), user.getX());
                displayCurrentBoard();
            }
            if (turn == 0) {
                play();
                displayCurrentBoard();
            }
            endOfGame();

            if (count % 3 == 0) {
                int play_otherGame = Menu();
                if (play_otherGame == 2)//diger oyuna gecer
                    return 2;
                if (play_otherGame == 3) {//butun oyunlardan cikar
                    cout << "Butun oyunlardan cikmak istediniz" << endl;
                    return 3;
                }
                //3 se bir sey yapmaz//oyuna devam eder

                //eger bir sonraki oyuna geçilmek istenirse return ile maine doner
            }
            ++count;
        } while (turn != -1);
        if (turn == -1)
            Report();
        return 0;
    }

    void Reversi::setTurn(int whosTurn) {
        if (turn == -1 && whosTurn == 1)
            turn = -1;
        else turn = whosTurn;

    }

    void Reversi::take_fromMemory() {//DUZENLE!!!!
        Cell *temp;
        setMinCapacity((getCurrentCells() * 2));
        //ilk giris degilse
        //cunku ilk giriste 4 hucre var
        if (getCurrentCells() != 4) {
            temp = new Cell[getCurrentCells()];
            for (int i = 0; i < getCurrentCells(); ++i)
                temp[i] = gameCells[i];
        }//eger yeni baslamamissa oncekini kopyalar
        if (getMinCapacity() < (getCol() * getRow())) {
            gameCells = new Cell[getMinCapacity()];
        }//yer ayirir
        if (getCurrentCells() != 4) {
            for (int i = 0; i < getCurrentCells(); ++i)
                gameCells[i] = temp[i];
            delete []temp;
        }//kopyalanmissa bunlari yeni ayrilan yere yerlestirir
    }

    //ayni boyutlarda oyunu bastan baslatiyor

    void Reversi::resizeBoard() {
        delete []gameCells;
        setCurrentCells(4);
        take_fromMemory();
        setStartBoard();
    }

    void Reversi::setStartBoard() {
        int coloum = 1;
        for (int row = 0; row <= getRow(); ++row) {
            for (int col = 0; col <= getCol(); ++col) {
                if (col < 23) {
                    if (row == (getRow() / 2 - 1) && col == (getCol() / 2 - 1)) {
                        gameCells[0].setPointX_O("O");
                        gameCells[0].setX(letterss[(col)]);
                        gameCells[0].setY(row);
                    } else if (row == (getRow() / 2 - 1) && col == (getCol() / 2)) {
                        gameCells[1].setPointX_O("X");
                        gameCells[1].setX(letterss[(col)]);
                        gameCells[1].setY(row);
                    } else if (row == (getRow() / 2) && col == (getCol() / 2 - 1)) {
                        gameCells[2].setPointX_O("X");
                        gameCells[2].setX(letterss[(col)]);
                        gameCells[2].setY(row);
                    } else if (row == (getRow() / 2) && col == (getCol() / 2)) {
                        gameCells[3].setPointX_O("O");
                        gameCells[3].setX(letterss[(col)]);
                        gameCells[3].setY(row);
                    }
                } else if (col >= 23) {
                    int temp = col % 23;
                    if (temp == 1)
                        temp = col % 23 + 1;
                    if (row == (getRow() / 2 - 1) && col == (getCol() / 2 - 1)) {
                        gameCells[0].setPointX_O("O");
                        gameCells[0].setX(letterss[temp / 2] + myItoa(coloum));
                        gameCells[0].setY(row);
                    } else if (row == (getRow() / 2 - 1) && col == (getCol() / 2)) {
                        gameCells[1].setPointX_O("X");
                        gameCells[1].setX(letterss[temp / 2 + 1] + myItoa(coloum));
                        gameCells[1].setY(row);
                    } else if (row == (getRow() / 2) && col == (getCol() / 2 - 1)) {
                        gameCells[2].setPointX_O("X");
                        gameCells[2].setX(letterss[temp / 2] + myItoa((coloum)));
                        gameCells[2].setY(row);
                    } else if (row == (getRow() / 2) && col == (getCol() / 2)) {
                        gameCells[3].setPointX_O("O");
                        gameCells[3].setX(letterss[temp / 2 + 1] + myItoa((coloum)));
                        gameCells[3].setY(row);
                    }
                }
                if (getCol() / 23 == coloum)
                    ++coloum;
            }
        }
    }

    void Reversi::setSizesTable(const int row, const int col) {
        setRow(row);
        setCol(col);
    }

    bool Reversi::endOfGame() {
        if (getCurrentCells() == (getRow()) * (getCol()))
            setTurn(-1);
    }

    void Reversi::takeTableSizes() {
        char temp_r[10], temp_c[10];
        do {
            cout << "Tablonun satir sayisini giriniz:";
            cin >>temp_r;
            cout << "Tablonun sutun sayisini giriniz:";
            cin>>temp_c;
            setSizesTable(atoi(temp_r), atoi(temp_c));
            if (atoi(temp_r) < 4 || atoi(temp_c) < 4)
                cout << "duzgun bir oyun olabilmesi icin en az 4x4'luk girmelisiniz" << endl;
        } while (atoi(temp_r) < 4 || atoi(temp_c) < 4);
    }

    Cell Reversi::takeCoordinate_withUser() {
        bool is_avail = true;
        int lengths_user[11];
        Cell user;
        do {
            do {
                int position_Y;
                string position_YX;
                string position_X;
                //kullanicidan alma kismi ve aldigi stringi anlamlandirma 
                cout << "oynamak istediginiz hucrenin koordinatlarini giriniz" << endl;
                cin>>position_YX; // c_str'yi atoi string tipini kabul etmedigi icin kullandim
                position_Y = atoi(position_YX.c_str());
                user.setY(position_Y - 1);
                for (int j = 0; j < position_YX.length(); ++j) {
                    for (int i = 0; i < 23; ++i) {
                        //tolower int donuyor bu nedenle letters'in elemanlarinda da 
                        //tolower fonksiyonunu kullandim
                        if (tolower(position_YX[j]) == tolower(letterss[i][0])) {
                            //letterss[i][0] tolower char aliyor lettersin ilk elemaninin 
                            //istedigimiz karakter old biliyorum.bu nedenle [i][0]i yolladim
                            for (int k = j; k < position_YX.length(); ++k) {
                                position_X += (position_YX[k]); //position_X'e a25 gibi olan kisimi dolduruyor
                            }
                            user.setX(position_X);
                            //ornegin a'nin 1 b'nin 2...
                            //i 0 dan basladigi icin bir fazlasini yolladim
                        }
                    }
                }
            } while (user.getIntX() > getCol() || user.getY() > getRow());
            user.setPointX_O("O");

            is_avail = available(lengths_user, user, "X");

        } while (is_avail == false);
        return user;
    }

    void Reversi::play(int Y, std::string X) {
        int lengths[11];
        bool avail = false;
        int side = 0;
        Cell user;
        user.setPointX_O("O");
        user.setX(X);
        user.setY(Y);
        avail = available(lengths, user, "X");
        if (avail == true)
            addNewCell(user, lengths);
        else turn = -1;
        setTurn(0);
    }

    void Reversi::play() {
        int lengths[11];
        bool avail = false;
        int *BestX_Side;
        int *Best_Xlengths;
        Cell *BestX;
        int count = 0;
        bool sign = false;

        for (int i = 0; i < getCurrentCells(); ++i)
            if (gameCells[i].getPointX_O() == "X")
                ++count;

        int sizeOfMove = 0; //yapilabilecek hamle size'i
        for (int i = 0; i < getCurrentCells(); ++i) {
            int coloum = 1;
            if (gameCells[i].getPointX_O() == "X") {//her X icin
                computer.setPointX_O(gameCells[i].getPointX_O());
                computer.setY(gameCells[i].getY());
                computer.setX(gameCells[i].getX());
                for (int k = 0; k < 11; ++k)
                    lengths[k] = 0;
                FindLogicalDecision_X(lengths);
                int index = FindMaxNum_InArray(lengths, 11);
                if (index != 10) {//uygun hamle varsa
                    //int index = FindMaxNum_InVector(lengths, 11); //her X icin en buyuk hamlesinin indexi
                    BestX_Side = new int[count];
                    Best_Xlengths = new int[count];

                    for (int k = 0; k < count; ++k) {
                        BestX_Side[k] = 0;
                        Best_Xlengths[k] = 0;
                    }
                    BestX = new Cell[count];

                    BestX_Side[sizeOfMove] = index; //her X icin en buyuk hamlesinin indexi tutar
                    Best_Xlengths[sizeOfMove] = lengths[index]; //her X in en buyuk hamlesinin uzunlugunu
                    BestX[sizeOfMove] = computer;
                    ++sizeOfMove;
                    sign = true;
                }
            }
        }
        if (sign == true) {//yapilacak hamle varsa
            int max = FindMaxNum_InArray(Best_Xlengths, sizeOfMove);
            computer.setX(BestX[max].getX());
            computer.setY(BestX[max].getY());
            CreateAddedCell_ForComputer(Best_Xlengths[max], BestX_Side[max]);
            for (int i = 0; i < 11; ++i)
                lengths[i] = 0;
            bool avail = false;
            avail = available(lengths, computer, "O");
            if (avail == true)
                addNewCell(computer, lengths);
            delete [] BestX;
            delete [] BestX_Side;
            delete [] Best_Xlengths;
        } else turn = -1; //yapilacak hamle yoksa 
        setTurn(1); //eger yapilacak hamle yokken bu cagirilirsa turn = -1 veriliyor

    }

    void Reversi::CreateAddedCell_ForComputer(int length, int side) {
        switch (side) {
            case 6:
                if ((*this).computer.getIntX() + length + 1 < 23)
                    computer.setX(letterss[(*this).computer.getIntX() + length + 1]);
                else if ((*this).computer.getIntX() + length + 1 >= 23)
                    computer.setX(letterss[((*this).computer.getIntX() + length + 1) % 23] + myItoa(((*this).computer.getIntX() + length + 1) / 23));
                break;
            case 4:
                if ((*this).computer.getIntX() - length - 1 < 23)
                    computer.setX(letterss[(*this).computer.getIntX() - length - 1]);
                else if ((*this).computer.getIntX() - length - 1 >= 23)
                    computer.setX(letterss[((*this).computer.getIntX() - length - 1) % 23] + myItoa(((*this).computer.getIntX() - length - 1) / 23));
                break;
            case 2: computer.setY((*this).computer.getY() + length + 1);
                break;
            case 8: computer.setY((*this).computer.getY() - length - 1);
                break;
            case 9:
                if ((*this).computer.getIntX() + length + 1 < 23)
                    computer.setX(letterss[(*this).computer.getIntX() + length + 1]);
                else if ((*this).computer.getIntX() + length + 1 >= 23)
                    computer.setX(letterss[((*this).computer.getIntX() + length + 1) % 23] + myItoa(((*this).computer.getIntX() + length + 1) / 23));
                computer.setY((*this).computer.getY() - length - 1);
                break;
            case 3:if ((*this).computer.getIntX() + length + 1 < 23)
                    computer.setX(letterss[(*this).computer.getIntX() + length + 1]);
                else if ((*this).computer.getIntX() + length + 1 >= 23)
                    computer.setX(letterss[((*this).computer.getIntX() + length + 1) % 23] + myItoa(((*this).computer.getIntX() + length + 1) / 23));
                computer.setY((*this).computer.getY() + length + 1);
                break;
            case 1:if ((*this).computer.getIntX() - length - 1 < 23)
                    computer.setX(letterss[(*this).computer.getIntX() - length - 1]);
                else if ((*this).computer.getIntX() - length - 1 >= 23)
                    computer.setX(letterss[((*this).computer.getIntX() - length - 1) % 23] + myItoa((*this).computer.getIntX() - length - 1 / 23));
                computer.setY((*this).computer.getY() + length + 1);
                break;
            case 7:if ((*this).computer.getIntX() - length - 1 < 23)
                    computer.setX(letterss[(*this).computer.getIntX() - length - 1]);
                else if ((*this).computer.getIntX() - length - 1 >= 23)
                    computer.setX(letterss[((*this).computer.getIntX() - length - 1) % 23] + myItoa((*this).computer.getIntX() - length - 1 / 23));
                computer.setY((*this).computer.getY() - length - 1);
                break;
        }
    }

    bool Reversi::compare(const Reversi other)const {
        int countFirst_O = 0;
        int countSecond_O = 0;
        for (int i = 0; i < getCurrentCells(); ++i) {
            if (gameCells[i].getPointX_O() == "O")
                ++countFirst_O;
        }
        for (int i = 0; i < other.getCurrentCells(); ++i) {
            if (other.gameCells[i].getPointX_O() == "O")
                ++countSecond_O;
        }
        if (static_cast<double> (countFirst_O) / (getCol() * getRow())
                >= static_cast<double> (countSecond_O) / (getCol() * getRow()))
            return true;
        else return false;

    }

    int Reversi::FindLengthOfRight_X(int lengths, int col, int row, int& sign) const {
        if (col >= getCol() - 1 && computer.getPointX_O() == "X")
            lengths = 0;
        if (col < (getCol() - 1)) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == computer.getY()) {
                    if (gameCells[i].getPointX_O() == "O") {//O ise X
                        ++lengths;
                        lengths = FindLengthOfRight_X(lengths, col + 1, row, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {//O ise O 
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;
    }

    int Reversi::FindLengthOfLeft_X(int lengths, int col, int row, int& sign) const {
        if (col < 0 && computer.getPointX_O() == "X")//bu da sifir donebilir tekrar bir bak!!!!!
            lengths = 0;
        if (col >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == computer.getY()) {
                    if (gameCells[i].getPointX_O() == "O") {
                        ++lengths;
                        lengths = FindLengthOfLeft_X(lengths, col - 1, row, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;
    }

    int Reversi::FindLengthOfUp_X(int lengths, int col, int row, int& sign) const {

        if (row < 0 && computer.getPointX_O() == "X")
            lengths = 0;
        if (row >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getY() == row && gameCells[i].getIntX() == computer.getIntX()) {
                    if (gameCells[i].getPointX_O() == "O") {
                        ++lengths;
                        lengths = FindLengthOfUp_X(lengths, col, row - 1, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;
    }

    int Reversi::FindLengthOfDown_X(int lengths, int col, int row, int& sign) const {

        if (row >= getRow() - 1 && computer.getPointX_O() == "X")
            lengths = 0;
        if (row < getRow() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getY() == row && gameCells[i].getIntX() == computer.getIntX()) {
                    if (gameCells[i].getPointX_O() == "O") {
                        ++lengths;
                        lengths = FindLengthOfDown_X(lengths, col, row + 1, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {
                        sign = true;
                        lengths = 0;
                    }



                }
            }
        }
        if (sign == false)
            lengths = lengths;


        return lengths;
    }

    int Reversi::FindLengthOfRightUp_X(int lengths, int col, int row, int& sign) const {

        if (col >= getCol() - 1 && row < 0 && computer.getPointX_O() == "X")
            lengths = 0;
        if (col < getCol() - 1 && row >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == "O") {
                        ++lengths;
                        lengths = FindLengthOfRightUp_X(lengths, col + 1, row - 1, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;

    }

    int Reversi::FindLengthOfRightDown_X(int lengths, int col, int row, int& sign) const {
        if (col >= getCol() - 1 && row >= getRow() - 1)
            return 0;
        if (col < getCol() - 1 && row < getRow() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == "O") {
                        ++lengths;
                        lengths = FindLengthOfRightDown_X(lengths, col + 1, row + 1, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;
    }

    int Reversi::FindLengthOfLeftUp_X(int lengths, int col, int row, int& sign) const {
        if (col < 0 && row < 0)
            lengths = 0;
        if (col >= 0 && row >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == "O") {
                        ++lengths;
                        lengths = FindLengthOfLeftUp_X(lengths, col - 1, row - 1, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;
    }

    int Reversi::FindLengthOfLeftDown_X(int lengths, int col, int row, int& sign) const {
        if (col < 0 && row >= getRow() - 1)
            lengths = 0;
        if (col >= 0 && row < getRow() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == "O") {// player O ise X 
                        ++lengths;
                        lengths = FindLengthOfLeftDown_X(lengths, col - 1, row + 1, sign);
                    } else if (gameCells[i].getPointX_O() == "X") {// player O ise O
                        sign = true;
                        lengths = 0;
                    }
                }
            }
        }
        if (sign == false)
            lengths = lengths;

        return lengths;
    }

    bool Reversi::FindLogicalDecision_X(int lengths[11])const {

        int sign = 0;
        sign = 0;
        lengths[6] = FindLengthOfRight_X(lengths[6], computer.getIntX() + 1, computer.getY(), sign);
        sign = 0;
        lengths[4] = FindLengthOfLeft_X(lengths[4], computer.getIntX() - 1, computer.getY(), sign);
        sign = 0;
        lengths[2] = FindLengthOfDown_X(lengths[2], computer.getIntX(), computer.getY() + 1, sign);
        sign = 0;
        lengths[8] = FindLengthOfUp_X(lengths[8], computer.getIntX(), computer.getY() - 1, sign);
        sign = 0;
        lengths[1] = FindLengthOfLeftDown_X(lengths[1], computer.getIntX() - 1, computer.getY() + 1, sign);
        sign = 0;
        lengths[7] = FindLengthOfLeftUp_X(lengths[7], computer.getIntX() - 1, computer.getY() - 1, sign);
        sign = 0;
        lengths[3] = FindLengthOfRightDown_X(lengths[3], computer.getIntX() + 1, computer.getY() + 1, sign);
        sign = 0;
        lengths[9] = FindLengthOfRightUp_X(lengths[9], computer.getIntX() + 1, computer.getY() - 1, sign);

    }

    int Reversi::Right(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {

        if (col >= getCol() - 1)
            lengths = 0;
        if (col < getCol() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == player_.getY()) {
                    if (gameCells[i].getPointX_O() == player_.getPointX_O()) {//O ise O 
                        sign = true;
                        lengths = lengths;
                    } else if (gameCells[i].getPointX_O() == rivalPlayer) {//O ise X
                        ++lengths;
                        lengths = Right(lengths, player_, col + 1, row, sign, rivalPlayer);
                    }
                }
            }
        } else if (sign == false)
            lengths = lengths;
        return lengths;
    }

    int Reversi::Left(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (col < 0)
            lengths = 0;
        if (col >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == player_.getY()) {
                    if (gameCells[i].getPointX_O() == player_.getPointX_O()) {
                        sign = true;
                        lengths = lengths;
                    } else if (gameCells[i].getPointX_O() == rivalPlayer) {
                        ++lengths;
                        lengths = Left(lengths, player_, col - 1, row, sign, rivalPlayer);
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;
        return lengths;
    }

    int Reversi::Up(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (row < 0)
            lengths = 0;
        if (row >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getY() == row && gameCells[i].getIntX() == player_.getIntX()) {
                    if (gameCells[i].getPointX_O() == rivalPlayer) {
                        ++lengths;
                        lengths = Up(lengths, player_, col, row - 1, sign, rivalPlayer);
                    } else if (gameCells[i].getPointX_O() == player_.getPointX_O()) {
                        sign = true;
                        lengths = lengths;
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;

        return lengths;
    }

    int Reversi::Down(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (row >= getRow() - 1)
            lengths = 0;
        if (row < getRow() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getY() == row && gameCells[i].getIntX() == player_.getIntX()) {
                    if (gameCells[i].getPointX_O() == rivalPlayer) {
                        ++lengths;
                        lengths = Down(lengths, player_, col, row + 1, sign, rivalPlayer);
                    } else if (gameCells[i].getPointX_O() == player_.getPointX_O()) {
                        sign = true;
                        lengths = lengths;
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;

        return lengths;
    }

    int Reversi::RightUp(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (col >= getCol() - 1 && row < 0)
            lengths = 0;
        if (col < getCol() - 1 && row >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == rivalPlayer) {
                        ++lengths;
                        lengths = RightUp(lengths, player_, col + 1, row - 1, sign, rivalPlayer);
                    } else if (gameCells[i].getPointX_O() == player_.getPointX_O()) {
                        sign = true;
                        lengths = lengths;
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;

        return lengths;

    }

    int Reversi::RightDown(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (col >= getCol() - 1 && row >= getRow() - 1)
            return 0;
        if (col < getCol() - 1 && row < getRow() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == rivalPlayer) {
                        ++lengths;
                        lengths = RightDown(lengths, player_, col + 1, row + 1, sign, rivalPlayer);
                    } else if (gameCells[i].getPointX_O() == player_.getPointX_O()) {
                        sign = true;
                        lengths = lengths;
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;

        return lengths;
    }

    int Reversi::LeftUp(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (col < 0 && row < 0)
            lengths = 0;
        if (col >= 0 && row >= 0) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == rivalPlayer) {
                        ++lengths;
                        lengths = LeftUp(lengths, player_, col - 1, row - 1, sign, rivalPlayer);
                    } else if (gameCells[i].getPointX_O() == player_.getPointX_O()) {
                        sign = true;
                        lengths = lengths;
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;

        return lengths;
    }

    int Reversi::LeftDown(int lengths, const Cell player_, int col, int row, bool& sign, string rivalPlayer) const {
        if (col < 0 && row >= getRow() - 1)
            lengths = 0;
        if (col >= 0 && row < getRow() - 1) {
            for (int i = 0; i < getCurrentCells(); ++i) {
                if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                    if (gameCells[i].getPointX_O() == rivalPlayer) {// player O ise X 
                        ++lengths;
                        lengths = LeftDown(lengths, player_, col - 1, row + 1, sign, rivalPlayer);
                    } else if (gameCells[i].getPointX_O() == player_.getPointX_O()) {// player O ise O
                        sign = true;
                        lengths = lengths;
                    }
                }
            }
        }
        if (sign == false)
            lengths = 0;
        return lengths;
    }

    bool Reversi::available(int lengths[11], const Cell user, string rivalPlayer)const {
        int index = 0;
        bool resAvail = true;
        for (int i = 0; i < 11; ++i)
            lengths[i] = 0;
        bool sign = false;
        sign = false;
        lengths[6] = Right(lengths[6], user, user.getIntX() + 1, user.getY(), sign, rivalPlayer);

        sign = false;
        lengths[4] = Left(lengths[4], user, user.getIntX() - 1, user.getY(), sign, rivalPlayer);

        sign = false;
        lengths[8] = Up(lengths[8], user, user.getIntX(), user.getY() - 1, sign, rivalPlayer);

        sign = false;
        lengths[2] = Down(lengths[2], user, user.getIntX(), user.getY() + 1, sign, rivalPlayer);

        sign = false;
        lengths[9] = RightUp(lengths[9], user, user.getIntX() + 1, user.getY() - 1, sign, rivalPlayer);

        sign = false;
        lengths[3] = RightDown(lengths[3], user, user.getIntX() + 1, user.getY() + 1, sign, rivalPlayer);

        sign = false;
        lengths[7] = LeftUp(lengths[7], user, user.getIntX() - 1, user.getY() - 1, sign, rivalPlayer);

        sign = false;
        lengths[1] = LeftDown(lengths[1], user, user.getIntX() - 1, user.getY() + 1, sign, rivalPlayer);


        if (user.getPointX_O() == "O") {
            for (int i = 0; i < getCurrentCells(); ++i) {
                //user dolu olan noktalardan birini yolladiysa
                if ((user.getIntX() == gameCells[i].getIntX() && user.getY() == gameCells[i].getY()))
                    resAvail = false;
            }
        }
        index = FindMaxNum_InArray(lengths, 11);
        if (index == 10)
            resAvail = false;

        return resAvail;
    }

    void Reversi::addNewCell(const Cell player_, const int lengths[11]) {
        int k = 0;
        increaseCurrentCells();
        take_fromMemory();
        gameCells[getCurrentCells() - 1 ] = player_;
        for (int k = 0; k < 11; ++k) {
            if (lengths[k] != 0) {
                switch (k) {
                    case 6:
                        for (int col = player_.getIntX() + 1; col < player_.getIntX() + lengths[k] + 1; ++col) {
                            for (int i = 0; i < getCurrentCells(); ++i) {
                                if (gameCells[i].getIntX() == col && gameCells[i].getY() == player_.getY()) {
                                    if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                        gameCells[i].setPointX_O(player_.getPointX_O());
                                    }
                                }
                            }
                        }
                        break;
                    case 4:
                        for (int col = player_.getIntX() - 1; col > player_.getIntX() - lengths[k] - 1; --col) {
                            for (int i = 0; i < getCurrentCells(); ++i) {
                                if (gameCells[i].getIntX() == col && gameCells[i].getY() == player_.getY()) {
                                    if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                        gameCells[i].setPointX_O(player_.getPointX_O());
                                    }
                                }
                            }
                        }
                        break;
                    case 2:
                        for (int row = player_.getY() + 1; row < player_.getY() + lengths[k] + 1; ++row) {
                            for (int i = 0; i < getCurrentCells(); ++i) {
                                if (gameCells[i].getY() == row && gameCells[i].getIntX() == player_.getIntX()) {
                                    if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                        gameCells[i].setPointX_O(player_.getPointX_O());
                                    }
                                }
                            }
                        }
                        break;
                    case 8:
                        for (int row = player_.getY() - 1; row > player_.getY() - lengths[k] - 1; --row) {
                            for (int i = 0; i < getCurrentCells(); ++i) {
                                if (gameCells[i].getY() == row && gameCells[i].getIntX() == player_.getIntX()) {
                                    if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                        gameCells[i].setPointX_O(player_.getPointX_O());
                                    }
                                }
                            }
                        }
                        break;
                    case 9:
                        for (int row = player_.getY() - 1; row > player_.getY() - lengths[k] - 1; --row) {
                            for (int col = player_.getIntX() + 1; col < player_.getIntX() + lengths[k] + 1; ++col) {
                                for (int i = 0; i < getCurrentCells(); ++i) {
                                    if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                                        if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                            gameCells[i].setPointX_O(player_.getPointX_O());
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 3:
                        for (int row = player_.getY() + 1; row < player_.getY() + lengths[k] + 1; ++row) {
                            for (int col = player_.getIntX() + 1; col < player_.getIntX() + lengths[k] + 1; ++col) {
                                for (int i = 0; i < getCurrentCells(); ++i) {
                                    if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                                        if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                            gameCells[i].setPointX_O(player_.getPointX_O());
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case 7:
                        for (int row = player_.getY() - 1; row > player_.getY() - lengths[k] - 1; --row) {
                            for (int col = player_.getIntX() - 1; col > player_.getIntX() - lengths[k] - 1; --col) {
                                for (int i = 0; i < getCurrentCells(); ++i) {
                                    if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                                        if (gameCells[i].getPointX_O() != player_.getPointX_O()) {
                                            gameCells[i].setPointX_O(player_.getPointX_O());
                                        }
                                    }
                                }
                            }
                        }

                        break;
                    case 1:
                        for (int row = player_.getY() + 1; row < player_.getY() + lengths[k] + 1; ++row) {
                            for (int col = player_.getIntX() - 1; col > player_.getIntX() - lengths[k] - 1; --col) {
                                for (int i = 0; i < getCurrentCells(); ++i) {
                                    if (gameCells[i].getIntX() == col && gameCells[i].getY() == row) {
                                        if (gameCells[i].getPointX_O() != player_.getPointX_O()) {

                                            gameCells[i].setPointX_O(player_.getPointX_O());
                                        }
                                    }
                                }
                            }
                        }
                        break;
                }
            }
        }
    }

    ostream& operator<<(ostream& print, const Reversi game) {
        int coloum = 1;
        for (int row = 0; row <= game.getRow(); ++row) {
            for (int col = 0; col <= game.getCol(); ++col) {
                bool sign = false;
                if (row == 0 && col == 0)
                    print << "- ";
                else if (row == 0 && col < 23)//coloum harfleri
                    print << letterss[col - 1];
                else if (row == 0 && col >= 23) {

                    if (col / 23 >= coloum) {//23/23=1
                        ++coloum;
                    }
                    print << letterss[col % 23] + myItoa(coloum - 1) + " ";

                } else if (col == 0) {//row
                    if (row < 10)
                        print << row << " ";
                    else
                        print << row;
                }

                for (int i = 0; i < game.getCurrentCells(); ++i) {//  DEGİSECEK!!!
                    if (game.gameCells[i].getY() == row - 1 && game.gameCells[i].getIntX() == col - 1) {
                        print << game.gameCells[i].getPointX_O();
                        i = game.getCurrentCells();
                        sign = true;
                    }

                }

                if (sign == false && col != 0 && row != 0)
                    print << ".";
            }
            print << endl;
        }
        return print;
    }

    void Reversi::displayCurrentBoard()const {
        cout << (*this);
    }

    Reversi::~Reversi() {//distructor
        delete []gameCells;
       // --(Reversi::NumberOfLivingGame);
    }


}
