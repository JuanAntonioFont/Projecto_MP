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
    void            setType(ChessPieceType type) { m_type = type; }
    void            setColor(ChessPieceColor color) { m_color = color; }
    ChessPieceColor getColor() const { return m_color; }
    char            getColorChar()const; //retorna el color com a char {Blanca => w, Negra => b} (per mètode toString de chessboard)
    ChessPieceType  getType() const { return m_type; }
    bool            getValidPos() const { return m_validPos; }
    void            setvalidPos(bool b) { m_validPos = b; }
    char            typeToChar()const; //retorna el caracter corresponent al tipus de la peça

    void            render(int posX, int posY);
private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;
    bool            m_validPos; //True si la peça seleccionada es pot moure a aquesta posicio(mostra en quadrat verd)
    
};

ChessPieceType charToType(char c); //retorna el tipus de peça corresponent al caracter del parametre
#endif /* Piece_hpp */
