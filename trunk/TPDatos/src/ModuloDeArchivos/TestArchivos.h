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

#ifndef TESTARCHIVO_H_
#define TESTARCHIVO_H_
void cargarLibros(ArchivoLibro* arcReg, ArchivoControlLibro* arcControl)
{
	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - Cell.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - Historias fantásticas.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - La Expedición.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - La torre Oscura I.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Stephen King - The Dead Zone.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Umberto Eco - El Nombre de la Rosa.txt");


	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");

	arcControl->registrarLibro(arcReg->getPosicionActual());
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");
}

void testBiblioteca()
{
    DatoLibro *dato = new DatoLibro();
    ArchivoLibro *arcReg = new ArchivoLibro("prueba.dat");
    ArchivoControlLibro *arcControl = new ArchivoControlLibro("pruebaControl.crt");

    cargarLibros(arcReg, arcControl);

    //se recorre toda la biblioteca
    arcReg->irAlInicio();
    DatoLibro libroRecuperado = arcReg->recuperarLibro(265090);
    cout << libroRecuperado.toString() << ";" << endl;

    delete (dato);
    delete (arcReg);
    delete (arcControl);
}


void testControladorBiblioteca()
{
	//TODO falta testear el eliminar y el tema de los indices
	ControladorBiblioteca* control = new ControladorBiblioteca("prueba.dat","pruebaControl.crt");

	control->ingresarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");
	DatoLibro libro = control->recuperarLibro(0);

	Logger::log("ControlBiblioteca","recuperarLibro",libro.getDato());
}



void testArchivoControlLibro(){
    ArchivoControlLibro* acl = new ArchivoControlLibro("controlLibro.txt");

    list<char> indices;
    indices.push_back('T');
    indices.push_back('A');
    indices.push_back('P');
    indices.push_back('E');

    //list<char>* indicesNuevos = new list<char>();

    /* Chequeo de registrarIndexado() */
    //acl->registrarIndexado(5,'E');

    /* Chequeo de chequearIndexado() */
    //indicesNuevos = acl->chequearIndexado(3);
    //list<char>::iterator it = indicesNuevos->begin();
    //for (it; it != indicesNuevos->end(); ++it) {
        //cout << *it << endl;
    //}

    /* Chequeo de dondeEscribo()*/
    uint32_t t = acl->dondeEscribo(10);

    cout << "donde escribo: " << t << endl;

    //acl->actualizarArchivo();

    delete(acl);
}



#endif /* TESTARCHIVO_H_ */
