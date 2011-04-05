TEMPLATE = app
TARGET = QT_Almacenamiento
QT += core
HEADERS += src/Tipos/Datos.h \
    src/Tipos/Bloque.h \
    src/Tipos/Bytes.h \
    src/Tipos/Registro.h \
    src/Tipos/RegistroFijo.h \
    src/Tipos/RegistroVariable.h \
    src/Almacenamiento/Almacenamiento.h \
    src/Almacenamiento/AlmacenamientoBloque.h
SOURCES += src/Tipos/Datos.cpp \
    src/Tipos/Bytes.cpp \
    src/Tipos/Bloque.cpp \
    src/Tipos/Registro.cpp \
    src/Tipos/RegistroFijo.cpp \
    src/Tipos/RegistroVariable.cpp \
    src/Almacenamiento/Almacenamiento.cpp \
    src/Almacenamiento/AlmacenamientoBloque.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 
