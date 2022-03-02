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
#include<string>

//Declaraci�n de nombres de espacio
using namespace std;

//Clase Element - Esta clase almacena el entero generado y el siguiente elemento generado
class Element {
	protected:
		int number;				//number: La clave o dato a almacenar en la tabla hash
		Element* nextElement;	//nextElement: Apunta al siguiente elemento de tipo Element (Lista)

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

//Clase HashTable - Esta es la clase que generar� los objetos de tipo tabla hash
class HashTable {
	protected:
		int nElements;			//nElements: N�mero de elementos ingresados a la tabla.
		int m;					//m: N�mero de elementos esperados - tama�o de tabla.
		Element** hashTable;	//hashTable: Doble apuntador al arreglo que representa la tabla hash.

	public:
		//Constructor de clase, recibe el tama�o de la tabla
		HashTable(int size) {
			*hashTable = (new Element*) [size];		//Asignaci�n din�mica de memoria para el tama�o de tabla.
			m = size;								//Se le especifica el tama�o que tendr� la tabla.

			//Se inicializan todas las posiciones de las claves k de la tabla hash en NULL.
			for (int k = 0; k < m; k++) {
				hashTable[k] = NULL;
			}

			nElements = 0;		//Se especifica que no hay elementos ingresados a la tabla.
		}

		//Busca la posici�n dentro de la tabla del elemento pasado como argumento.
		Element* searchE(int key) {
			Element* p = nullptr;
			int position;

			position = hashFunction(key);

			if (hashTable[position] != NULL) {
				p = hashTable[position];

				while (p->getNextElement() != NULL && p->getNumber() != key) {
					p = p->getNextElement();

					if (p->getNumber() != key) {
						p = nullptr;
					}
				}
			}

			return p;
		}

		//Inserta el elemento que recibe como argumento dentro de la tabla hash
		void insertE(Element elem) {
			int hx;					//Hash generado por la funci�n hash, ser� la posici�n dentro del arreglo.
			Element* newE;			//newE: Nuevo Elemento a insertar.
			Element* p;				//Almacenar� el elemento si este se encuentra en la tabla.

			p = searchE(elem.getNumber());				//Se busca el elemento en la tabla para no insertar dos veces el mismo elemento.

			if (!p) {									//Se entra a ete condicional si p no fue encontrado en la tabla hash.
				newE = new Element(elem);				//Se genera una nueva direcci�n de memoria para newE.
				newE->setNextElement(hashTable[hx]);	//Se enlaza el elemento con el apuntador de la posici�n en la cual se almacenar�.
				hashTable[hx] = newE;					//Se ingresa en la posici�n hx el nuevo elemento.
				nElements++;							//Se incrementa el n�mero de elementos ingresados a la tabla.
			}
			else {
				//Mensaje de exception
				throw "Error: No se puede ingresar la clave K = " + to_string(elem.getNumber()) + " porque ya se encuentra en la tabla.";
			}
		}

		//Elimina el elemento pasado como argumento de la tabla.
		void deleteE() {
			//
		}

	private:
		//Funci�n hash, se usa el m�todo de la multiplicaci�n, retorna la direcci�n de hash
		int hashFunction(long key) {
			double R = 0.618034;	//R: Constante para calcular el hash. El valor es inverso al numero �ureo.
			double d;				//d: Es la parte decimal de la multiplicaci�n por R.
			int hx;					//hx: ser� donde se almacene el hash generado por el m�todo de la multiplicaci�n.

			d = ((key * R) - (floor(R * key)));	//Se obtiene la parte decimal.
			hx = (int)(d * m);					//C�lculo del hash (parte decimal * tama�o de tabla)
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