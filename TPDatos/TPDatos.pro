TEMPLATE = app
TARGET = TPDatos
QT += core
HEADERS += src/ModuloDeIndices/ArbolBMas/src/TestArbol.h \
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
    src/ModuloDeIndices/ArbolBMas/src/FabricaDeNodos.h \
    src/ModuloDeInterfaz/ParserDeAtributo.h \
    src/ModuloDeInterfaz/ParserDeAutor.h \
    src/ModuloDeInterfaz/ParserDeEditorial.h \
    src/ModuloDeInterfaz/ParserDePalabras.h \
    src/ModuloDeInterfaz/ParserDeTitulo.h \
    src/ModuloDeTipos/FrontCodedString.h \
    src/ModuloDeArchivos/ControladorBiblioteca.h \
    src/ModuloParser/ParserAuxiliar.h \
    src/ModuloParser/ParserArchivoControl.h \
    src/ModuloParser/ParserDiccionario.h \
    src/ModuloDeArchivos/ArchivoLibro.h \
    src/ModuloDeArchivos/ArchivoControlLibro.h \
    src/ModuloDeTipos/DatoLibro.h \
    src/ModuloDeTipos/DatoNodo.h \
    src/ModuloDeTipos/DatoControlLibro.cpp \
    src/ModuloDeTipos/Dato.h \
    src/ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h \
    src/ModuloDeIndices/ArbolBMas/src/NodoHojaArbol.h \
    src/ModuloDeIndices/ArbolBMas/src/NodoArbol.h \
    src/ModuloDeArchivos/ManejadorArchivo.h \
    Common/Constantes.h \
    Common/Utilitarios/Logger.h \
    Common/Utilitarios/ServiceClass.h \
    src/ModuloDeInterfaz/Libro.h \
    src/ModuloEstructuras/Diccionario.h
SOURCES += src/ModuloDeInterfaz/Instruccion_VerEstructura.cpp \
    src/ModuloDeInterfaz/Instruccion_QuitarArchivo.cpp \
    src/ModuloDeInterfaz/Instruccion_ObtenerArchivo.cpp \
    src/ModuloDeInterfaz/Instruccion_ListarArchivosTomados.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarPalabras.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarTitulo.cpp \
    src/ModuloDeInterfaz/Instruccion_TomarTexto.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarAutor.cpp \
    src/ModuloDeInterfaz/Instruccion_ProcesarEditorial.cpp \
    src/ModuloDeInterfaz/Instruccion.cpp \
    src/ModuloDeIndices/ArbolBMas/src/FabricaDeNodos.cpp \
    src/ModuloDeInterfaz/ParserDeAutor.cpp \
    src/ModuloDeInterfaz/ParserDeEditorial.cpp \
    src/ModuloDeInterfaz/ParserDePalabras.cpp \
    src/ModuloDeInterfaz/ParserDeTitulo.cpp \
    src/ModuloDeInterfaz/ManejadorInstrucciones.cpp \
    src/ModuloDeTipos/FrontCodedString.cpp \
    src/ModuloDeArchivos/ControladorBiblioteca.cpp \
    src/ModuloParser/ParserAuxiliar.cpp \
    src/ModuloParser/ParserArchivoControl.cpp \
    src/ModuloParser/ParserDiccionario.cpp \
    src/ModuloDeArchivos/ArchivoLibro.cpp \
    src/ModuloDeArchivos/ArchivoControlLibro.cpp \
    src/ModuloDeTipos/DatoLibro.cpp \
    src/ModuloDeTipos/DatoNodo.cpp \
    src/ModuloDeTipos/Dato.cpp \
    src/ModuloDeTipos/DatoControlLibro.cpp \
    src/ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.cpp \
    src/ModuloDeIndices/ArbolBMas/src/NodoHojaArbol.cpp \
    src/ModuloDeIndices/ArbolBMas/src/NodoArbol.cpp \
    src/ModuloDeArchivos/ManejadorArchivo.cpp \
    Common/Utilitarios/Logger.cpp \
    Common/Utilitarios/ServiceClass.cpp \
    src/ModuloDeInterfaz/Libro.cpp \
    src/ModuloEstructuras/Diccionario.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 
