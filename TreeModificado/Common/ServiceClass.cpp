#include "ServiceClass.h"

ServiceClass::ServiceClass() {

}

string ServiceClass::obtenerString(unsigned int valor) {
	stringstream aux;
	aux << valor;
	return aux.str();
}

unsigned int ServiceClass::obtenerNumero(string valor) {
	stringstream numero;
	unsigned int a;
	numero << valor;
	numero >> a;
	return a;
}

bool ServiceClass::estaEntre(unsigned int valor1, unsigned int valor2,
		unsigned int valor) {
	if ((valor1 <= valor) && (valor <= valor2))
		return true;
	else
		return false;
}

int ServiceClass::devolverFechaInt(string valor) {
	int pos = 0;
	string AAAA, DD, MM;

	DD = valor.substr(pos, 2);
	pos = valor.find('/', 0);
	MM = valor.substr(pos + 1, 2);
	pos = valor.find('/', pos + 1);
	AAAA = valor.substr(pos + 1, 4);

	return ServiceClass::obtenerNumero(AAAA + MM + DD);
}

const unsigned char* ServiceClass::obtenerPuntero(const string & valor) {
	const unsigned char* pValor =
			reinterpret_cast<const unsigned char*> (valor.c_str());

	return pValor;
}

string ServiceClass::toUppercase(string s) {
	for (size_t i = 0; i < s.length(); ++i) {
		s[i] = toupper(s[i]);
	};

	return s;
}

string ServiceClass::toDowncase(string s) {
	for (size_t i = 0; i < s.length(); ++i) {
		s[i] = tolower(s[i]);
	};

	return s;
}

string ServiceClass::toStringData(vector<string>* datos, string separador){
	string aux;
	vector<string>::iterator it = datos->begin();

	for(it; it != datos->end(); it++){
		aux += (*it);
		aux += separador;
	}

	return aux;
}

std::vector<std::string> ServiceClass::obtenerListaPalabras(std::string linea, std::string separadores)
{
	//retorno
	std::vector<std::string> listaPalabras;

	//Pasamos el string linea a un char[]
	char *a=new char[linea.size()+1];
	a[linea.size()]=0;
	memcpy(a,linea.c_str(),linea.size());

	//char* a = NULL;
	//strcpy(a, linea.c_str());

	//http://www.cplusplus.com/reference/clibrary/cstring/strtok/
	char* pch = strtok (a, separadores.c_str() );
	while ( pch != NULL )
	{
		std::string stopWord (pch);

		listaPalabras.push_back(stopWord);

		//pch = strtok (NULL, " ,.-");
		pch = strtok (NULL, separadores.c_str());
	}

	delete []a;

	return listaPalabras;
}

std::vector<std::string> ServiceClass::obtenerListaRenglones(string texto, char caracterFinDeLinea)
{
	std::string renglon;
	std::vector<std::string> listaRenglones;

	size_t posicionFin = 0;
	size_t posicionInicio = 0;

	if (!texto.empty())
	{
		while(posicionFin != string::npos)
		{
			//posicionFin = texto.find("\n", posicionInicio);
			posicionFin = texto.find(string(&caracterFinDeLinea), posicionInicio);
			if (posicionFin != string::npos)
			{
				//subcadena desde posición inicio hasta (posiciónFin-1 -posicionInicio). Equivale a un renglón.
				renglon = texto.substr(posicionInicio, (posicionFin - 1)-posicionInicio);
			}
			else
			{
				renglon = "";
			}

			listaRenglones.push_back(renglon);

			//posición siguiente al último fin de línea; en caso de fin de cadena, no se usa.
			posicionInicio = posicionFin+1;
		}
	}
	return listaRenglones;
}

string ServiceClass::getFechaHora() {
    time_t rawtime;
    time ( &rawtime );

    string aux = ctime(&rawtime);

    return string (aux.substr(0,aux.size() - 1));
}

string ServiceClass::toString(uint32_t numero)
{
	char aux[11]; // 11 bytes: 10 for the digits, 1 for the null character

	snprintf(aux, sizeof aux, "%lu", (uint32_t)numero);

	return (string)aux;
}

string ServiceClass::toStringSized(uint32_t numero, unsigned int cantidadCaracteres)
{
	std::string cadena = toString(numero);

	if(cadena.size() < cantidadCaracteres)
	{
		std::stringstream ss;
		std::string ceros(cantidadCaracteres-cadena.size(), '0');
		ss<<ceros<<cadena;

		return ss.str();
	}
	else if (cadena.size() > cantidadCaracteres)
	{
		int caracteresSobrantes = cadena.size()-cantidadCaracteres;
		cadena.erase( cadena.size()-caracteresSobrantes, caracteresSobrantes);
	}

	return cadena;

}

/*
string ServiceClass::toStringSized(unsigned int numero, unsigned int cantidadCaracteres)
{

}
*/


string ServiceClass::normalizarString(string cadena)
{
	std::string cadenaRetorno = ServiceClass::toDowncase(cadena);

	for (unsigned int x = 0; x < cadenaRetorno.size(); x++)
	{
		char letra = cadenaRetorno.at(x);
		switch(letra)
		{
		case '�':
			cadenaRetorno.replace(x,1,"a");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"e");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"i");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"o");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"u");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"u");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"n");
			break;
		case '�':
			cadenaRetorno.replace(x,1,"n");
			break;
			//(lamentablemente el toDownCase no reconoce la � may�scula)
		}
	}
	return cadenaRetorno;
}

uint32_t ServiceClass::convertirAUint32(string aux)
{
	string s;
	uint32_t rdo = 0;
	int tamanioString = aux.length();

	for(int i = 0; i < tamanioString; i++)
	{
		s=aux[i];
		int iAux=atoi((const char*)s.c_str());
		//int iAux = obtenerNumero(aux);
		rdo+= iAux*(pow(10,tamanioString-1-i));
	}

	return rdo;
}


ServiceClass::~ServiceClass() {

}









