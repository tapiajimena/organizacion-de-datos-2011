#include "Logger.h"

Logger::Logger() {
}

void Logger::log(string clase, string metodo, string mensaje) {

	string nombreClase = ServiceClass::toUppercase(clase);

	cout << ServiceClass::getFechaHora() << " - " << nombreClase << " [" << metodo << "]: " << mensaje << endl;
}

Logger::~Logger() {
}
