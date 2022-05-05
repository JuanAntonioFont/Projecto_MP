//
//  Chessboard.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"



class Chessboard {

public:
    Chessboard();
    
    void            LoadBoardFromFile(const string& path);
    VecOfPositions  GetValidMoves (const ChessPosition& pos) const;
    bool            MovePiece (const ChessPosition& posFrom, const ChessPosition& posTo);
    string          ToString () const;

    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;
    
private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    void            comprovaHorVer(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color) const;
    void            comprovaDiagonals(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color) const;
    void            comprovacio(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color, int mod_x, int mod_y) const;
    void            transformaPeo(ChessPosition p);
};


#endif /* Chessboard_hpp */
