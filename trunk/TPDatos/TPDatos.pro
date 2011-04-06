TEMPLATE = app
TARGET = TPDatos
QT += core
HEADERS += src/ModuloDeArchivos/ManejadorArchivo.h \
    Common/Utilitarios/Logger.h \
    Common/Utilitarios/ServiceClass.h \
    src/ModuloDeInterfaz/Libro.h \
    src/ModuloDeInterfaz/ParserDeLibros.h
SOURCES += src/ModuloDeArchivos/ManejadorArchivo.cpp \
    src/ModuloDeArchivos/ArchivoVariable.cpp \
    src/ModuloDeIndices/ArbolBMas/src/ArbolBMas.cpp \
    src/ModuloDeIndices/ArbolBMas/src/NodoArbol.cpp \
    src/ModuloDeIndices/ArbolBMas/src/NodoHojaArbol.cpp \
    src/ModuloDeIndices/ArbolBMas/src/NodoInternoArbol.cpp \
    src/ModuloDeTipos/Datos.cpp \
    src/ModuloDeTipos/Registro.cpp \
    src/ModuloDeTipos/RegistroFijo.cpp \
    src/ModuloDeTipos/RegistroVariable.cpp \
    Common/Utilitarios/Logger.cpp \
    Common/Utilitarios/ServiceClass.cpp \
    src/ModuloDeInterfaz/Libro.cpp \
    src/ModuloDeInterfaz/ParserDeLibros.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 
