#include "Logger.h"

Logger::Logger() {
}

void Logger::log(string clase, string metodo, string mensaje) {

	string nombreClase = ServiceClass::toUppercase(clase);

	//cerr << ServiceClass::getFechaHora() << " - " << nombreClase << " ["
		//	<< metodo << "]: " << mensaje << endl;
}

Logger::~Logger() {
}
