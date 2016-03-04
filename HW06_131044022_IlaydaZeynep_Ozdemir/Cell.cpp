/* 
 * File:   Cell.cpp
 * Author: ilayda
 * 
 * Created on November 29, 2015, 3:51 PM
 */

#include "Cell.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;


//getC
namespace Reversi__ {

    Cell::Cell() {
        setX("a");
        setY(0);
        setPointX_O("O");
    }

    Cell::Cell(int pos_Y, string pos_X) {
        setY(pos_Y);
        setX(pos_X);
        setPointX_O("O");
    }

    Cell::Cell(int pos_Y, string pos_X, string what) {
        setX(pos_X);
        setY(pos_Y);

        setPointX_O(what);
    }

    void Cell::setX(const string position) {
        m_X = position; //coloum
        setIntX();
    }

    void Cell::setY(const int position) {
        m_Y = position; //row
    }

    void Cell::setIntX() {
        string forIntPart;
        string intPart;
        int temp;
        int valueOfletter;


        for (int i = 0; i < getX().length(); ++i) {

            for (int j = 0; j < 23; ++j) {
                if (getX().at(i) == letterss[j].at(0)) {

                    temp = j;
                    for (int k = i; k < getX().size(); ++k) {
                        forIntPart += getX().at(k);
                    }
                }
            }
        }

        valueOfletter = temp + atoi(forIntPart.c_str());
        for (int i = 1; i < m_X.length(); ++i) {//0.elemani int degil char
            //bu nedenle birden baslattim
            intPart += m_X[i];
        }
        int value_of_intX = atoi(intPart.c_str());
        m_IntX = (value_of_intX * 23) + valueOfletter;
        //burada yaptigim sey : a25 in integer oalrak degerini bulmak
        //25 * 23(harf arrayinin sayisi) + 1(a'nin degeri)
        if (getX() == "w")
            m_IntX = -1000;


    }
    // tablo elemanlari

    void Cell::setPointX_O(const string what_char) {
        m_PointX_O = what_char;
    }
    Cell& Cell::operator=(const Cell& rCell){
        setPointX_O(rCell.getPointX_O());
        setX(rCell.getX());
        setY(rCell.getY());
    }
}

