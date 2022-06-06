//
//  Piece.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Piece.hpp"
#include <string>
#include <iostream>
#include "../GraphicManager.h"

char Piece::getColorChar() const
{
	char c='_';
	if (m_color == CPC_White)
	{
		c = 'w';
	}
	else
	{
		if (m_color == CPC_Black)
		{
			c = 'b';
		}
	}

	return c;
}

char Piece::typeToChar() const
{
    char c;
	switch (m_type)
	{
	case CPT_King:
		c = 'R';
		break;
	case CPT_Queen:
		c = 'D';
		break;
	case CPT_Rook:
		c = 'T';
		break;
	case CPT_Bishop:
		c = 'A';
		break;
	case CPT_Knight:
		c = 'C';
		break;
	case CPT_Pawn:
		c = 'P';
		break;
	default:
		c = '_';
		break;
	}
	return c;
}


void Piece::render(int posX, int posY)
{
	/*if (m_type!=CPT_EMPTY)*/
	{
		IMAGE_NAME NAME;
		ChessPieceColor color = m_color;
		switch (m_type)
		{
		case CPT_King:
			if (color == CPC_White)
				NAME = IMAGE_PIECE_KING_WHITE;
			else
				NAME = IMAGE_PIECE_KING_BLACK;
			break;
		case CPT_Queen:
			if (color == CPC_White)
				NAME = IMAGE_PIECE_QUEEN_WHITE;
			else
				NAME = IMAGE_PIECE_QUEEN_BLACK;
			break;
		case CPT_Rook:
			if (color == CPC_White)
				NAME = IMAGE_PIECE_ROOK_WHITE;
			else
				NAME = IMAGE_PIECE_ROOK_BLACK;
			break;
		case CPT_Bishop:
			if (color == CPC_White)
				NAME = IMAGE_PIECE_BISHOP_WHITE;
			else
				NAME = IMAGE_PIECE_BISHOP_BLACK;
			break;
		case CPT_Knight:
			if (color == CPC_White)
				NAME = IMAGE_PIECE_KNIGHT_WHITE;
			else
				NAME = IMAGE_PIECE_KNIGHT_BLACK;
			break;
		case CPT_Pawn:
			if (color == CPC_White)
				NAME = IMAGE_PIECE_PAWN_WHITE;
			else
				NAME = IMAGE_PIECE_PAWN_BLACK;
			break;
		default:
			if (m_validPos)
			{
				NAME = IMAGE_VALID_POS;
			}
			else
			{
				NAME = IMAGE_NUM_MAX;
			}
			
			break;
		}
		GraphicManager::getInstance()->drawSprite(NAME, posX, posY);
		if (m_validPos && m_type!=CPT_EMPTY)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, posX, posY);
		}
	}
}



ChessPieceType charToType(char c)
{
	ChessPieceType t;
	switch (c)
	{
	case 'R':
		t = CPT_King;
		break;
	case 'D':
		t = CPT_Queen;
		break;
	case 'T':
		t = CPT_Rook;
		break;
	case 'A':
		t = CPT_Bishop;
		break;
	case 'C':
		t = CPT_Knight;
		break;
	case 'P':
		t = CPT_Pawn;
		break;
	default:
		t = CPT_EMPTY;
		break;
	}
	return t;
}



