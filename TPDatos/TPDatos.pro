TEMPLATE = app
TARGET = TPDatos
QT += core
HEADERS += src/ModuloDeArchivos/ArchicoControlTriadas.h \
    src/ModuloDeArchivos/ArchivoTriadas.h \
    src/ModuloDeTipos/DatoControlTriada.h \
    src/ModuloDeTipos/DatoTriada.h \
    src/ModuloParser/ParserArchivoTriadas.h \
    src/ModuloDeInterfaz/Instruccion_ConsultarEditorial.h \
    src/ModuloDeInterfaz/Instruccion_ConsultarAutor.h \
    src/ModuloDeIndices/ConsultaIndice.h \
    src/ModuloDeInterfaz/Instruccion_ConsultarTitulo.h \
    Common/Comparable.h \
    Common/Serializable.h \
    Common/FileManager.h \
    src/ModuloDeIndices/ArbolBMas/BPlusTree.h \
    src/ModuloDeIndices/ArbolBMas/BPlusTree_CONST.h \
    src/ModuloDeIndices/ArbolBMas/InternalNode.h \
    src/ModuloDeIndices/ArbolBMas/LeafNode.h \
    src/ModuloDeIndices/ArbolBMas/Node.h \
    src/ModuloDeIndices/ArbolBMas/NodeFactory.h \
    src/ModuloDeTipos/CaseFoldedString.h \
    src/ModuloEstructuras/Configuracion.h \
    src/ModuloEstructuras/Libro.h \
    src/ModuloParser/ParserDeAtributo.h \
    src/ModuloParser/ParserDeAutor.h \
    src/ModuloParser/ParserDeEditorial.h \
    src/ModuloParser/ParserDePalabras.h \
    src/ModuloParser/ParserDeTitulo.h \
    src/ModuloDeIndices/Indexador.h \
    src/ModuloControladores/ControladorIndice.h \
    src/ModuloControladores/ControladorBiblioteca.h \
    src/ModuloDeTipos/TestDato.h \
    src/ModuloDeArchivos/TestArchivos.h \
    src/ModuloDeTipos/DatoElementoNodo.h \
    src/ModuloDeIndices/Hash/ElementoHash.h \
    src/ModuloDeTipos/DatoTablaHash.h \
    src/ModuloDeTipos/DatoCubetaHash.h \
    src/ModuloDeIndices/Hash/Hash.h \
    src/ModuloDeTipos/DatoElementoNodo.h \
    src/ModuloDeInterfaz/Instruccion_VerEstructura.h \
    src/ModuloDeInterfaz/Instruccion_QuitarArchivo.h \
    src/ModuloDeInterfaz/Instruccion_ObtenerArchivo.h \
    src/ModuloDeInterfaz/Instruccion_ListarArchivosTomados.h \
    src/ModuloDeInterfaz/Instruccion_ProcesarPalabras.h \
    src/ModuloDeInterfaz/Instruccion_ProcesarTitulo.h \
    src/ModuloDeInterfaz/Instruccion_TomarTexto.h \
    src/ModuloDeInterfaz/Instruccion_ProcesarAutor.h \
    src/ModuloDeInterfaz/Instruccion_ProcesarEditorial.h \
    src/ModuloDeInterfaz/Instruccion.h \
    src/ModuloDeInterfaz/ManejadorInstrucciones.h \
    src/ModuloDeTipos/FrontCodedString.h \
    src/ModuloParser/ParserAuxiliar.h \
    src/ModuloParser/ParserArchivoControl.h \
    src/ModuloParser/ParserDiccionario.h \
    src/ModuloDeArchivos/ArchivoLibro.h \
    src/ModuloDeArchivos/ArchivoControlLibro.h \
    src/ModuloDeTipos/DatoLibro.h \
    src/ModuloDeTipos/DatoControlLibro.h \
    src/ModuloDeTipos/Dato.h \
    src/ModuloDeArchivos/ManejadorArchivo.h \
    Common/Constantes.h \
    Common/Utilitarios/Logger.h \
    Common/Utilitarios/ServiceClass.h \
    src/ModuloEstructuras/Diccionario.h
SOURCES += src/ModuloDeArchivos/ArchicoControlTriadas.cpp \
    src/ModuloDeArchivos/ArchivoTriadas.cpp \
    src/ModuloDeTipos/DatoControlTriada.cpp \
    src/ModuloDeTipos/DatoTriada.cpp \
    src/ModuloParser/ParserArchivoTriadas.cpp \
    src/ModuloDeInterfaz/Instruccion_ConsultarEditorial.cpp \
    src/ModuloDeInterfaz/Instruccion_ConsultarAutor.cpp \
    src/ModuloDeIndices/ConsultaIndice.cpp \
    src/ModuloDeInterfaz/Instruccion_ConsultarTitulo.cpp \
    Common/FileManager.cpp \
    src/ModuloDeIndices/ArbolBMas/BPlusTree.cpp \
    src/ModuloDeIndices/ArbolBMas/InternalNode.cpp \
    src/ModuloDeIndices/ArbolBMas/LeafNode.cpp \
    src/ModuloDeIndices/ArbolBMas/Node.cpp \
    src/ModuloDeIndices/ArbolBMas/NodeFactory.cpp \
    src/ModuloDeIndices/ArbolBMas/Tree.cpp \
    src/ModuloDeIndices/ArbolBMas/tests.cpp \
    src/ModuloDeTipos/CaseFoldedString.cpp \
    src/ModuloEstructuras/Configuracion.cpp \
    src/ModuloDeIndices/Hash/TestHash.cpp \
    src/ModuloEstructuras/Libro.cpp \
    src/ModuloParser/ParserDeAutor.cpp \
    src/ModuloParser/ParserDeEditorial.cpp \
    src/ModuloParser/ParserDePalabras.cpp \
    src/ModuloParser/ParserDeTitulo.cpp \
    src/ModuloDeIndices/Indexador.cpp \
    src/ModuloControladores/ControladorIndice.cpp \
    src/ModuloControladores/ControladorBiblioteca.cpp \
    src/ModuloDeIndices/Hash/ElementoHash.cpp \
    src/ModuloDeTipos/DatoTablaHash.cpp \
    src/ModuloDeTipos/DatoCubetaHash.cpp \
    src/ModuloDeIndices/Hash/Hash.cpp \
    src/ModuloDeInterfaz/Instruccion_VerEstructura.cpp \
    src/ModuloDeTipos/DatoElementoNodo.cpp \
    src/ModuloDeInterfaz/Instruccion_QuitarArchivo.cpp \
    src/ModuloDeInterfaz/Instruccion_ObtenerArchivo.cpp \
    src/ModuloDeInterfaz/Instruccion_ListarArchivosTomados.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarPalabras.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarTitulo.cpp \
    src/ModuloDeInterfaz/Instruccion_TomarTexto.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarAutor.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarEditorial.cpp \
    src/ModuloDeInterfaz/Instruccion.cpp \
    src/ModuloDeInterfaz/ManejadorInstrucciones.cpp \
    src/ModuloDeTipos/FrontCodedString.cpp \
    src/ModuloParser/ParserAuxiliar.cpp \
    src/ModuloParser/ParserArchivoControl.cpp \
    src/ModuloParser/ParserDiccionario.cpp \
    src/ModuloDeArchivos/ArchivoLibro.cpp \
    src/ModuloDeArchivos/ArchivoControlLibro.cpp \
    src/ModuloDeTipos/DatoLibro.cpp \
    src/ModuloDeTipos/Dato.cpp \
    src/ModuloDeTipos/DatoControlLibro.cpp \
    src/ModuloDeArchivos/ManejadorArchivo.cpp \
    Common/Utilitarios/Logger.cpp \
    Common/Utilitarios/ServiceClass.cpp \
    src/ModuloEstructuras/Diccionario.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 
