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
    m_mode = GM_NONE;
    m_movements = QueueMovements();
    m_board = Chessboard();
}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    m_mode = mode;
    m_movementsFile = movementsFile;
    m_board.LoadBoardFromFile(intitialBoardFile);

    if (mode == GM_REPLAY)
    {
        
        //Creacio cua
        //QueueMovements _cua; //No hace falta
        
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

            file >> pos_Inicial >> pos_Final;
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

                //Afegim node (contingut: objecte Movement) a la cua
                m_movements.afegeix(mov);

            }
            
        }
    }
    else
    {
        if (mode == GM_NORMAL)
        {
            m_torn = CPC_White;
            
        }
    }
    
}


void CurrentGame::canviaTorn()
{
    if (m_torn==CPC_White)
    {
        m_torn = CPC_Black;
    }
    else
    {
        if (m_torn==CPC_Black)
        {
            m_torn = CPC_White;
        }
    }
}

bool CurrentGame::comprovaFinalPartida() const
{
    int comptaReis = 0;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            ChessPosition p(i, j);
            if (m_board.GetPieceTypeAtPos(p) == CPT_King)
                comptaReis++;
        }
    }

    return comptaReis<2;
}

void CurrentGame::end()
{
   
    if (m_mode == GM_NORMAL)
    {
        Movement aux;

        //Opertura fitxer movementsFile
        ofstream fitxer;
        fitxer.open(m_movementsFile);

        if (fitxer.is_open())
        {
            while (!m_movements.esBuida())
            {
                aux = m_movements.getPrimer();

                //Escriptura al fitxer movements File
                fitxer << (aux.getInicial()).toString() << " " << (aux.getFinal()).toString() << endl;

                //Eliminem Movement de la cua
                m_movements.treu();
            }
            fitxer.close();
        }
    }
    else
    {
        if (m_mode == GM_REPLAY)
        {
            
            ~QueueMovements();
        }
    }

}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{

    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    m_board.render();

    // Texte del torn
    int posTextX = CELL_INIT_X-20;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 140;
    string s;

    if (m_torn==CPC_Black)
        s = "Black";
    else
        if (m_torn==CPC_White)
            s = "White";
  
    std::string msg = "Turn: " + s;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 1, msg);

    //Texte del mode de joc
    posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 70;
    if (m_mode == GM_NORMAL)
        s = "Normal Play";
    else
    {
        if (m_mode == GM_REPLAY)
            s = "RePlay";
    }
        
    msg = "Game Mode: " + s;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 1, msg);


    if ((mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
        (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
        (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS))  && (!m_partidaFinalitzada))
    {
        int i = (mousePosX / CELL_W) -1, j =(((mousePosY / CELL_H) - 1) * -1) + 7;
       
        if (m_mode == GM_NORMAL)
        {
            ChessPosition pRat; //ChessPosition amb la posicio del ratoli
            VecOfPositions v;
            pRat.setPosX(i);
            pRat.setPosY(j);

            if (mouseStatus)
            {
                if (m_torn == m_board.GetPieceColorAtPos(pRat) || m_board.getPosValida(pRat))
                {
                    if (m_board.getPosValida(pRat))
                    {
                        m_board.MovePiece(m_board.getPieceSeleccionada(), pRat);
                        Movement m(m_board.getPieceSeleccionada(), pRat);
                        m_movements.afegeix(m);
                        if (comprovaFinalPartida())
                        {
                            m_partidaFinalitzada = true;
                        }
                        m_board.carregaPosValides(v); // Com que v es buit, es resetejen les posicions valides
                        canviaTorn();
                    }
                    m_board.setPieceSeleccionada(pRat);
                    v = m_board.GetValidMoves(pRat);
                    m_board.carregaPosValides(v);
                }
                else
                {
                    m_board.carregaPosValides(v);
                }
            }

        }
        if (m_mode==GM_REPLAY)
        {
            if (mouseStatus)
            {
                Movement m = m_movements.getPrimer();
                ChessPosition posTo = m.getFinal(), posFrom = m.getInicial();
                m_board.MovePiece(posFrom, posTo);
                m_movements.treu();
            }
           
        }
    }
    if (m_partidaFinalitzada)
    {
        ChessPieceColor colorGuanyador=CPC_NONE;
        int i = 0, j = 0;
        while (colorGuanyador==CPC_NONE && i<NUM_ROWS)
        {
            j = 0;
                while (colorGuanyador==CPC_NONE && j<NUM_COLS)
                {
                    ChessPosition p(i, j);
                    if (m_board.GetPieceTypeAtPos(p)==CPT_King)
                    {
                        colorGuanyador = m_board.GetPieceColorAtPos(p);
                    }
                    j++;
                }
                i++;
        }
        posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 200;
        if (colorGuanyador == CPC_Black)
            s = "Black";
        else
            if (colorGuanyador == CPC_White)
                s = "White";
        std::string msg = "Winner: " + s;
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 1, msg);
        VecOfPositions vBuit;
        m_board.carregaPosValides(vBuit);
    }

    return m_partidaFinalitzada;
}

    


    

