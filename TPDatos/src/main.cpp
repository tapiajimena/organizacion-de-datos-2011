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
	Datos* datos = new Datos();
	//RegistroFijo* reg = new RegistroFijo(*datos);
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
	datos->setDatos("PIRULO EN EL BOSQUE Ññ áÁ Éé íÍ óÓ úÚÜ &!");
	rv->setDato(*datos);
	arcReg->escribirAlFinal(*rv);
	*/

	//se lee
	uint32_t sizeAux = 0;
	arcReg->irAInicio();
	string rdo = arcReg->leer();
	while(!arcReg->finArchivo())
		cout<< sizeAux<<";"<<arcReg->leer()<<";"<<endl;



	delete(rv);
    delete(datos);
    delete(arcReg);

    return 0;
}
