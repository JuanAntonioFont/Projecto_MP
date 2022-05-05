//
//  Piece.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Piece.hpp"
#include <string>
#include <iostream>
using namespace std;

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


/*string Piece::pieceToString(const Piece& p) const
{
	
	string resultat;
	char type;
	resultat = p.getColorChar();
	type = p.typeToChar();



	resultat.push_back(type);

	return resultat;

}
*/
