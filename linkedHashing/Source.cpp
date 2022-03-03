/*
* Programa:
* 
*				Determinar la lista enlazada más larga (mayor número de nodos)
*	cuando se utiliza una tabla hash enlazada para guardar 1.000
*	números enteros generados aleatoriamente. Escribir un programa
*	que realice la tarea propuesta, considerar que el factor de carga
*	es 1.
*
* Integrantes:
*				Luis Márquez		-	C.I: 25.687.494
*				Eliana Rodríguez	-	C.I: 00.000.000
*
* Fecha: 03/03/2022
*/

//Librerias
#include <iostream>
#include<string>

//Declaración de nombres de espacio
using namespace std;

//Clase Element - Esta clase almacena el entero generado y el siguiente elemento generado
class Element {
	protected:
		int number;				//number: La clave o dato a almacenar en la tabla hash
		Element* nextElement;	//nextElement: Apunta al siguiente elemento de tipo Element (Lista)

	public:
		//Constructor básico (No recibe nada)
		Element() {
			number = NULL;
			nextElement = NULL;
		}
		 
		//Constructor sobrecargado 1 (recibe un int que será el número del elemento)
		Element(int n) {
			number = n;
			nextElement = NULL;
		}

		//Establece el entero recibido como el número del elemento
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

//Clase HashTable - Esta es la clase que generará los objetos de tipo tabla hash
class HashTable {
	protected:
		int nElements;			//nElements: Número de elementos ingresados a la tabla.
		int m;					//m: Número de elementos esperados - tamaño de tabla.
		Element** hashTable;	//hashTable: Doble apuntador al arreglo que representa la tabla hash.

	private:
		//Función hash, se usa el método de la multiplicación, retorna la dirección de hash
		int hashFunction(long key) {
			double R = 0.618034;	//R: Constante para calcular el hash. El valor es inverso al numero áureo.
			double d;				//d: Es la parte decimal de la multiplicación por R.
			int hx;					//hx: será donde se almacene el hash generado por el método de la multiplicación.

			d = ((key * R) - (floor(R * key)));	//Se obtiene la parte decimal.
			hx = (int)(d * m);					//Cálculo del hash (parte decimal * tamaño de tabla).
			
			return hx;
		}

		//Pide la confirmación para realizar una eliminación
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
		//Constructor de clase, recibe el tamaño de la tabla
		HashTable(int size) {
			hashTable = (new Element* [size]);		//Asignación dinámica de memoria para el tamaño de tabla.
			m = size;								//Se le especifica el tamaño que tendrá la tabla.

			//Se inicializan todas las posiciones de las claves k de la tabla hash en NULL.
			for (int k = 0; k < m; k++) {
				hashTable[k] = NULL;
			}
			
			nElements = 0;		//Se especifica que no hay elementos ingresados a la tabla.
		}

		//Busca la posición dentro de la tabla del elemento pasado como argumento.
		Element* searchE(int key) {
			Element* p = NULL;
			int position;

			position = hashFunction(key);

			if (hashTable[position] != NULL) {
				p = hashTable[position];

				while (p->getNextElement() != NULL && p->getNumber() != key) {
					p = p->getNextElement();

					if (p->getNumber() != key) {
						p = NULL;
					}
				}
			}

			return p;
		}

		//Inserta el elemento que recibe como argumento dentro de la tabla hash
		void insertE(Element elem) {
			int hx;					//Hash generado por la función hash, será la posición dentro del arreglo.
			Element* newE;			//newE: Nuevo Elemento a insertar.
			Element* p;				//Almacenará el elemento si este se encuentra en la tabla.

			hx = hashFunction(elem.getNumber());

			p = searchE(elem.getNumber());				//Se busca el la posicion dentro del arreglo en la que se encuentra o no elem.

			if (!p) {									//Si la posici[on está vacía seentra acá y se inserta el primer nodo de esa pos. de la tabla.
				newE = new Element(elem);				//Se genera una nueva dirección de memoria para newE.
				newE->setNextElement(hashTable[hx]);	//Se enlaza el elemento con el apuntador de la posición en la cual se almacenará.
				hashTable[hx] = newE;					//Se ingresa en la posición hx el nuevo elemento.
				nElements++;							//Se incrementa el número de elementos ingresados a la tabla.
			}
			else {										//Se entra acá si ya en la pos del arreglo que marca la clave hay al menos un nodo.
				Element* current = hashTable[hx];
				
				do {
					if (current->getNextElement() == NULL) {
						if (current->getNumber() != elem.getNumber()) {
							newE = new Element(elem);
							newE->setNextElement(NULL);
							current->setNextElement(newE);
							nElements++;
						}
						else {
							cout << "Error: No se puede ingresar la clave K = " << elem.getNumber() << " porque ya se encuentra en la tabla." << endl;
						}
					}
					else {
						if (current->getNextElement()->getNumber() == elem.getNumber()) {
							cout << "Error: No se puede ingresar la clave K = " << elem.getNumber() << " porque ya se encuentra en la tabla." << endl;
						}
					}

					current = current->getNextElement();
				} while (current->getNextElement() != NULL);
			}
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

//Función principal
int main(int args, char* argsv[]) {

	HashTable tabla(5);

	Element e1, e2, e3, e4, e5, e6, e7, e8, e9, e10;

	e1.setNumber(1);
	e2.setNumber(2);
	e3.setNumber(3);
	e4.setNumber(4);
	e5.setNumber(5);
	e6.setNumber(7);
	e7.setNumber(8);
	e8.setNumber(10);
	e9.setNumber(6);
	e10 = e9;

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
	cout << "Elementos insertados en la tabla... " << endl;

	tabla.deleteE(1);
	tabla.deleteE(2);
	tabla.deleteE(3);
	tabla.deleteE(4);
	tabla.deleteE(5);
	tabla.deleteE(5);
	tabla.deleteE(6);
	tabla.deleteE(7);
	tabla.deleteE(8);
	tabla.deleteE(9);
	tabla.deleteE(11);
	tabla.deleteE(10);
	cout << "Elementos eliminados de la tabla... " << endl;

	return 0;
}