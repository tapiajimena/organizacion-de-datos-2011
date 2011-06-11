/*
 * DatoControlTriada.h
 *
 *	Autor	: GRUPO 1 - Fernandez, Gallinal, Maraggi, Tapia
 *	Catedra	: SERVETTO-FERRER-FERNANDEZ
 *	Materia	: Organizacion de Datos (75.06) - FIUBA
 *
 *	Representa el dato que va a usarse para el manejo de las triadas.
 *
 */

#ifndef DATOCONTROLTRIADA_H_
#define DATOCONTROLTRIADA_H_

#include "Dato.h"

class DatoControlTriada: public Dato {
private:
	/* Limite inferior del rango de triadas que pertenecen al mismo libro.
	 */
	uint32_t idTriadaInicial;

	/* Limite superior del rango de triadas que pertenecen al mismo libro.
	 */
	uint32_t idTriadaFinal;

	uint32_t idLibro;
	bool eliminado;
public:
	DatoControlTriada();

	/* Setters y Getters */
	bool getEliminado() const;
    uint32_t getIdLibro() const;
    uint32_t getIdTriadaFinal() const;
    uint32_t getIdTriadaInicial() const;
    void setEliminado(bool eliminado);
    void setIdLibro(uint32_t idLibro);
    void setIdTriadaFinal(uint32_t idTriadaFinal);
    void setIdTriadaInicial(uint32_t idTriadaInicial);

	virtual ~DatoControlTriada();
};

#endif /* DATOCONTROLTRIADA_H_ */
