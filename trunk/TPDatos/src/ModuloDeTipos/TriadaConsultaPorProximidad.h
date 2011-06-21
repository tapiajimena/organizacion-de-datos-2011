#ifndef TRIADA_CONSULTA_POR_PROXIMIDAD_H_
#define TRIADA_CONSULTA_POR_PROXIMIDAD_H_

struct TriadaConsultaPorProximidad {
	uint32_t id_libro;
	double proximidad;
	int orden;
};

struct ComparadorTriadaConsultaPorProximidad {
	bool operator()(const TriadaConsultaPorProximidad* lhs,
			const TriadaConsultaPorProximidad* rhs) const{
		if (lhs->orden > rhs->orden) {
			return true;
		} else if (lhs->orden == rhs->orden) {
			return (lhs->proximidad > rhs->proximidad);
		} else {
			return false;
		}
	}
};

#endif /* TRIADA_CONSULTA_POR_PROXIMIDAD_H_ */
