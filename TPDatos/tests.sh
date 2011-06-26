 #
 #
 # test.sh
 # dar permisos de ejecucion con: chmod x+a test.sh
 #
 #	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 #	Catedra	: SERVETTO-FERRER-FERNANDEZ
 #	Materia	: Organizacion de Datos (75.06) - FIUBA
 #
 #
 #

rm Indices/*.* 2> /dev/null
rm reportes/*.* 2> /dev/null
mkdir Indices 2> /dev/null
mkdir reportes 2> /dev/null
clear
echo "Se ingresaran los textos de prueba"
read -p "Pulse una tecla para continuar...."
echo ""
echo ""
echo "Insertando libro 1"
./TPDatos -i doc/prueba1.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Insertando libro 2"
./TPDatos -i doc/prueba2.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Insertando libro 3"
./TPDatos -i doc/prueba3.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Insertando libro 4"
./TPDatos -i doc/prueba4.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Insertando libro 5"
./TPDatos -i doc/prueba5.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Insertando libro 6"
./TPDatos -i doc/prueba6.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Insertando libro 7"
./TPDatos -i doc/prueba7.txt
echo ""
read -p "Pulse una tecla para continuar...."
echo ""
echo "Fin del ingreso de textos de pruebas"
read -p "Pulse una tecla para continuar...."
clear
echo "Se listan los libros tomados"
echo ""
./TPDatos -l
echo ""
echo "Fin del listado de libros"
read -p "Pulse una tecla para continuar...."
clear
echo "Generacion de indices"
echo ""
echo "Se generan los indices por autor"
./TPDatos -a
read -p "Pulse una tecla para continuar...."
echo ""
echo "Se generan los indices por editorial"
./TPDatos -e
read -p "Pulse una tecla para continuar...."
echo ""
echo "Se generan los indices por titulo"
./TPDatos -t
echo ""
echo ""
echo "Fin del ingreso de la generacion de indices"
read -p "Pulse una tecla para continuar...."
clear
echo "Realizacion de consultas"
echo ""
echo "Prueba indice por autor"
./TPDatos -qa "Asimoov"
read -p "Pulse una tecla para continuar...."
echo ""
echo "Prueba indice por editorial"
./TPDatos -qe "Samsung"
read -p "Pulse una tecla para continuar...."
echo ""
echo "Prueba indice por titulo"
./TPDatos -qt "La torre Oscura"
read -p "Pulse una tecla para continuar...."
echo ""
echo "Prueba por terminos proximos"
./TPDatos -qp "hola como estas"
read -p "Pulse una tecla para continuar...."
echo ""
echo ""
echo "Fin de las consultas"
read -p "Pulse una tecla para continuar...."
clear
echo "Se generaran los archivos de reporte"
echo ""
echo "Archivo de terminos"
./TPDatos -v -at "Reporte"
read -p "Pulse una tecla para continuar...."
echo "Archivo de normas infinito"
./TPDatos -v -ani "Reporte"
read -p "Pulse una tecla para continuar...."
echo "Archivo de triadas"
./TPDatos -v -aop "Reporte"
read -p "Pulse una tecla para continuar...."
echo "Archivo de arbol"
./TPDatos -v -li "Reporte"
echo ""
echo ""
echo "Fin de las pruebas automatizadas"
read -p "Pulse una tecla para continuar...."
clear
