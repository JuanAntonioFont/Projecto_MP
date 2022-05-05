//
//  ChessPosition.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "ChessPosition.hpp"
#include "GameInfo.h"

/* Coordinate system:
    Y (rows)
  . ^
  . |  ***Black***
  4 |
  3 |
  2 |
  1 |  ***White***
 (0,0)----------> X (cols)
      a b c ...
*/

string ChessPosition::toString()const
{
    string s;
    s.resize(1);
    char column=ColToChar();
    char row = '0' + m_posY;
    s[0] = column;
    s[1] = row;
    return s;


}

char ChessPosition::ColToChar() const
{
    char col;
    col = m_posX + 'a';
    /*switch (m_posX)
    {
    case 0:
        col = 'a';
        break;
    case 1:
        col = 'b';
        break;
    case 2:
        col = 'c';
        break;
    case 3:
        col = 'd';
        break;
    case 4:
        col = 'e';
        break;
    case 5:
        col = 'f';
        break;
    case 6:
        col = 'g';
        break;
    case 7:
        col = 'h';
        break;
    default:

        break;
    }*/
    return col;
}

int ChessPosition::charToCol(char c)
{
    return c - 'a';
}

int CharToCol(char c)
{
    return c - 'a';
}


ostream& operator<<(ostream& output, const ChessPosition& pos)
{
    char col = pos.ColToChar();
    int row = pos.getPosY() + 1;
    output << col << row;
    return output;
}

bool ChessPosition::operator==(const ChessPosition pos) const
{
    return (m_posX == pos.getPosX()) && (m_posY == pos.getPosY());
}
