/*
* TestDato.h
*  
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*      
*  
*      
*      
*/   

#ifndef TESTDATO_H_
#define TESTDATO_H_

//testeo de clase Dato y DatoLibro
void testDato()
{
	DatoLibro* dato = new DatoLibro("PIRULO EL DEL BOSQUE!!!");

	cout<<dato->toCharPointer()<<endl;
	dato->vaciar();
	if (dato->estaVacio())
		cout<<"NO ESTA MAS!!";
	cout<<dato->toCharPointer();

	delete(dato);
}

void testPersistenciaNodoInterno()
{
	/*
	NodoInternoArbol* nodito = new NodoInternoArbol();

	list<string>* claves = new list<string>();
	claves->push_back("hola");
	claves->push_back("mundo");
	claves->push_back("cruel");

	nodito->setClaves(claves);

	list<int>* hijos = new list<int>();
	hijos->push_back(1);
	hijos->push_back(21);
	hijos->push_back(5);
	hijos->push_back(51);

	nodito->setHijos(hijos);



	DatoNodo* dato = new DatoNodo(nodito);

	string s = dato->getDato();
	cout <<s << endl;

	delete(hijos);
	delete(claves);
	delete(nodito);
	delete(dato);


    //Prueba de NodoInterno persistiendolo mediante DatoNodo
    //NodoInternoArbol* nodito = new NodoInternoArbol();
    list<int> hijos;
    hijos.push_front(2);
    hijos.push_front(3);
    hijos.push_front(5);

    list<string> claves;
    claves.push_front("casa");
    claves.push_front("travesti");
    claves.push_front("servetto");

   // nodito->setClaves(claves);
   // nodito->setHijos(hijos);

    //DatoNodo* datoNodo = new DatoNodo((NodoInternoArbol*)nodito);
     * */

}


void testSetHidratacionDatoElementoNodo()
{
	DatoElementoNodo* elemento 			= new DatoElementoNodo();
	DatoElementoNodo* elementoHidratado = new DatoElementoNodo();
	stringstream ss;

	elemento->setClave("Atlantida");
	elemento->agregarLibro((uint32_t)21);
	elemento->agregarLibro((uint32_t)22);
	elemento->agregarLibro((uint32_t)23);
	elemento->agregarLibro((uint32_t)24);
	elemento->agregarLibro((uint32_t)25);

	elemento->serializar(&ss);
	cout<<"SERIALIZACION: "<<elemento->getDato()<<endl;

	elementoHidratado->hidratar(&ss);
	cout<<"HIDRATADO Clave: "<<elementoHidratado->getClave()<<endl;

	list<uint32_t> aux = elementoHidratado->getLibros();
	for (list<uint32_t>::const_iterator ci = aux.begin(); ci != aux.end(); ++ci)
		cout<<"HIDRATADO IdLibros: "<<*ci<<endl;
}

#endif /* TESTDATO_H_ */
