#ifndef POSICIONES_MAS_PROXIMAS_TERMINO_H_
#define POSICIONES_MAS_PROXIMAS_TERMINO_H_

struct PosicionesMasProximasTermino {
	long posicionMasProximaTerminoAnterior;
	long posicionMasProximaTerminoPosterior;
	long posicionActualTermino;
	inline bool operator < (const PosicionesMasProximasTermino &rhs) const{
		if ((posicionMasProximaTerminoAnterior == -1) && (posicionMasProximaTerminoPosterior == -1)){
			
			return false;
			
		} else if ((posicionMasProximaTerminoPosterior == -1) && (rhs.posicionMasProximaTerminoPosterior == -1)){
			
			return ((posicionActualTermino - posicionMasProximaTerminoAnterior)
				<(rhs.posicionActualTermino - rhs.posicionMasProximaTerminoAnterior));
				
		} else if ((posicionMasProximaTerminoAnterior == -1) && (rhs.posicionMasProximaTerminoAnterior == -1)){
			
			return ((posicionMasProximaTerminoPosterior - posicionActualTermino)
				<(rhs.posicionMasProximaTerminoPosterior - rhs.posicionActualTermino));
		} else {
			if (posicionMasProximaTerminoAnterior == -1) {
			
				return false;
			} else if (posicionMasProximaTerminoPosterior == -1){ 

				return false;
			} else {
				return ((posicionMasProximaTerminoPosterior - posicionMasProximaTerminoAnterior)
					< (rhs.posicionMasProximaTerminoPosterior - rhs.posicionMasProximaTerminoAnterior));
			}
			
		}
	}
};

#endif /* POSICIONES_MAS_PROXIMAS_TERMINO_H_ */
