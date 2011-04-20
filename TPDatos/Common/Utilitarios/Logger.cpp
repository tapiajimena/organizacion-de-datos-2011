#include "Logger.h"

Logger::Logger() {
}

void Logger::log(string clase, string metodo, string mensaje) {

	string nombreClase = ServiceClass::toUppercase(clase);

	cout << ServiceClass::getFechaHora() << " - " << nombreClase << " ["
			<< metodo << "]: " << mensaje << endl;
}

void Logger::log(string clase, string metodo, string mensaje, string aux) {

	string nombreClase = ServiceClass::toUppercase(clase);

	cout << ServiceClass::getFechaHora() << " - " << nombreClase << " ["
			<< metodo << "]: " << mensaje << " " << aux << endl;
}

Logger::~Logger() {
}
