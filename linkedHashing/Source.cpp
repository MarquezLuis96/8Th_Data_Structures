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
#include <string>
#include <cstdlib>

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
			nextElement = NULL;
		}
		 
		//Constructor sobrecargado 1 (recibe un int que ser� el n�mero del elemento)
		Element(int n) {
			number = n;
			nextElement = NULL;
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

	private:
		//Funci�n hash, se usa el m�todo de la multiplicaci�n, retorna la direcci�n de hash
		int hashFunction(long key) {
			double R = 0.618034;	//R: Constante para calcular el hash. El valor es inverso al numero �ureo.
			double d;				//d: Es la parte decimal de la multiplicaci�n por R.
			int hx;					//hx: ser� donde se almacene el hash generado por el m�todo de la multiplicaci�n.

			d = ((key * R) - (floor(R * key)));	//Se obtiene la parte decimal.
			hx = (int)(d * m);					//C�lculo del hash (parte decimal * tama�o de tabla).
			
			return hx;
		}

		//Pide la confirmaci�n para realizar una eliminaci�n
		bool confirm(int key) {
			char opc;

			while (true) {
				cout << "Seguro que desea eliminar la clave K = " << key << "? (s/n): ";
				cin >> opc; cout << endl;

				if (opc == 'n' || opc == 'N') {
					return false;
				}

				if (opc == 's' || opc == 'S') {
					return true;
				}
				else {
					cout << "Error: Ha ingresado una opcion invalida. Intente de nuevo..." << endl;
				}
			}
		}

	public:
		//Constructor de clase, recibe el tama�o de la tabla
		HashTable(int size) {
			hashTable = (new Element* [size]);		//Asignaci�n din�mica de memoria para el tama�o de tabla.
			m = size;								//Se le especifica el tama�o que tendr� la tabla.

			//Se inicializan todas las posiciones de las claves k de la tabla hash en NULL.
			for (int k = 0; k < m; k++) {
				hashTable[k] = NULL;
			}
			
			nElements = 0;		//Se especifica que no hay elementos ingresados a la tabla.
		}

		//Retorna el tama�o de la tabla
		int getM() {
			return m;
		}

		//Retorna el n�mero de elementos ingresados a la tabla
		int getNElements() {
			return nElements;
		}

		Element** getHashTable() {
			return hashTable;
		}

		//Busca un elemento, si lo encuentra lo retorna, si no lo encuentra retorna null
		Element* searchEToReturn(int key) {
			Element* p = NULL;
			int position;

			position = hashFunction(key);

			if (hashTable[position] != NULL) {
				p = hashTable[position];

				while (p->getNextElement() != NULL && p->getNumber() != key) {
					p = p->getNextElement();

					if (p->getNumber() != key && p->getNextElement() == NULL) {
						return NULL;
					}
				}
			}

			return p;
		}

		//Busca la posici�n dentro de la tabla del elemento pasado como argumento.
		// Esta funcion busca solo para insertar, para retornar usaremos searchEReturn
		// que es muy parecida pero retorna null cuando no se encuentra la clave,
		//esta en cambio retorna el ultimo elemento
		Element* searchEToInsert(int key) {
			Element* p = NULL;
			int position;

			position = hashFunction(key);

			if (hashTable[position] != NULL) {
				p = hashTable[position];

				while (p->getNextElement() != NULL && p->getNumber() != key) {
					p = p->getNextElement();

					/*if (p->getNumber() != key && p->getNextElement() == NULL) {
						return NULL;
					}*/
				}
			}

			return p;
		}

		//Inserta el elemento que recibe como argumento dentro de la tabla hash
		bool insertE(Element elem) {
			int hx;					//Hash generado por la funci�n hash, ser� la posici�n dentro del arreglo.
			Element* newE;			//newE: Nuevo Elemento a insertar.
			Element* p;				//Almacenar� el elemento si este se encuentra en la tabla.

			hx = hashFunction(elem.getNumber());

			p = searchEToInsert(elem.getNumber());				//Se busca el la posicion dentro del arreglo en la que se encuentra o no elem.

			if (!p) {									//Si la posici[on est� vac�a seentra ac� y se inserta el primer nodo de esa pos. de la tabla.
				newE = new Element(elem);				//Se genera una nueva direcci�n de memoria para newE.
				newE->setNextElement(hashTable[hx]);	//Se enlaza el elemento con el apuntador de la posici�n en la cual se almacenar�.
				hashTable[hx] = newE;					//Se ingresa en la posici�n hx el nuevo elemento.
				nElements++;							//Se incrementa el n�mero de elementos ingresados a la tabla.
			}
			else {										//Se entra ac� si ya en la pos del arreglo que marca la clave hay al menos un nodo.
				
				if (p->getNumber() == elem.getNumber()) {
					//cout << "Error: No se puede ingresar la clave K = " << elem.getNumber() << " porque ya se encuentra en la tabla." << endl;
					return false;
				}
				else {
					Element* current = p;
					if (current->getNextElement() == NULL && current->getNumber() != elem.getNumber()) {
						newE = new Element(elem);
						newE->setNextElement(NULL);
						current->setNextElement(newE);
						nElements++;
					}
				}
			}

			return true;
		}

		//Elimina el elemento pasado como argumento de la tabla.
		void deleteE(int key) {
			int position;

			position = hashFunction(key);

			if (hashTable[position] != NULL) {
				Element* previous;
				Element* current;

				previous = NULL;
				current = hashTable[position];

				while (current->getNextElement() != NULL && current->getNumber() != key) {
					previous = current;
					current = current->getNextElement();
				}

				if (current->getNumber() != key) {
					cout << "Error: La clave K = " + to_string(key) + " no se encuentra en la tabla." << endl;
				}
				else {
					if (confirm(current->getNumber())) {
						if (previous == NULL) {
							hashTable[position] = current->getNextElement();
						}
						else {
							previous->setNextElement(current->getNextElement());
						}
						delete current;
						nElements--;
					}
					else {
						//no se elimina la clave
					}
				}
			}
			else {
				cout << "Error: Posibles errores:\n1)La clave K = " + to_string(key);
				cout << " no se encuentra en la tabla.\n2)La posicion" << position<< " en el arreglo esta vacia." << endl;
			}
		}
};

void randomNumbersGeneration(int maxNumbers, HashTable table) {
	int randomNumber;
	for (int i = 0; i < maxNumbers; i++) {
		randomNumber = 0 + rand() % maxNumbers;

		/*
			Si el n�mero generado ya se encuentra en la tabla
			Se busca otro n�mero.
			Ojo: Solo si es el mismo n�mero, si hay colisiones con
			otros n�meros se agrega sin problemas.
		*/

		while (!table.insertE(randomNumber)) {
			randomNumber = 0 + rand() % maxNumbers;
		}
	}

	cout << "Se han agregado exitosamente " << maxNumbers << " numeros en el rango [0," << maxNumbers << "] a la tabla hash." << endl;
}

int countNodes(Element* list) {
	Element* p = list;
	int nNodes = 0;

	if (p != NULL) {
		nNodes++;

		while (p->getNextElement() != NULL) {
			nNodes++;
			p = p->getNextElement();
		}
	}

	return nNodes;
}

void countCollisions(HashTable table) {
	int maxCollisions = 0;	//El mayor n�mero de colisiones
	int posCollisions = 0;	//La posici�n del elemento con el mayot num de colisiones
	int currCollisions = 0;	//Colisiones Actuales
	int m = table.getM();
	
	for (int i = 0; i < m; i++) {
		currCollisions = countNodes(table.getHashTable()[i]);
		if (currCollisions > maxCollisions) {
			maxCollisions = currCollisions;
			posCollisions = i;
		}
	}

	cout << "La posicion dentro de la tabla con el mayor numero de colisiones es: " << posCollisions << endl;
	cout << "teniendo " << maxCollisions << " colisiones" << endl;
}

//Funci�n principal
int main(int args, char* argsv[]) {

	HashTable tabla(5);

	//randomNumbersGeneration(tabla.getM(), tabla);

	Element e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11;

	e1.setNumber(2);
	e2.setNumber(5);
	e3.setNumber(6);
	e4.setNumber(8);
	e5.setNumber(7);
	e6.setNumber(4);
	e7.setNumber(9);
	e8.setNumber(4);
	e9.setNumber(11);
	e10.setNumber(12);
	e11 = e10;

	tabla.insertE(e1);
	tabla.insertE(e2);
	tabla.insertE(e3);
	tabla.insertE(e4);
	tabla.insertE(e5);
	tabla.insertE(e6);
	tabla.insertE(e7);
	tabla.insertE(e8);
	tabla.insertE(e9);
	tabla.insertE(e10);
	tabla.insertE(e11);
	cout << "Elementos insertados en la tabla... " << endl;

	countCollisions(tabla);

	/*tabla.deleteE(1);
	tabla.deleteE(2);
	tabla.deleteE(5);
	tabla.deleteE(6);
	tabla.deleteE(8);
	tabla.deleteE(7);
	tabla.deleteE(4);
	tabla.deleteE(9);
	tabla.deleteE(4);
	tabla.deleteE(11);
	tabla.deleteE(12);
	cout << "Elementos eliminados de la tabla... " << endl;*/

	return 0;
}