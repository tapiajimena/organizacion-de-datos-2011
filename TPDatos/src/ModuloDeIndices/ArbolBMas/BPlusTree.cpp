/*
 * BPlusTree.cpp
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *
 *
 *
 */

#include "BPlusTree.h"
#include "BPlusTree_CONST.h"

BPlusTree::BPlusTree() {
}

BPlusTree::BPlusTree(string fileName, long blockSize) {

	this->fileName = fileName;
	this->blockSize = blockSize;
	//long: blockSize unsigned int: elementoCounter, nodeCounter, freeNodeCounter
	this->controlDataSize = sizeof(long) + 3 * sizeof(unsigned int);
	if (FileManager::fileExists(fileName)) { // si el archivo existe
		Logger::log("BPlusTree","BPlusTree","se abre el archivo del arbol");
		FileManager::openFile(&file, fileName); // abre el archivo
		FileManager::openFile(&freeNodesFile, getFreeNodesFileName(fileName));
		if (this->readControlData() == EXIT_SUCCESS) {// si pudo leer el header
			root = readNode(0); //lee y carga la raiz, del primer bloque del archivo
		} else {
			exit(EXIT_FAILURE);
		}
	} else {
		if (FileManager::createFile(&file, fileName)) {
			Logger::log("BPlusTree","BPlusTree","se crea el archivo del arbol");
			FileManager::createFile(&freeNodesFile,
					getFreeNodesFileName(fileName));
			root = new LeafNode();
			root->setNodeId(0);
			nodeCounter = 1;
			freeNodeCounter = 0;
			writeControlData();
			writeNode(root);
		}
	}
}

BPlusTree::~BPlusTree() {
	//dump("albol.txt");
	writeControlData();
	FileManager::closeFile(&file);
	FileManager::closeFile(&freeNodesFile);
}

int BPlusTree::readControlData() {
	stringstream iosCtrlData(ios_base::in | ios_base::out | ios_base::binary);
	bool readData = false;
	readData = FileManager::readData(&file, 0, controlDataSize, &iosCtrlData);
	if (readData) {
		(iosCtrlData).read(reinterpret_cast<char *> (&blockSize),
				sizeof(blockSize));
		(iosCtrlData).read(reinterpret_cast<char *> (&nodeCounter),
				sizeof(nodeCounter));
		(iosCtrlData).read(reinterpret_cast<char *> (&freeNodeCounter),
				sizeof(freeNodeCounter));
		(iosCtrlData).read(reinterpret_cast<char *> (&elementoCounter),
				sizeof(elementoCounter));
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}

int BPlusTree::writeControlData() {
	/* Datos de control del árbol:
	 * <TamBloque><CantNodos><CantNodosLibres><CantRegistros> */
	stringstream iosCtrlData(ios_base::in | ios_base::out | ios_base::binary);
	(iosCtrlData).write(reinterpret_cast<char *> (&blockSize),
			sizeof(blockSize));
	(iosCtrlData).write(reinterpret_cast<char *> (&nodeCounter),
			sizeof(nodeCounter));
	(iosCtrlData).write(reinterpret_cast<char *> (&freeNodeCounter),
			sizeof(freeNodeCounter));
	(iosCtrlData).write(reinterpret_cast<char *> (&elementoCounter),
			sizeof(elementoCounter));
	if (FileManager::writeData(&file, 0, controlDataSize, &iosCtrlData)) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}

Node* BPlusTree::getRoot() {
	if (root == NULL)
		root = new LeafNode();
	return root;
}

int BPlusTree::insert(DatoElementoNodo* elemento) {
	int result, promotedNodeId;
	string promotedKey;

	if (elemento->getSize() > getMaxRecordSize()) {
		return EXIT_FAILURE;
	}

	result = recursiveInsert(elemento, root, &promotedKey, &promotedNodeId);
	if (result == OVERFLOWDED) { // Si se desborda la raíz...
		InternalNode* newRoot = new InternalNode();
		newRoot->setLevel(root->getLevel() + 1);
		newRoot->setNodeId(0);
		NodeFactory::assignNodeId(root, &nodeCounter, &freeNodeCounter,
				&freeNodesFile);

		newRoot->getChildIds()->push_back(root->getNodeId()); //por orden se pone una despues de la otra
		newRoot->insertKeyChild(promotedKey, promotedNodeId);

		writeNode(root);
		writeNode(newRoot);
		delete this->root;
		this->root = newRoot;
		return EXIT_SUCCESS;
	}
	return result;
}

int BPlusTree::recursiveInsert(DatoElementoNodo* elemento, Node* currentNode,
		string* promotedKey, int* promotedNodeId) {
	int result;
	Node* newNode = NULL;
	if (currentNode->getLevel() == 0) { // Es un LeafNode
		result = currentNode->insert(elemento);

		if (result == EXIT_SUCCESS) {
			writeNode(currentNode);
		} else if (result == OVERFLOWDED) {
			newNode = new LeafNode();
			NodeFactory::assignNodeId(newNode, &nodeCounter, &freeNodeCounter,
					&freeNodesFile);
			currentNode->split(newNode, BLOCKSIZE, promotedKey, promotedNodeId);
			writeNode(currentNode);
			writeNode(newNode);

			delete (newNode);
			return OVERFLOWDED;
		} else if (result == DUPLICATED) {
			return result;
		}
		return EXIT_SUCCESS;
	} else { // Es un InternalNode
		InternalNode* inner = (InternalNode*) currentNode;
		int locationId = inner->findLocation(elemento);

		Node* nextNode = readNode(locationId);
		result = recursiveInsert(elemento, nextNode, promotedKey,
				promotedNodeId);

		if (result == OVERFLOWDED) {
			inner->insertKeyChild(*promotedKey, *promotedNodeId);
			if (inner->isOverFlowded(BLOCKSIZE)) { // Si luego de insertar el "registrito" quedo en overflow
				newNode = new InternalNode();
				newNode->setLevel(inner->getLevel());
				NodeFactory::assignNodeId(newNode, &nodeCounter,
						&freeNodeCounter, &freeNodesFile);
				inner->split(newNode, BLOCKSIZE, promotedKey, promotedNodeId);
				writeNode(inner);
				writeNode(newNode);
				delete (newNode);
				delete (nextNode);
				return OVERFLOWDED;
			}
			writeNode(inner);
			delete (nextNode);
			return EXIT_SUCCESS;
		} else {
			delete (nextNode);
			return result;
		}
	}
}

int BPlusTree::remove(DatoElementoNodo* elemento) {
	int result = this->root->remove(elemento, this->controlDataSize,
			&this->file, &nodeCounter, &freeNodesFile, &freeNodeCounter);

	/*
	 * si la raiz no es un nodo hoja
	 */
	if (this->root->getLevel() > 0) {
		InternalNode* root = (InternalNode*) this->root;
		if (root->getChildIds()->size() == 1) {
			/*
			 * al ser la raiz un nodo interno y tener solo un
			 * hijo, no puede seguir siendo raiz
			 * por lo que su hijo pasará a serlo.
			 */
			int newRootId = root->getChildIds()->front();
			NodeFactory::addFreeNodeId(newRootId, &freeNodeCounter,
					&freeNodesFile);

			Node* newRoot = readNode(newRootId);
			newRoot->setNodeId(0);
			delete (this->root);
			this->root = newRoot;
			writeNode(this->root);
		}
	}

	this->writeNode(this->root);
	return result;
}

DatoElementoNodo* BPlusTree::find(DatoElementoNodo* elemento) {
	return recursiveSearch(elemento, root);
}

DatoElementoNodo* BPlusTree::recursiveSearch(DatoElementoNodo* elemento,
		Node* node) {

	InternalNode* inner;
	DatoElementoNodo* elementoAux;
	if (node->getLevel() == 0) {
		/*
		 * llegó a la hoja
		 * lo encuentra y lo retorna
		 */
		elementoAux = node->find(elemento);
		return elementoAux->clonar();
	} else {
		inner = (InternalNode*) node;
		int locationId = inner->findLocation(elemento);
		Node* nextNode = readNode(locationId);
		elementoAux = recursiveSearch(elemento, nextNode);
		delete (nextNode);
		return elementoAux;
	}
}

void BPlusTree::dump(string dumpFileName) {
	fstream dumpFile;

	FileManager::createFile(&dumpFile, dumpFileName);

	(dumpFile) << "[B+Tree controlDataSize=[" << this->controlDataSize
			<< "] blockSize=[" << BLOCKSIZE << "] nodeCounter=["
			<< this->nodeCounter << "] freeNodeCounter=["
			<< this->freeNodeCounter << "] ]" << endl;

	this->root->toString(&dumpFile, this->root->getLevel(),
			this->controlDataSize, &this->file);
	FileManager::closeFile(&dumpFile);
}

void BPlusTree::dumpToXML(string dumpFileName) {
	fstream dumpFile;

	FileManager::createFile(&dumpFile, dumpFileName);

	(dumpFile) << "<BPlusTree controlDataSize=\"" << this->controlDataSize
			<< "\" blockSize=\"" << BLOCKSIZE << "\" nodeCounter=\""
			<< this->nodeCounter << "\" freeNodeCounter=\""
			<< this->freeNodeCounter << "\" >" << endl;

	this->root->toStringXML(&dumpFile, this->root->getLevel(),
			this->controlDataSize, &this->file);

	(dumpFile) << "</BPlusTree>";
	FileManager::closeFile(&dumpFile);
}

Node* BPlusTree::readNode(int nodeId) {
	int level = 0;
	Node* node = NULL;
	stringstream ios(ios_base::in | ios_base::out | ios_base::binary);
	long offset = this->controlDataSize + (nodeId * this->blockSize);
	FileManager::readData(&file, offset, blockSize, &ios);

	ios.read(reinterpret_cast<char *> (&level), sizeof(int));
	if (level == 0) {
		node = new LeafNode();
	} else {
		node = new InternalNode();
		node->setLevel(level);
	}

	node->deserialize(&ios);
	return node;
}

void BPlusTree::writeNode(Node* node) {
	stringstream ios(ios_base::in | ios_base::out | ios_base::binary);
	long offset = controlDataSize + (node->getNodeId() * blockSize);
	node->serialize(&ios);
	FileManager::writeData(&file, offset, blockSize, &ios);
}

void BPlusTree::iterate() {

}

int BPlusTree::modify(DatoElementoNodo* elemento) {
	if (elemento->getSize() > getMaxRecordSize()) {
		return EXIT_FAILURE;
	}

	int result = recursiveModify(elemento, root);

	if (result == OVERFLOWDED) {
		// Como se que existe, lo puedo borrar
		remove(elemento);
		// Como ya lo borré, lo puedo insertar
		insert(elemento);
		return EXIT_SUCCESS;

		/*
		 * la raiz no es un nodo hoja
		 */
	} else if (this->root->getLevel() > 0) {
		InternalNode* root = (InternalNode*) this->root;
		if (root->getChildIds()->size() == 1) {
			/*
			 * al ser la raiz un nodo interno y tener solo un
			 * hijo, no puede seguir siendo raiz
			 * por lo que su hijo pasará a serlo.
			 */
			int newRootId = root->getChildIds()->front();
			//newRootId pasa a ser libre porque la raiz se va a reubicar con Id = 0
			NodeFactory::addFreeNodeId(newRootId, &freeNodeCounter,
					&freeNodesFile);

			//se recupera la nueva raiz
			Node* newRoot = readNode(newRootId);
			//se le setea el nuevo Id para que sea reubicada
			newRoot->setNodeId(0);
			delete (this->root);
			this->root = newRoot;
			writeNode(this->root);
			return EXIT_SUCCESS;
		}
	}
	return result;
}

int BPlusTree::recursiveModify(DatoElementoNodo* elemento, Node* currentNode) {
	int result;

	/*
	 * si es una hoja
	 */
	if (currentNode->getLevel() == 0) {
		LeafNode* leafNode = (LeafNode*) currentNode;
		result = leafNode->modify(elemento);

		if (result == EXIT_SUCCESS) {
			writeNode(leafNode);
		}

		/*
		 * si la raiz queda en underflow, la operación resulta exitosa
		 * de todas maneras, ya que no se puede balancear contra nada
		 */
		if (result == UNDERFLOWDED && leafNode->getNodeId() == 0) {
			return EXIT_SUCCESS;
		}

		return result;

		/*
		 * si es nodo interno
		 */
	} else {
		InternalNode* inner = (InternalNode*) currentNode;
		int locationId = inner->findLocation(elemento);

		Node* nextNode = readNode(locationId);
		result = recursiveModify(elemento, nextNode);

		if (result == OVERFLOWDED) {
			return OVERFLOWDED;
		}

		if (result == UNDERFLOWDED) {
			result = inner->resolveUnderflow(nextNode, controlDataSize, &file,
					&nodeCounter, &freeNodesFile, &freeNodeCounter);

			/*
			 * nextNode pudo haber dejado de existir al resolver el underflow
			 * por eso se consulta si su dataSize es diferente de cero para
			 * persistir sus posibles cambios.
			 */
			if (nextNode->getDataSize() != 0) {
				NodeFactory::writeNode(nextNode, controlDataSize, &file);
			}
		}

		/*
		 * se persisten los cambios del inner node
		 */
		NodeFactory::writeNode(inner, controlDataSize, &file);

		delete nextNode;

		if (inner->isUnderFlowded(BLOCKSIZE)) {
			if (currentNode->getNodeId() == 0) {

				/*
				 * luego de inner->resolveUnderFlow(...), inner puede quedar
				 * como raiz si queda en underflow la operación es exitosa
				 * ya que no existe otro nodo con el cual poder hacer un balanceo
				 */
				return EXIT_SUCCESS;

			} else {
				return UNDERFLOWDED;
			}
		}

		return result;
	}
}

Node* BPlusTree::getNodeToInsert(string key) {
	if (root == NULL)
		root = new LeafNode();
	return root;
}

void BPlusTree::balance() {
}

string BPlusTree::getFreeNodesFileName(string fileName) {
	string name, ext;
	size_t found;
	found = fileName.find_last_of(".");
	name = fileName.substr(0, found);
	if (found == fileName.npos) {
		return (name + ".free");
	}
	ext = fileName.substr(found);
	return (name + ".free" + ext);
}

long BPlusTree::getMaxRecordSize() {
	return MAX_RECORD_PERCENTAGE * (BLOCKSIZE - 16);
}
