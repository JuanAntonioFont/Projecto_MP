//
//  ChessPosition.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "ChessPosition.hpp"
#include "GameInfo.h"
#include "Chessboard.hpp"

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
    /*s.resize(1);*/
    char column=ColToChar();
    char row = '1' + m_posY;
    s += column;
    s += row;
    return s;


}
//string ToString()
//{
//    string s;
//    s.resize(1);
//    char column = ColToChar();
//    char row = '0' + m_posY;
//    s[0] = column;
//    s[1] = row;
//    return s;
//
//
//}

char ChessPosition::ColToChar() const
{
    char col;
    col = m_posX + 'a';
   
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

int ChessPosition::CharToRow(char c)
{
    
    return c - 1 - '0';
}

int CharToRow(char c)
{
    
    return c - 1 - '0';
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
