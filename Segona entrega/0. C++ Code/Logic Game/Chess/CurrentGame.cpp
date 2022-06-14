//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "Chessboard.hpp"
#include "QueueMovements.hpp"
#include "../GraphicManager.h"
#include <fstream>



CurrentGame::CurrentGame()
{

}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    m_board.LoadBoardFromFile(intitialBoardFile);
    if (mode == GM_REPLAY)
    {
        //Creacio cua
        QueueMovements cua;

        
        //Lectura arxiu MOVEMENTSFILE
        ifstream file;
        file.open(movementsFile);

        while (!file.eof())
        {
            //Creacio "Movement" per guardar a cua
            Movement mov;
            //Variables per leectura arxius
            string pos_Inicial, pos_Final;
            char blank; //Espai en blanc
            file >> pos_Inicial >> blank >> pos_Final  ;
            int row, column;
            if (!pos_Inicial.empty())
            {
                ChessPosition aux_from;
                column = CharToCol(pos_Inicial[0]); //metode global de ChessPosition
                row = CharToRow(pos_Inicial[1]); //metode global ChessPosition
                aux_from.setPosX(column);
                aux_from.setPosY(row);

               
                mov.setInicial(aux_from);

                ChessPosition aux_to;
                column = CharToCol(pos_Final[0]); //metode global de ChessPosition
                row = CharToRow(pos_Final[1]); //metode global ChessPosition
                aux_to.setPosX(column);
                aux_to.setPosY(row);

                mov.setFinal(aux_to);

                //Agefim node (contingut: Moviment) a la cua
                cua.afegeix(mov);

            }

    }
    else
    {
        if (mode == GM_NORMAL)
        {

        }
    }
    
}


void CurrentGame::end()
{
    
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    m_board.render();

    if ((mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
        (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
        (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
    {
        int i = (mousePosX / CELL_W) -1, j =(((mousePosY / CELL_H) - 1) * -1) + 7;

        int posTextX2 = CELL_INIT_X;
        int posTextY2 = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 80;
        string si, sj;
        si = i +'0';
        sj = j + '0';
        std::string msg = "PosX: " + si + ", PosY: " + sj;
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX2, posTextY2, 0.8, msg);


        ChessPosition pRat; //ChessPosition amb la posicio del ratoli
        VecOfPositions v;
        pRat.setPosX(i);
        pRat.setPosY(j);
        
        if (mouseStatus)
        {
            if (m_board.getPosValida(pRat))
            {
                m_board.MovePiece(m_board.getPieceSeleccionada(), pRat);
                m_board.carregaPosValides(v);
                
            }
            else
            {
                m_board.setPieceSeleccionada(pRat);
                v = m_board.GetValidMoves(pRat);
                m_board.carregaPosValides(v);
            }
            
        }

        if (mouseStatus /*&& !(m_board.getPieceSeleccionada() == p)*/)
        {
            
        }

        
    }

    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);


    return false;

}

