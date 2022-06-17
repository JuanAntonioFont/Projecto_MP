#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"
#include "ChessPosition.hpp"



class Chessboard {

public:
    Chessboard();
    
    void            LoadBoardFromFile(const string& path);
    VecOfPositions  GetValidMoves (const ChessPosition& pos) const;
    bool            MovePiece (const ChessPosition& posFrom, const ChessPosition& posTo);
    string          ToString () const;

    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType  GetPieceTypeAtPos(const ChessPosition& pos) const;
    void            carregaPosValides(VecOfPositions v);
    void            setPieceSeleccionada(ChessPosition p) { m_pieceSeleccionada.setPosX(p.getPosX()); m_pieceSeleccionada.setPosY(p.getPosY()); }
    ChessPosition   getPieceSeleccionada() { return m_pieceSeleccionada; }const
    bool            getPosValida(const ChessPosition p) { return m_board[p.getPosY()][p.getPosX()].getValidPos(); }const

    
    void            render();

private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    ChessPosition m_pieceSeleccionada;      //Posicio de la peça on s'ha fet click

    void            comprovaHorVer(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color) const;
    void            comprovaDiagonals(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color) const;
    void            comprovacio(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color, int mod_x, int mod_y) const;
    void            transformaPeo(ChessPosition p);
};

int             getGraphicPosX(int i);  //retorna la posico X de la posicio i per utilitzar el GraphicManager
int             getGraphicPosY(int i);  //retorna la posico Y de la posicio i per utilitzar el GraphicManager
#endif /* Chessboard_hpp */
