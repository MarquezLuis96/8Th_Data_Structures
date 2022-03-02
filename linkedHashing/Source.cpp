/*
* Programa:
* 
*				Determinar la lista enlazada m�s larga (mayor n�mero de nodos)
*	cuando se utiliza una tabla hash enlazada para guardar 1.000
*	n�meros enteros generados aleatoriamente. Escribir un programa
*	que realice la tarea propuesta, considerar que el factor de carga
*	es 1.
*
* Integrantes:
*				Luis M�rquez		-	C.I: 25.687.494
*				Eliana Rodr�guez	-	C.I: 00.000.000
*
* Fecha: 03/03/2022
*/

//Librerias
#include <iostream>

//Declaraci�n de nombres de espacio
using namespace std;

class Element {
	private:
		int number;
		Element* nextElement;

	public:
		//Constructor b�sico (No recibe nada)
		Element() {
			number = NULL;
			nextElement = nullptr;
		}
		 
		//Constructor sobrecargado 1 (recibe un int que ser� el n�mero del elemento)
		Element(int n) {
			number = n;
			nextElement = nullptr;
		}

		//Establece el entero recibido como el n�mero del elemento
		void setNumber(int n) {
			number = n;
		}

		void setNextElement(Element* next) {
			nextElement = next;
		}

		int getNumber() {
			return number;
		}

		Element* getNextElement() {
			return nextElement;
		}
};

//Funci�n principal
int main(int args, char* argsv[]) {
	
	Element a, b, c;

	a.setNumber(1);
	b.setNumber(2);
	c.setNumber(3);

	a.setNextElement(&b);
	b.setNextElement(&c);

	cout << "Claves enlazadas" << endl;

	return 0;
}