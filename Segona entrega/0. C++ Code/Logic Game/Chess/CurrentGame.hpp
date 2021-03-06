//
//  CurrentGame.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include "GameInfo.h"
#include "Chessboard.hpp"
#include "QueueMovements.hpp"

using namespace std;



class CurrentGame {

public:
    CurrentGame();
    
    void            init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool			updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void            canviaTorn();
    bool            comprovaFinalPartida() const; //Retorna true si hi ha menys de 2 reis al tauler
    void            end();  
    
    
    
private:
    Chessboard m_board;
    QueueMovements m_movements;
    GameMode m_mode;
    ChessPieceColor m_torn;
    bool m_partidaFinalitzada;      //True si la partida ha acabat
    string m_movementsFile;         //Guarda el fitxer on s'han de guardar els moviments
    int m_mouseStatusFrameCounter;  //Compta les vegades que s'ha executat updateAndRender mentre el ratoli estaba apretat
};

#endif /* CurrentGame_hpp */ 
//
