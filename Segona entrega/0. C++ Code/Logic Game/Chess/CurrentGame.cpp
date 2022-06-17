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
    m_board = Chessboard();
}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    m_mode = mode;
    m_torn = CPC_White;
    m_board.LoadBoardFromFile(intitialBoardFile);
    m_mouseStatusFrameCounter = 0;

    if (mode == GM_REPLAY)
    {
        
        
        //Lectura arxiu MOVEMENTSFILE
        ifstream file;
        file.open(movementsFile);

        while (!file.eof())
        {
            //Creacio "Movement" per guardar a cua
            Movement mov;

            //Variables per lectura arxius
            string pos_Inicial, pos_Final;

            //Lectura arxiu
            file >> pos_Inicial >> pos_Final;


            int row, column;
            if (!pos_Inicial.empty())   //Comprovacio arxiu no �s buit
            {
                ChessPosition aux_from;
                column = CharToCol(pos_Inicial[0]); //Conversio char del string en numero (metode global de ChessPosition)
                row = CharToRow(pos_Inicial[1]); //Conversio char del string en numero (metode global ChessPosition)
                aux_from.setPosX(column); //Assignacio valor de la columna   
                aux_from.setPosY(row); //Assignacio valor de la fila


                mov.setInicial(aux_from);   //Asignaci� valor del atribut setInicial (classe Movement)
                
                ChessPosition aux_to;
                column = CharToCol(pos_Final[0]); //metode global de ChessPosition
                row = CharToRow(pos_Final[1]); //metode global ChessPosition
                aux_to.setPosX(column);
                aux_to.setPosY(row);

                mov.setFinal(aux_to);   //Asignaci� valor del atribut setFinal (classe Movement)

                //Afegim node (contingut: objecte Movement) a la cua
                m_movements.afegeix(mov);

            }
            
        }
    }
    else
    {
        if (mode == GM_NORMAL)
        {
            m_movementsFile = movementsFile;
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
            while (!m_movements.esBuida())  //Comprovaci� cua es buida
            {
                aux = m_movements.getPrimer();  //Guardem valor del primer node (== Movement)

                //Escriptura al fitxer movements File
                fitxer << (aux.getInicial()).toString() << " " << (aux.getFinal()).toString() << endl;

                //Eliminem Movement de la cua
                m_movements.treu();
            }
            fitxer.close();
        }
    }

}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    // Mostra el tauler y les pe�es
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    m_board.render();

    // Mostra el text de qui te el torn

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

    //Mostra el text de en quin mode de joc estem

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

    // Comprovem si el ratoli esta dins dels limits del tauler
     
    if ((mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
        (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
        (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS))  && (!m_partidaFinalitzada))
    {
       

       // En mode normal
        if (m_mode == GM_NORMAL)
        {
            // Capturem la posici� X e Y de la casella on es troba el ratoli
            int mouseCellX = (mousePosX / CELL_W) - 1, mouseCellY = (((mousePosY / CELL_H) - 1) * -1) + 7;

            ChessPosition pRat(mouseCellX, mouseCellY); //ChessPosition amb la posicio del ratoli
            VecOfPositions v;                           // VecOfPositions amb posicions valides

            // Comprovem si hem fet click
            if (mouseStatus)
            {
                // Comrpbem si la casella on es fa click es del color de qui te el torn o si es una posico valida per moure la pe�a seleccionada
                if (m_torn == m_board.GetPieceColorAtPos(pRat) || m_board.getPosValida(pRat))
                {
                    //Si es fa click a una posicio valida per moure la pe�a seleccionada
                    if (m_board.getPosValida(pRat))
                    {
                        //Mou la pe�a
                        m_board.MovePiece(m_board.getPieceSeleccionada(), pRat);

                        //Crea un Movement del moviment que s'acaba de fer y es guarda a m_movements
                        Movement m(m_board.getPieceSeleccionada(), pRat);
                        m_movements.afegeix(m);

                        //Comprovem si s'ha acabar la partida
                        if (comprovaFinalPartida())
                        {
                            m_partidaFinalitzada = true;
                        }

                        m_board.carregaPosValides(v); // En aquest punt v no conte cap posicio y per tant es buit, resetejant les posicions valides
                        canviaTorn();
                    }

                    // Seleccionem la pe�a de la casella on s'ha fet click i guardem les posicions valides on es pot moure en v
                    m_board.setPieceSeleccionada(pRat);
                    v = m_board.GetValidMoves(pRat);

                    // Carreguem les posicions valides a m_board (aix� ens mostrara els quadrats verds quan es cridi al render de pice)
                    m_board.carregaPosValides(v);
                }
                // Si es fa click en una posicio que no sigui del color de qui te el torn ni una posicio valida
                else
                {
                    // Carrega v (que en aquest punt esta buit) resetejant les posicions valides
                    m_board.carregaPosValides(v);
                }
            }

        }
        // En mode replay
        if (m_mode==GM_REPLAY)
        {
            // Si es fa click
            if (mouseStatus)
            {
                //Comprovem que m_movements no sigui buida i evitem entrar al if mentre el ratoli continui apretat (comptem les vegades que es pasa per
                //updateAndRender mentre mouseStatus=true)
                if (m_mouseStatusFrameCounter<1 && !m_movements.esBuida())
                {
                    //Extreiem les posicions de m_movements i efectuem el moviment
                    Movement m = m_movements.getPrimer();
                    ChessPosition posTo = m.getFinal(), posFrom = m.getInicial();
                    m_board.MovePiece(posFrom, posTo);
                    canviaTorn();
                    // Treiem el moviment de m_movements i incrementem el comptador
                    m_movements.treu();
                    m_mouseStatusFrameCounter++;
                }
                
                
            }
            //Si el comtador no es 0 i s'ha deixat de fer click resetejem el comptador
            if (m_mouseStatusFrameCounter > 0 && !mouseStatus)
            {
                m_mouseStatusFrameCounter = 0;
            }

            //Quan m_movements sigui buida acabem la partida
            if (m_movements.esBuida())
            {
                m_partidaFinalitzada = true;
            }
        }
    }

    //Si la partida ha finalitzat
    if (m_partidaFinalitzada)
    {
        //Comptem els reis que hi ha al tauler guardant el color de l'ultim que hem trobat
        ChessPieceColor colorGuanyador = CPC_NONE;
        int reis=0;
        for (int i = 0; i < NUM_COLS; i++)
        {
            for (int j = 0; j < NUM_ROWS; j++)
            {
                ChessPosition p(i, j);
                if (m_board.GetPieceTypeAtPos(p)==CPT_King)
                {
                    colorGuanyador = m_board.GetPieceColorAtPos(p);
                    reis++;
                }
            }
        }

        posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 200;

        // Si hi ha menys de 2 reis, el color del rei que hi ha al tauler es el jugador guanyador
        if (reis < 2)
        {
            if (colorGuanyador == CPC_Black)
                s = "Winner: Black";
            else
                if (colorGuanyador == CPC_White)
                    s = "Winner: White";
        }
        //Si hi ha 2 (o mes), sabent que la partida ha acabat podem dir que estem a GM_REPLAY i m_movemets es buida
        else
            s = "No more moves to play";
        
        
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 1, s);

        // resetejem les posicions valides per treure cualsevol quadrat verd que pugi quedar
        VecOfPositions vBuit;
        m_board.carregaPosValides(vBuit);
    }
    //Retornem si la partida ha acabat
    return m_partidaFinalitzada;
}

    


    

