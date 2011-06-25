/*
 * ManejadorInstrucciones.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 */

#include "ManejadorInstrucciones.h"

ManejadorInstrucciones::ManejadorInstrucciones(char* argumentos[], int cantidad) {

	this->cantidadArgumentos = cantidad;

	for (int i = 0; i < cantidad; i++)
	{
		string aux = argumentos[i];
		this->comando[i] = aux;
	}
}

char ManejadorInstrucciones::armarInstruccion() {
	Logger::log("ManejadorInstrucciones", "armarInstruccion",
			"Se obtiene la instruccion ingresada como parametro");

	return obtenerIDinstruccion(this->comando[1]);

}

void ManejadorInstrucciones::ejecutarInstruccion(char id) {

	switch (id) {
	case 'i':
		this->instruccion = new Instruccion_TomarTexto(id,
				ServiceClass::normalizarString(this->comando[2]));
		this->instruccion->ejecutar();
		break;
	case 'e':
		this->instruccion = new Instruccion_ProcesarEditorial(id);
		this->instruccion->ejecutar();
		break;
	case 'a':
		this->instruccion = new Instruccion_ProcesarAutor(id);
		this->instruccion->ejecutar();
		break;
	case 't':
		this->instruccion = new Instruccion_ProcesarTitulo(id);
		this->instruccion->ejecutar();
		break;
	case 'p':
		this->instruccion = new Instruccion_ProcesarPalabras(id);
		this->instruccion->ejecutar();
		break;
	case 'l':
		this->instruccion = new Instruccion_ListarArchivosTomados(id);
		this->instruccion->ejecutar();
		break;
	case 'o':
		this->instruccion = new Instruccion_ObtenerArchivo(id,
				ServiceClass::convertirAUint32(this->comando[2]));
		this->instruccion->ejecutar();
		break;
	case 'q':
		if (this->comando[2] != "")
		{
			this->instruccion = new Instruccion_QuitarArchivo(id,
					ServiceClass::convertirAUint32(this->comando[2]));
			this->instruccion->ejecutar();
		}
		else cout<<MENSAJE_LIBRO_NO_EXISTE<<endl;
		break;
	case 'v':
		this->instruccion = new Instruccion_VerEstructura(id,
				obtenerIDinstruccion(this->comando[2]),
				ServiceClass::normalizarString(this->comando[3]));
		this->instruccion->ejecutar();
		break;
	case (CONSULTA_INDICE_TITULO):
			this->instruccion = new Instruccion_ConsultarTitulo(CONSULTA_INDICE_TITULO,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	case (CONSULTA_INDICE_AUTOR):
			this->instruccion = new Instruccion_ConsultarAutor(CONSULTA_INDICE_AUTOR,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	case (CONSULTA_INDICE_EDITORIAL):
			this->instruccion = new Instruccion_ConsultarEditorial(CONSULTA_INDICE_EDITORIAL,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	case (CONSULTA_INDICE_PALABRAS):
			this->instruccion = new Instruccion_ConsultarTerminosProximos(CONSULTA_INDICE_PALABRAS,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	case (CONSULTA_ARCHIVO_OCURRENCIA):
			this->instruccion = new Instruccion_ConsultarOcurrenciaPosicional(CONSULTA_INDICE_PALABRAS,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	case (CONSULTA_ARCHIVO_NORMAS):
			this->instruccion = new Instruccion_ConsultarNormaInfinito(CONSULTA_ARCHIVO_NORMAS,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	case (CONSULTA_ARCHIVO_TERMINOS):
			this->instruccion = new Instruccion_ConsultarArchivoTerminos(CONSULTA_ARCHIVO_TERMINOS,obtenerConsulta());
			this->instruccion->ejecutar();
			break;
	case (CONSULTA_INDICE_TERMINOS):
			this->instruccion = new Instruccion_ConsultarIndiceTerminos(CONSULTA_INDICE_TERMINOS,obtenerConsulta());
			this->instruccion->ejecutar();
		break;
	default:
		Logger::log("ManejadorInstrucciones", "ejecutarInstruccion",
				"Comando no valido.");
		break;
	}
}

char ManejadorInstrucciones::obtenerIDinstruccion(string id) {
	char idInstruccion = ' ';

	for (int i = 0; i < id.size(); i++) {
		if (id[i] == '-')
		{
			idInstruccion = id[i + 1];
			if ((id[i + 2] != ' ') && (idInstruccion == 'q'))
			{
				if (id[i + 2] == 'a')
					idInstruccion =  CONSULTA_INDICE_AUTOR;
				else if (id[i + 2] == 'e')
					idInstruccion =  CONSULTA_INDICE_EDITORIAL;
				else if (id[i + 2] == 't')
					idInstruccion =  CONSULTA_INDICE_TITULO;
				else if (id[i + 2] == 'p')
					idInstruccion =  CONSULTA_INDICE_PALABRAS;
			}
			else if((idInstruccion == 'v'))
			{
				//string aux = obtenerConsulta();
				string aux = this->comando[2];
				vector<string> vectorAux = ServiceClass::obtenerListaPalabras( aux, SEPARADORES_DE_PALABRAS);

				//al pasarlo por el filtro de separadores de palabras pierde el guion "-"

				if(aux == "-at")//vectorAux.at(0) == "at")//aux == "-at")
					idInstruccion =  CONSULTA_ARCHIVO_TERMINOS;
				else if(aux == "-ani")//vectorAux.at(0) == "ani")//if(aux == "-ani")
					idInstruccion =  CONSULTA_ARCHIVO_NORMAS;
				else if(aux == "-aop")//vectorAux.at(0) == "aop")//if(aux == "-aop")
					idInstruccion =  CONSULTA_ARCHIVO_OCURRENCIA;
				else if(aux == "-li")//vectorAux.at(0) == "li")//if(aux == "-li")
					idInstruccion =  CONSULTA_INDICE_TERMINOS;
			}
		}
	}
	cout<<endl;
	Logger::log("ManejadorInstrucciones", "obtenerIDInstruccion",
			"Se codifica.");

	return idInstruccion;
}

string ManejadorInstrucciones::obtenerConsulta() {
	string rdo = "";

	string tipoConsulta = this->comando[1];

	for (int i = 2; i < MAX_COMANDOS; i++)
		rdo+=this->comando[i]+" ";

	//Ahora solo nos interesa el ultimo termino (antes traia toda la cadena desde el 2do parametro
	//en adelante, y traia problemas para 3 parametros).
	vector<string> listaParametros = ServiceClass::obtenerListaPalabras(rdo, SEPARADORES_DE_PALABRAS);

	//TODO ojo, poner constante si se va a cambiar.
	if( tipoConsulta == "-qp")
	{
		//Nos interesan todods los terminos
	}
	else
	{
		//si no, salteamos los comandos intermedios y nos quedamos con el parametro nombre de archivo
		rdo = listaParametros.back();
	}


	Logger::log("ManejadorInstrucciones", "obtenerIDInstruccion",
			"Se codifica.");


	return rdo;
}

void ManejadorInstrucciones::ejecutarInstruccionElegida() {

	std::cout<<"parametros instruccion = "<< this->cantidadArgumentos;

	ejecutarInstruccion(armarInstruccion());

}

ManejadorInstrucciones::~ManejadorInstrucciones() {
	delete (this->instruccion);
}
