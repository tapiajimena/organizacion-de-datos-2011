TEMPLATE = app
TARGET = TPDatos
QT += core
HEADERS += Common/Utilitarios/Logger.h \
    Common/Utilitarios/ServiceClass.h \
    src/ModuloDeInterfaz/Libro.h \
    src/ModuloDeInterfaz/ParserDeLibros.h
SOURCES += Common/Utilitarios/Logger.cpp \
    Common/Utilitarios/ServiceClass.cpp \
    src/ModuloDeInterfaz/Libro.cpp \
    src/ModuloDeInterfaz/ParserDeLibros.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 
