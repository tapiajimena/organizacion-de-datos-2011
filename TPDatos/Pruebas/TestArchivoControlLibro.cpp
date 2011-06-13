#include "TestArchivoControlLibro.h"

TestArchivoControlLibro::TestArchivoControlLibro(string pathArchivoControl) {
	this->acl = new ArchivoControlLibro(pathArchivoControl);
}

ArchivoControlLibro * TestArchivoControlLibro::getAcl() const {
		return this->acl;
}

void TestArchivoControlLibro::testRegistrarIndexado() {
	this->acl->registrarIndexado(5,'E');
	acl->actualizarArchivo();
}

void TestArchivoControlLibro::testChequearIndexado() {
	list<char>* indicesNuevos = new list<char>();
	indicesNuevos = acl->chequearIndexado(3);

	if(indicesNuevos != NULL){
		list<char>::iterator it = indicesNuevos->begin();
		for (it; it != indicesNuevos->end(); ++it) {
			cout << *it << endl;
		}
	}
}

void TestArchivoControlLibro::testDondeEscribo() {
	uint32_t t = acl->dondeEscribo(4);
}

void TestArchivoControlLibro::testEliminarLibro() {
	acl->eliminarLibro(22,89);
	acl->actualizarArchivo();
}

void TestArchivoControlLibro::testRegistrarLibro(){
	//acl->registrarLibro(45);
	acl->actualizarArchivo();
}

void TestArchivoControlLibro::ejecutarPrueba(){
	//testRegistrarIndexado();
	//testChequearIndexado();
	//testDondeEscribo();
	//testEliminarLibro();
	testRegistrarLibro();
}

TestArchivoControlLibro::~TestArchivoControlLibro() {
	// TODO Auto-generated destructor stub
}
