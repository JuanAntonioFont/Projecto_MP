#ifndef QueueMovements_hpp
#define QueueMovements_hpp


#include <iostream>
#include"ChessPosition.hpp"
using namespace std;


class Movement {

public:
	Movement();
	Movement(ChessPosition inicial, ChessPosition posFinal) { m_inicial = inicial; m_final = posFinal; }
	void setInicial(const ChessPosition& inicial) { m_inicial = inicial; }
	void setFinal(const ChessPosition& posFinal) { m_final = posFinal; }
	ChessPosition& getInicial() { return m_inicial ; }
	ChessPosition& getFinal() { return m_final ; }


private:
	
	ChessPosition m_inicial;	//posicio peca
	ChessPosition m_final;
};



class Node {

public:
	Movement& getValor() { return m_valor; }
	Node* getNext() { return m_next; }
	void setValor(const Movement& valor) { m_valor = valor; }
	void setNext(Node* next) { m_next = next; }
private:
	Movement m_valor;
	Node* m_next;
};

class QueueMovements {

public:
	QueueMovements();
	~QueueMovements();
	void afegeix(Movement& valor);
	void treu(); 
	Movement& getPrimer() const { return m_primer->getValor(); }
	Movement& getUltim() const { return m_ultim->getValor(); }
	bool esBuida() const;
private:
	Node* m_primer;
	Node* m_ultim;
};



#endif // QueueMovements_hpp