#include "ServiceClass.h"

ServiceClass::ServiceClass() {

}

string ServiceClass::agregarExtensionArchivo(string valor) {
	if (valor.find(".tmpl") == string::npos)
		valor.insert(valor.size(), ".tmpl");
	return valor;
}

string ServiceClass::obtenerNombreArchivo(string valor) {
	size_t pos = 0;
	pos = valor.rfind('/');
	string aux;

	if (pos != string::npos && pos != valor.size() - 1)
		aux = valor.substr(pos + 1, valor.size());
	else
		aux = valor;

	pos = aux.find(".tmpl");
	if (pos != string::npos)
		aux.erase(pos, aux.size() - pos);

	return aux;
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

int ServiceClass::getLineas(string texto) {
	int lineas = 0;
	size_t pos = 0;
	if (!texto.empty()) {
		while (pos < texto.size() && pos != string::npos) {
			pos = texto.find('\n', pos);
			if (pos != string::npos) {
				lineas++;
				pos++;
			}
		}
		if (texto.at(texto.size() - 1) != '\n')
			lineas++;
	}
	return lineas;
}

unsigned int ServiceClass::getMaxLargoLinea(std::string cadena) {
	unsigned int largo_linea = 0;
	size_t pos = 0;
	if (!cadena.empty()) {
		while (pos != string::npos) {
			pos = cadena.find('\n', 0);
			if (pos != string::npos) {
				if (pos < cadena.size() - 1)
					cadena = cadena.substr(pos + 1);
				else
					cadena = "";
				if (pos > largo_linea)
					largo_linea = pos;
			} else {
				if (cadena.size() > largo_linea)
					largo_linea = cadena.size();
			}
		}
	}
	return largo_linea;
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

string ServiceClass::getFechaHora() {
    time_t rawtime;
    time ( &rawtime );

    string aux = ctime(&rawtime);

    return string (aux.substr(0,aux.size() - 1));
}

ServiceClass::~ServiceClass() {

}
