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
    void            end();  
    
    
    
private:
    Chessboard m_board;
    QueueMovements m_movements;
    GameMode m_mode;
};

#endif /* CurrentGame_hpp */ 
//
