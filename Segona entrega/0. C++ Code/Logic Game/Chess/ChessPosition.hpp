#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
#include<iostream>
#include<vector>
using namespace std;

class ChessPosition {

public:
    ChessPosition() { m_posX = 0; m_posY = 0; }
    ChessPosition(string s) { m_posX = charToCol(s[0]); m_posY = CharToRow(s[1]); }
    int getPosX() const{ return m_posX; }
    int getPosY() const{ return m_posY; } 
    void setPosX(int x) { m_posX = x; }
    void setPosY(int y) { m_posY = y; }
    string toString()const;
    char ColToChar()const;
    int charToCol(char c);
    int CharToRow(char c);

    bool operator==(const ChessPosition pos) const;
    
private:
    int m_posX; //Column
    int m_posY; //Row
    
    
};



int CharToCol(char c);
int CharToRow(char c);
ostream& operator<<(ostream& output, const ChessPosition& pos);
typedef vector<ChessPosition> VecOfPositions;
#endif /* ChessPosition_hpp */