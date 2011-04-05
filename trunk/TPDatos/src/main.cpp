/*
 date: 14/03/11


*/
#include <iostream>
#include "ModuloDeTipos/Datos.h"
#include "ModuloDeTipos/Registro.h"
#include "ModuloDeTipos/RegistroFijo.h"
#include "ModuloDeTipos/RegistroVariable.h"
#include "ModuloDeArchivos/ArchivoVariable.h"



using namespace std;
int main()
{
	Datos* datos = new Datos((char*) "PiRULO2!!");
	//RegistroFijo* reg = new RegistroFijo(*datos);
	RegistroVariable* rv = new RegistroVariable(*datos);
	ArchivoVariable* arcReg = new ArchivoVariable("prueba.dat");

	cout<<datos->toString()<<endl;
	cout<<rv->getDato().toString()<<endl;

	arcReg->escribir(*rv,0);


	delete(rv);
    delete(datos);
    delete(arcReg);

    return 0;
}
