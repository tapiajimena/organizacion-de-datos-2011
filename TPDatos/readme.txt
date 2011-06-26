BOOQUERIO:
==========
Instalacion:
-------------
	+ El sistema utiliza las librerias Qt para el modulo de CaseFolding. 
	El grupo eligio utilizar esta libreria debido a los requeriminetos pedidos.
	para instalarlas por favor ejecute el comando:	apt-get install libqt4-dev
	+ El sistema cuenta con un archivo de configuracion conf.ini que se encuentra en
	la carpeta padre de la aplicacion; para indicar la ruta donde se depositan:
		*Archivo de stopwords.
		*Carpeta de trabajo.
		*Carpeta de reportes.
	  
	+ Una vez instalada la libreria de Qt y configurado puede ejecutar el comando 
	make.
	Ej:
		grupo1@grupo1-laptop:~/workspace/ make
		grupo1@grupo1-laptop:~/workspace/ ./TPDatos [-comando]

Configuracion:
-------------
	+ Cambiar el archivo conf.ini y setearlo bien. 
	Ej:
		#CARPETA_TRABAJO=Indices/
		#CARPETA_REPORTES=/home/NOMBRE_USUARIO/Escritorio/reportes/
		#ARCHIVO_STOPWORDS=doc/stopwordstest.txt


TESTS AUTOMATIZADOS:
====================

	+ Darle permisos de ejecucion al archivo test.sh mediante chmod a+x test.sh
	+ Correr test automatizados ejecutando el comando ./test.sh


COMANDOS:
=========

    Comandos 1er Etapa
    ------------------

    Archivo de configuración (con directorio de almacenamiento)
    * Tomar Texto: 
	  ./TPDatos -i "archivo de texto"
    * Procesar Editorial: 
	  ./TPDatos -e (procesa los no procesados)
    * Procesar Autor: 
	  ./TPDatos –a
    * Procesa Título: 
	  ./TPDatos –t
    * Procesa Palabras: 
	  ./TPDatos –p
    * Listar Archivos Tomados: 
	  ./TPDatos –l (muestra identificador, Título, Autor,

    * Obtener Archivo: 
	  ./TPDatos -o ID_Archivo
    * Quita Archivo: 
	  ./TPDatos -q ID_Archivo (se elminan las entradas en los otros índices)

    * Ver Estructura: Genera archivos en forma de texto plano, que describen las estructuras y contenidos de los archivos de almacenamiento 
    y control del sistema.
	./TPDatos -v [-e árbol de Editorial, -a árbol de Autor, -t hash de Título, -p hash de Palabra] "Nombre Archivo"

    * Nombre y estructuras para los archivos generados:
      Archivo de Estructura de control: "Nombre Archivo"_Índice,"Nombre Archivo"_tabla.
      Archivos de control de espacios libres: "Nombre Archivo"_libres.
      Archivos de bloques de datos: "Nombre Archivo"_datos.
      Estructura: para árboles la indicada en teórica. Separadores: Bloques con "|", Registros con ";", atributos con ",".

    Comandos 2da Etapa
    ------------------

    * Consultar Editorial: ./TPDatos -qe “Editorial”
    * Consultar Autor: ./TPDatos –qa “Autor”
    * Consultar Título: ./TPDatos –qt “Título”
    * Consultar Palabras: ./TPDatos –qp “Palabras para búsqueda por cercania y rankeada”
    * Ver Estructura: Genera archivos en forma de texto plano, que describen las
    estructuras y contenidos de los archivos de almacenamiento y control del
    sistema.
      ./TPDatos -v [-at Archivo de Términos, -ani Archivo de Norma Infinito, -aop Archivo de ocurrencia posicional, -li Listas Invertidas]
    "Nombre Archivo" Nombre y estructuras para los archivos generados:
    * Archivo de Términos: "Nombre Archivo"_Terminos
    * Archivo de Norma Infinito: "Nombre Archivo"_NormaInfinito.
    * Archivo de ocurrencia posicional: "Nombre_Archivo"_OcurrenciaPosicional.
    * Listas Invertidas: "Nombre_Archivo"_ListasInvertidas. Separadores: Bloques con "|", Registros con ";", atributos con ",".
