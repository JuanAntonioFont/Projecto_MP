#include<iostream>
#include"QueueMovements.hpp"

using namespace std;

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
	/*bool buida = false;
	if (m_primer == nullptr)
	{
		buida = true;
	}*/

	return m_primer == nullptr;
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

Movement::Movement()
{
	ChessPosition p;
	m_inicial = p;
	m_final = p;
}
