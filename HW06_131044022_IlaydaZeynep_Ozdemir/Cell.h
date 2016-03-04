/* 
 * File:   Cell.h
 * Author: ilayda
 *
 * Created on November 29, 2015, 3:51 PM
 */

#ifndef CELL_H
#define	CELL_H
#include<iostream>
namespace Reversi__ {

    class Cell {
    public:


        Cell();
        Cell(int pos_Y, std::string pos_X);
        Cell(int pos_Y, std::string pos_X, std::string what); //what X mi O mu anlamak icin 
        void setX(const std::string position);
        void setY(const int position);
        void setPointX_O(const std::string what_char);

        int getIntX()const {
            return m_IntX;
        };

        std::string getX()const {
            return m_X;
        };

        int getY()const {
            return m_Y;
        };

        std::string getPointX_O()const {
            return m_PointX_O;
        };
        
        Cell& operator=(const Cell& rCell);

    private:
        //////////////////
        void setIntX(); // odev 4te public olarak yollamistim ama bunu
        //kullanicinin bilmesine gerek yok bilmemeli 
        std::string m_X;
        int m_Y;
        int m_IntX; //X'in integera cevirilmis hali
        //ekrana basilan tablo m_PointX_O memberinda
        std::string m_PointX_O;

    };

    const std::string letterss[23] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "r", "s", "t", "u", "v", "y", "z"};
}
#endif	/* CELL_H */

