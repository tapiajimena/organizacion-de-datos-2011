/*
 date: 14/03/11


*/
#include <iostream>
#include "ModuloDeTipos/Datos.h"
#include "ModuloDeTipos/Registro.h"
#include "ModuloDeTipos/RegistroFijo.h"
#include "ModuloDeTipos/RegistroVariable.h"
#include "ModuloDeArchivos/ArchivoVariable.h"


/**
 * hacer el test con el CUTE
 */
void testEscrituraLectura()
{
	Datos* datos = new Datos();
	RegistroVariable* rv = new RegistroVariable(*datos);
	ArchivoVariable* arcReg = new ArchivoVariable("prueba.dat");

	//se escribe. abre y se cierra el archivo n veces
	for (int i = 65; i < 512; i++)
	{
		datos->setDatos(datos->getDatos()+(char)i);
		rv->setDato(*datos);
		arcReg->escribirAlFinal(*rv);
	}

	/*
	//test agregarAlFinal
	datos->setDatos("PIRULO EN EL BOSQUE Ññ áÁ Éé íÍ óÓ úÚÜ &!");
	rv->setDato(*datos);
	arcReg->escribirAlFinal(*rv);
	*/

	//se lee
	uint32_t sizeAux = 0;
	arcReg->irAInicio();
	/*
	string rdo = arcReg->leerRegistroVariable();
	while(!arcReg->finArchivo())
		cout<< sizeAux<<";"<<arcReg->leerRegistroVariable()<<";"<<endl;
		*/
}


using namespace std;
int main()
{
	Datos* datos = new Datos();
	RegistroVariable* rv = new RegistroVariable(*datos);
	ArchivoVariable* arcReg = new ArchivoVariable("prueba.dat");


	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - El signo de los cuatro.txt");
	arcReg->agregarLibro("doc/libros/Arthur Conan Doyle - Estudio en Escarlata.txt");

	arcReg->irAInicio();
	cout<< arcReg->leerRegistroVariable()<<";"<<endl;

	delete(rv);
    delete(datos);
    delete(arcReg);

    return 0;
}
