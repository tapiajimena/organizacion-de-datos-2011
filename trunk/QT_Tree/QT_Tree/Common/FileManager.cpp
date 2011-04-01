/*
 * FileManager.cpp
 *
 *  Created on: 18/04/2010
 *      Author: marcelo
 */

#include "FileManager.h"


bool FileManager::readData(fstream* file, long offset, long size, iostream* ios) {
	file->seekg(offset, ios_base::beg);
	char * buffer = new char[size];
	memset(buffer, 0, size);
	file->read(buffer, size);

	ios->write(buffer, size);
	delete[] buffer;
	if (file->good() && ios->good()) {
		return true;
	} else {
		return false;
	}
}

long FileManager::fileSize(string fileName){
	long l, m;
	ifstream file(fileName.c_str(), ios::in|ios::binary);
	l = file.tellg();
	file.seekg (0, ios::end);
	m = file.tellg();
	file.close();
	return (m-l);
}

bool FileManager::writeData(fstream* file, long offset, long size, iostream* ios) {
	file->seekp(offset, ios_base::beg);
	char* buffer = new char[size];

	ios->read(buffer, size);
	file->write(buffer, size);
	if (file->good() && ios->good()) {
		delete [] buffer;
		return true;
	} else {
		delete [] buffer;
		return false;
	}
}

/* Verifica la existencia del archivo de nombre fileName.*/
bool FileManager::fileExists(string fileName) {
	fstream fs;
	fs.open(fileName.c_str(), fstream::in | fstream::out | fstream::binary);
	if (fs.is_open()) {
		fs.close();
		return true;
	}
	return false;
}

/* Crea y abre el archivo */
bool FileManager::createFile(fstream* file, string fileName) {
	file->open(fileName.c_str(), fstream::in | fstream::out | fstream::trunc | fstream::binary);
	if (file->is_open()) {
		return true;
	}
	return false;
}

/* Abre el archivo y retorna TRUE. Si no pudo abrirlo retorna FALSE. */
bool FileManager::openFile(fstream* file, string fileName) {
	file->open(fileName.c_str(), fstream::in | fstream::out | fstream::binary);

	if (file->is_open()) {
		return true;
	}
	return false;
}

bool FileManager::openFileToAppend(fstream* file, string fileName){
	file->open(fileName.c_str(), fstream::in | fstream::out | ios::app);
	if (file->is_open()) {
		return true;
	}
	return false;
}

bool FileManager::copyFile(string name, string copyName){

	std::ifstream ifs(name.c_str(), std::ios::binary);
	std::ofstream ofs(copyName.c_str(), std::ios::binary);

	ofs << ifs.rdbuf();
	ifs.close();
	ofs.close();
}

void FileManager::appendLine(fstream* file,const string line) {
	*file << line << endl;
}

string FileManager::readLine(fstream* file){
	const int sz = 2000; // Buffer size;
	char* buf = new char[sz];
	stringstream sin;
	if (!(file->eof()) && file->getline(buf, sz)) {
		sin << buf;
		return sin.str();
	}
	return "";
}

bool FileManager::renameFile(string name, string newName){
	int res = rename(name.c_str(),newName.c_str());
	if (res==1) return true;
	return false;
}

bool FileManager::closeFile(fstream* file) {
	file->close();
	return true;
}

