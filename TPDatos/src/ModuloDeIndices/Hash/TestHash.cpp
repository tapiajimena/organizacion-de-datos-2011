/*
* TestHash.cpp
*  
*	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
*	Catedra	: SERVETTO-FERRER-FERNANDEZ
*	Materia	: Organizacion de Datos (75.06) - FIUBA
*      
*  
*      
*      
*/   

void testDatoCubetaHash()
{
	stringstream ssElemento;

	ElementoHash elementoHash("palabraElemento", 1000);

	elementoHash.serializarElementoHash(&ssElemento);
	//std::string elementoHashSerializado = elementoHash.serializarElementoHash(ss);
	std::cout<<"tamanioElementoHashSerializadoAAAA: "<<ssElemento.str().size()<<std::endl;

	stringstream ssCubeta;

	unsigned int numero = 989; //bytes libres.
	ssCubeta.write(reinterpret_cast<char *>(&numero), sizeof(numero));

	numero = 2048; //Puntero a supuesta proxima cubeta.
		ssCubeta.write(reinterpret_cast<char *>(&numero), sizeof(numero));

	numero = 1; //1 cantidad de elementos
	ssCubeta.write(reinterpret_cast<char *>(&numero), sizeof(numero));

	//Serializamos elemento
	ssCubeta.write(ssElemento.str().c_str(), ssElemento.str().size());

	/*
	//Completamos los bytes supuestamente leidos del disco.
	for( unsigned int x = 0; x < 989; x++)
	{
		char c = '0';
		ssCubeta.write(&c, 1);
	}
	 */


	fstream archivoCubetas;
	ManejadorArchivo::Crear("pruebaDatoCubeta.dat", archivoCubetas, true);

	std::cout<<ssCubeta.str().size()<<std::endl;

	DatoCubetaHash datoCubeta(&ssCubeta);


	std::cout<<"Datos serializados: ..."<<std::endl;
	std::cout<<"Size Vector Elementos Cubeta: "<<datoCubeta.getElementos().size()<<std::endl;
	std::cout<<"Palabra 1er elemento: "<<datoCubeta.getElementos().at(0).getPalabra()<<std::endl;
	std::cout<<"BytesLibres: "<<datoCubeta.getBytesLibres()<<std::endl;
	std::cout<<"Prox. Cubeta: "<<datoCubeta.getOffsetCubetaContinuacion()<<std::endl;
	std::cout<<"Cant. Elementos: "<<datoCubeta.getCantidadDeElementos()<<std::endl;


	ssCubeta.seekg(0, ios_base::beg);
	ManejadorArchivo::Escribir(&archivoCubetas, &ssCubeta, 0,1024);

	ManejadorArchivo::Cerrar(archivoCubetas);

}
