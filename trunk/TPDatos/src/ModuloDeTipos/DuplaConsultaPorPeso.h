#ifndef DUPLA_CONSULTA_POR_PESO_H_
#define DUPLA_CONSULTA_POR_PESO_H_

typedef struct {
	uint32_t id_libro;
	float similitud;
} DuplaConsultaPorPeso;

typedef struct {
	bool operator()
		(const DuplaConsultaPorPeso* lhs,
			const DuplaConsultaPorPeso* rhs) const{
		return (lhs->similitud > rhs->similitud);
	}
} ComparadorDuplaConsultaPorPeso;

#endif /* DUPLA_CONSULTA_POR_PESO_H_ */
