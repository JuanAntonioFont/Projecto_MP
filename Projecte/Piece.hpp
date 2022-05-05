//
//  Piece.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include "GameInfo.h"
using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,   //torre
    CPT_Bishop, //alfil
    CPT_Knight, //caball
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;





class Piece {

public:
    void setType(ChessPieceType type) { m_type = type; }
    void setColor(ChessPieceColor color) { m_color = color; }
    ChessPieceColor getColor() const { return m_color; }
    char getColorChar()const; //retorna el color com a char {Blanca => w, Negra => b} (per toString de chessboard)
    ChessPieceType getType() const { return m_type; }
    int getTypeInt()const; //retorna el color de la peça com a int {Blanca => 0, Negra => 1}
    //char getTypeChar()const; //retorna el tipus de la peça com a char {consulta la taula del guio}
    char typeToChar()const; //retorna el caracter corresponent al tipus de la peça
private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;
    
    
    
};

ChessPieceType charToType(char c); //retorna el tipus de la peça corresponent al caracter del parametre
#endif /* Piece_hpp */
