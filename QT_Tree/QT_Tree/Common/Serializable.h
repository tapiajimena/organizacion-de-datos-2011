/*
 * Serializable.h
 *
 *  Created on: Apr 7, 2010
 *      Author: igor
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <iostream>

using namespace std;

class Serializable{

public:
	virtual void  serialize(iostream* ios)=0;
	virtual void deserialize(iostream* record)=0;
};


#endif /* SERIALIZABLE_H_ */
