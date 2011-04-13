TEMPLATE = app
TARGET = TPDatos
QT += core
HEADERS += src/ModuloDeArchivos/ArchivoLibro.h \
	src/ModuloDeArchivos/ArchivoControlLibro.h \
   src/ModuloDeTipos/DatoLibro.h \
   src/ModuloDeTipos/DatoNodo.h \
   src/ModuloDeTipos/DatoControlLibro.cpp \
   src/ModuloDeTipos/Dato.h \
   src/ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.h \
   src/ModuloDeIndices/ArbolBMas/src/NodoArbol.h \
   src/ModuloDeArchivos/ManejadorArchivo.h \
   Common/Constantes.h \
   Common/Utilitarios/Logger.h \
   Common/Utilitarios/ServiceClass.h \
   src/ModuloDeInterfaz/Libro.h \
   src/ModuloDeInterfaz/ParserDeLibros.h \
   src/ModuloParser/ParserArchivoTexto.h \
   src/ModuloEstructuras/Diccionario.h
SOURCES += src/ModuloDeArchivos/ArchivoLibro.cpp \
   src/ModuloDeArchivos/ArchivoControlLibro.cpp \
   src/ModuloDeTipos/DatoLibro.cpp \
   src/ModuloDeTipos/DatoNodo.cpp \
   src/ModuloDeTipos/Dato.cpp \
   src/ModuloDeTipos/DatoControlLibro.cpp \
   src/ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.cpp \
   src/ModuloDeIndices/ArbolBMas/src/NodoArbol.cpp \
   src/ModuloDeArchivos/ManejadorArchivo.cpp \
   Common/Utilitarios/Logger.cpp \
   Common/Utilitarios/ServiceClass.cpp \
   src/ModuloDeInterfaz/Libro.cpp \
   src/ModuloDeInterfaz/ParserDeLibros.cpp \
   src/ModuloEstructuras/Diccionario.cpp \
   src/ModuloParser/ParserArchivoTexto.cpp \
   src/main.cpp
FORMS +=
RESOURCES +=