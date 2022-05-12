//
//  Chessboard.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Chessboard.hpp"
#include "ChessPosition.hpp"
#include <iostream>
#include <fstream>

using namespace std;


//Inicialitzaci� del tauler sense pe�es 
Chessboard::Chessboard()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			m_board[i][j].setColor(CPC_NONE);
			m_board[i][j].setType(CPT_EMPTY);

		}
	}
}

void Chessboard::LoadBoardFromFile(const string& path)
{
	ifstream file;
	file.open(path);
	
	while (!file.eof())
	{
		int player;
		char separator;
		string s;
		file >> player >> separator >>s;
		int row, column;
		ChessPieceType type;
		if (!s.empty())
		{
			type = charToType(s[0]); //m�tode global de Piece
			column = CharToCol(s[1]); //m�tode global de ChessPosition
			row = CharToRow(s[2]); //m�tode global ChessPosition

			m_board[row][column].setType(type);
			if (player==0)
			{
				m_board[row][column].setColor(CPC_White);
			}
			else
			{
				if (player==1)
				{
					m_board[row][column].setColor(CPC_Black);
				}
			}

		}
		
	}
	file.close();
}

bool peoInicial(ChessPosition pos)  
{
	return (pos.getPosY() == 1) || (pos.getPosY() == 6);
	//DESCRIPCIO;
	//Aquesta funci� comprova si el pe� seleccionat es pot moure dos espais endavant. Sabent que els peons nomes es mouen endavant, nomes ens cal comprovar
	//si el pe� es trova a la seva posici� inicial. La distincio entre blanques i negres ya es fa indirectament abans de cridar la funci�.
	//(sempre que es crida aquesta funcio sabem que el tipus de casella de la posicio avaluada es un pe�)
	// 
	//PARAMETRES:
	//Es pasa com a parametre la posicio del tauler a evaluar.
	// 
	//RETORN:
	//Es retorna TRUE si el pe� es pot moure dues caselles, en cas contrari es retorna FALSE
}

VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos) const
{
	VecOfPositions posicions;
	ChessPieceType tipus = m_board[pos.getPosY()][pos.getPosX()].getType();
	ChessPieceColor color= m_board[pos.getPosY()][pos.getPosX()].getColor();
	ChessPosition p;
	int i, j;
	bool b = false;


	switch (tipus)
	{
	case CPT_King:
	{
		for (i = pos.getPosY() + 1; i >= pos.getPosY() - 1; i--)
		{
			for (j = pos.getPosX() - 1; j <= pos.getPosX() + 1; j++)
			{
				if ((i >= 0 && i <= 7) && (j >= 0 && j <= 7))
				{
					if (color != m_board[i][j].getColor())
					{
						p.setPosY(i);
						p.setPosX(j);
						posicions.push_back(p);
					}
				}
				
			}
		}

		break;
	}
	case CPT_Queen:
	{
		comprovaDiagonals(posicions, pos, color);
		comprovaHorVer(posicions, pos, color);
		break;
	}
	case CPT_Rook:
	{
		comprovaHorVer(posicions, pos, color);
		break;
	}
	case CPT_Bishop:
	{
		comprovaDiagonals(posicions, pos, color);
		break;
	}
	case CPT_Knight:
	{
		i = pos.getPosY(), j = pos.getPosX();

		if (m_board[i + 2][j - 1].getColor() != color && (i+2 >= 0 && i+2 <= 7) && (j-1 >= 0 && j-1 <= 7)) //superior dreta
		{
			p.setPosX(j - 1);
			p.setPosY(i + 2);
			posicions.push_back(p);
		}
		if (m_board[i + 2][j + 1].getColor() != color && (i+2 >= 0 && i+2 <= 7) && (j+1 >= 0 && j+1 <= 7)) //superior esquerra
		{
			p.setPosX(j + 1);
			p.setPosY(i + 2);
			posicions.push_back(p);
		}

		if (m_board[i - 2][j - 1].getColor() != color && (i-2 >= 0 && i-2 <= 7) && (j-1 >= 0 && j-1 <= 7)) //inferior dreta
		{
			p.setPosX(j - 1);
			p.setPosY(i - 2);
			posicions.push_back(p);
		}
		if (m_board[i - 2][j + 1].getColor() != color && (i-2 >= 0 && i-2 <= 7) && (j+1 >= 0 && j+1 <= 7)) //inferior esquqerra
		{
			p.setPosX(j + 1);
			p.setPosY(i - 2);
			posicions.push_back(p);
		}

		if (m_board[i + 1][j - 2].getColor() != color && (i+1 >= 0 && i+1 <= 7) && (j-2 >= 0 && j-2 <= 7)) //dreta superior
		{
			p.setPosX(j - 2);
			p.setPosY(i + 1);
			posicions.push_back(p);
		}
		if (m_board[i - 1][j - 2].getColor() != color && (i-1 >= 0 && i-1 <= 7) && (j-2 >= 0 && j-2 <= 7)) //dreta inferior
		{
			p.setPosX(j - 2);
			p.setPosY(i - 1);
			posicions.push_back(p);
		}

		if (m_board[i + 1][j + 2].getColor() != color && (i+1 >= 0 && i+1 <= 7) && (j+2 >= 0 && j+2 <= 7))//esquerra superior
		{
			p.setPosX(j + 2);
			p.setPosY(i + 1);
			posicions.push_back(p);
		}
		if (m_board[i - 1][j + 2].getColor() != color && (i-1 >= 0 && i-1 <= 7) && (j+2 >= 0 && j+2 <= 7))//esquerra inferior
		{
			p.setPosX(j + 2);
			p.setPosY(i - 1);
			posicions.push_back(p);
		}
		break;
	}
	case CPT_Pawn:
	{
		if (m_board[pos.getPosY()][pos.getPosX()].getColor() == CPC_White)
		{
			if (m_board[pos.getPosY()+1][pos.getPosX()-1].getColor()==CPC_Black) //moviments diagonals (superior esquerra)
			{
				p.setPosX(pos.getPosX()-1);
				p.setPosY(pos.getPosY() + 1);
				posicions.push_back(p);
			}
			if (m_board[pos.getPosY() + 1][pos.getPosX() + 1].getColor() == CPC_Black) //moviments diagonals (inferior dreta)
			{
				p.setPosX(pos.getPosX() + 1);
				p.setPosY(pos.getPosY() + 1);
				posicions.push_back(p);
			}


			if (peoInicial(pos)) //moviment doble del peo
			{
				if (m_board[pos.getPosY() + 1][pos.getPosX()].getColor() != color)
				{
					p.setPosX(pos.getPosX());
					p.setPosY(pos.getPosY() + 1);
					posicions.push_back(p);
					if (m_board[pos.getPosY() + 2][pos.getPosX()].getColor() != color)
					{
						p.setPosX(pos.getPosX());
						p.setPosY(pos.getPosY() + 2);
						posicions.push_back(p);
					}
				}
				
			}
			else
			{
				if (m_board[pos.getPosY() + 1][pos.getPosX()].getColor() != color)
				{
					p.setPosX(pos.getPosX());
					p.setPosY(pos.getPosY() + 1);
					posicions.push_back(p);
				}
			}
		}
		else
		{
			if (m_board[pos.getPosY()][pos.getPosX()].getColor() == CPC_Black)
			{
				if (m_board[pos.getPosY() - 1][pos.getPosX() - 1].getColor() == CPC_White) //moviments diagonals (inferior esquerra)
				{
					p.setPosX(pos.getPosX() - 1);
					p.setPosY(pos.getPosY() - 1);
					posicions.push_back(p);
				}
				if (m_board[pos.getPosY() - 1][pos.getPosX() + 1].getColor() == CPC_White) //moviments diagonals (inferior dreta)
				{
					p.setPosX(pos.getPosX() + 1);
					p.setPosY(pos.getPosY() - 1);
					posicions.push_back(p);
				}

				if (peoInicial(pos)) //moviment doble
				{
					if (m_board[pos.getPosY() - 1][pos.getPosX()].getColor() != color)
					{
						p.setPosX(pos.getPosX());
						p.setPosY(pos.getPosY() - 1);
						posicions.push_back(p);
						if (m_board[pos.getPosY() - 2][pos.getPosX()].getColor() != color)
						{
							p.setPosX(pos.getPosX());
							p.setPosY(pos.getPosY() - 2);
							posicions.push_back(p);
						}
					}
					
				}
				else
				{
					if (m_board[pos.getPosY() - 1][pos.getPosX()].getColor() != color)
					{
						p.setPosX(pos.getPosX());
						p.setPosY(pos.getPosY() - 1);
						posicions.push_back(p);
					}
				}
			}
		}
		break;
	}
	default:
		
		break;
	}
	return posicions;
}

void Chessboard::comprovaHorVer(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color) const
{
	comprovacio(posicions, pos, color, -1, 0);
	comprovacio(posicions, pos, color, 1, 0);
	comprovacio(posicions, pos, color, 0, 1);
	comprovacio(posicions, pos, color, 0, -1);
	//DESCRIPCIO:
	//Aquesta funcio comprova si les caselles al voltant de la pe�a seleccionada son valides. Nomes comprova les caselles en forma de + centrada a la posicio que es pasa 
	//com a parametre. Es comprova de forma radial en aquest ordre: esquerra, dreta, amunt, avall.
	//
	//PARAMETRES:
	//Es pasa com a parametre la posicio que s'ha d'evaluar, el vector de posicions per guardar les posicons valides i el color de la pe�a que s'evalua
	//
	//RETORN:
	//No es retorna res.
}

void Chessboard::comprovaDiagonals(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color) const
{
	 
	comprovacio(posicions, pos, color, -1, 1);
	comprovacio(posicions, pos, color, -1, -1);
	comprovacio(posicions, pos, color, 1, 1);
	comprovacio(posicions, pos, color, 1, -1);
	//DESCRIPCIO:
	//Aquesta funcio comprova si les caselles al voltant de la pe�a seleccionada son valides. Nomes comprova les caselles en forma de x centrada a la posico que es pasa 
	//con a parametre. Es comprova de forma radial en aquest ordre: dreta inferior, esquerra superior, esquerra inferior, dreta superior.
	//
	//PARAMETRES:
	//Es pasa com a parametre la posicio que s'ha d'evaluar, el vector de posicions per guardar les posicons valides i el color de la pe�a que s'evalua
	//
	//RETORN:
	//No es retorna res.
}
void Chessboard::comprovacio(VecOfPositions& posicions, const ChessPosition& pos, ChessPieceColor color, int mod_x, int mod_y) const
{
	int i=pos.getPosX()+mod_x, j=pos.getPosY()+mod_y;
	bool b=false;
	ChessPosition p;
	while ((i < NUM_COLS && i>=0) && (j < NUM_ROWS && j >= 0) && m_board[j][i].getColor() != color && !b)
	{
		if (color == CPC_Black)
		{
			if (m_board[j][i].getColor() == CPC_White)
			{
				b = true;
			}
		}
		else
		{
			if (color == CPC_White)
			{
				if (m_board[j][i].getColor() == CPC_Black)
				{
					b = true;
				}
			}
		}
		p.setPosX(i);
		p.setPosY(j);
		posicions.push_back(p);

		i += mod_x;
		j += mod_y;
	}
}
	//DESCRIPCIO:
	//Aquesta funcio evalua posicions per comprovar si son valides.Comrova si el color de la possicio es diferent al de la pe�a que s'evalua
	//o si la posicio es buida. S'evaluen el linia recta fins que alguna condicio no es compleix. Es pot indicar amb paramentres la direccio
	// de la recta.
	//
	//PARAMETRES:
	//Es pasa com a parametre la posicio que s'ha d'evaluar, el vector de posicions per guardar les posicons valides i el color de la pe�a que s'avalua
	//Tambe es pasen dos valors mod_x i mod_y que indiquen si s'ha de sumar, restar o no modificar els valors de x e y per la seguent iteraci�.
	// 
	//RETORN:
	//No es retorna res. La funcio modifica VecOfPositions de posicions valides directament.

void Chessboard::transformaPeo(ChessPosition p)
{
	char tipus;
	bool valid=false;
	ChessPieceColor color = m_board[p.getPosY()][p.getPosX()].getColor();
	switch (color)
	{
	case CPC_Black:
		if (p.getPosY() == 0)
			valid = true;
		break;
	case CPC_White:
		if (p.getPosY() == 7)
			valid = true;
		break;
	default:
		break;
	}
	if (valid)
	{
		cout << "Dama   - D" << endl;
		cout << "Torre  - T" << endl;
		cout << "Alfil  - A" << endl;
		cout << "Cavall - C" << endl;
		cout << "Introdueix lletra(MAJUSCULA): ";
		cin >> tipus;
		
		while (tipus!='D' && tipus!='T' && tipus!='A' && tipus!='C')
		{
			cout << "ERROR: Introdueix una lletra valida" << endl << endl;
			cout << "Dama   - D" << endl;
			cout << "Torre  - T" << endl;
			cout << "Alfil  - A" << endl;
			cout << "Cavall - C" << endl;
			cout << "Introdueix lletra: ";
			cin >> tipus;

		}
		
		m_board[p.getPosY()][p.getPosX()].setType(charToType(tipus));
	}

	//DESCRIPCIO:
	//
	// Un peo pot cridar aquesta funcio per comprovar si ha arribat a l'altra banda del tauler i transformar-se en una altra pe�a.
	// 
	//PARAMETRES:
	//Es pasa com a parametre la posici� del peo.
	// 
	//RETORN:
	//No es retorna res. La funcio tranforma el tipus de pe�a del peo si es nessecari.
}


bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	VecOfPositions posicionsVal=GetValidMoves(posFrom);
	bool posValida=false;
	int i=0;

	//Recorre el vector dels moviments v�lids d'una pe�a i compara amb la posici� desitjada est�
	while (posValida==false && i<posicionsVal.size())
	{
		if (posicionsVal[i]==posTo)
		{
			posValida = true;
		}
		i++;
	}
	if (posValida)
	{
		//Movem pe�a. Es donen els valors de color i tipus de posfrom a posTo i es deixa "en blanc" al posFrom
		m_board[posTo.getPosY()][posTo.getPosX()].setColor(m_board[posFrom.getPosY()][posFrom.getPosX()].getColor());
		m_board[posTo.getPosY()][posTo.getPosX()].setType(m_board[posFrom.getPosY()][posFrom.getPosX()].getType());

		m_board[posFrom.getPosY()][posFrom.getPosX()].setColor(CPC_NONE);
		m_board[posFrom.getPosY()][posFrom.getPosX()].setType(CPT_EMPTY);
	}
	//Si la pe�a es PE� em de comprovar si hem arribat al final del tauler per canviar la pe�a. Si es FALS no pasa res
	if (m_board[posTo.getPosY()][posTo.getPosX()].getType()==CPT_Pawn)
	{
		transformaPeo(posTo);
	}
	return posValida;
}

string infoCasella(Piece p)
{
	string s;
	s = p.getColorChar();
	s += p.typeToChar();

	return s;

	//DESCRIPCIO:
	//La funcio recull la informaci� d'una casella i la transforma en un string que fara servir la funci� toString. L'string es composa d'una lletra minuscula per al color
	//{blanca => w  negra => b} seguida d'una lletra majuscula per al tipus {consultar la taula del guio}
	//
	//PARAMETRES:
	//Es pasa com a par�metre la pe�a a avaluar.
	//
	//RETORN:
	//Es retorna un string amb la informaci� de la pe�a.
}

string Chessboard::ToString() const
{
	string s;
	for (int i = NUM_ROWS-1; i >= 0; i--)
	{
		s += (char)i+48+1; //guardem els nums de 8-1 
		for (int j = 0; j < NUM_COLS; j++)
		{
			s += " ";
			s += infoCasella(m_board[i][j]);
		}
		s += "\n";
	}
	s += "  a  b  c  d  e  f  g  h";

	return s;
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosY()][pos.getPosX()].getColor();
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosY()][pos.getPosX()].getType();
}

void Chessboard::render()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			int posX = m_board[i][j].getGraphicPosX(i);
			int posY = m_board[i][j].getGraphicPosY(j);
			m_board[j][i].render(posX, posY);
		}
	}
}
