/*
 * FileManager.h
 *
 *  Created on: 18/04/2010
 *      Author: marcelo
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class FileManager {

public:
	static bool fileExists(string fileName);
	static bool createFile(fstream* file, string fileName);
	static bool openFile(fstream* file, string fileName);
	static bool openFileToAppend(fstream* file, string fileName);
	static bool closeFile(fstream* file);
	static bool	readData(fstream* file, long offset, long size, iostream* ios);
	static bool writeData(fstream* file, long offset, long size, iostream* ios);
	static long fileSize(string fileName);
	static bool copyFile(string name, string copyName);
	static bool renameFile(string name, string newName);
	static void appendLine(fstream* file,const string line);
	static string readLine(fstream* file);
};

#endif /* FILEMANAGER_H_ */

