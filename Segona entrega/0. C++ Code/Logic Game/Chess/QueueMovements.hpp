#include <iostream>
using namespace std;


class Movement
{
public:
	Movement();
	~Movement();
	void setInicial(const ChessPosition& inicial) { pos_inicial = inicial; }
	void setFinal(const ChessPosition & final) { pos_final = final; }


private:
	
	ChessPosition pos_inicial;	//posicio peca
	ChessPosition pos_final;
};

Movement::Movement()
{
}

Movement::~Movement()
{
}


class Node
{
public:
	Movement& getValor() { return m_valor; }
	Node* getNext() { return m_next; }
	void setValor(const Movement& valor) { m_valor = valor; }
	void setNext(Node* next) { m_next = next; }
private:
	Movement m_valor;
	Node* m_next;
};

class QueueMovements
{
public:
	void afegeix(Movement& valor);
	void treu();
	Movement& getPrimer() const { return m_primer->getValor(); }
	Movement& getUltim() const { return m_ultim->getValor(); }
	bool esBuida() const;
private:
	Node* m_primer;
	Node* m_ultim;
};


//CONSTRUCTOR
QueueMovements::QueueMovements()
{
	m_primer = nullptr;
	m_ultim = nullptr;
}

//DESTRUCTOR
QueueMovements::~QueueMovements()
{
	Node* aux = m_primer;
	Node* _aux;
	while (aux != nullptr)
	{
		_aux = aux;
		aux = aux->getNext();
		delete _aux;
	}
}


bool QueueMovements::esBuida() const
{
	bool buida = false;
	if (m_primer == nullptr)
	{
		buida = true;
	}

	return buida;
}

void QueueMovements::afegeix(Movement& valor)
{
	Node* nou_node;
	nou_node = new Node;
	nou_node->setValor(valor);
	nou_node->setNext(nullptr);
	
	if (esBuida())	//Si es el primer element de la cua
	{
		m_primer = nou_node;
		m_ultim = nou_node;
	}
	else
	{
		m_ultim->setNext(nou_node);
		m_ultim = nou_node;
	}
}


void QueueMovements::treu()
{
	if (!esBuida())
	{
		Node* aux = m_primer;
		
		if (m_primer == m_ultim)
		{
			m_primer = nullptr;
			m_ultim = nullptr;
		}
		else
		{
			m_primer = m_primer->getNext();
		}
		delete aux;
	}
}

