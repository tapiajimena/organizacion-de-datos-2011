/*
 * oversizedRecord.h
 *
 *  Created on: 21/04/2010
 *      Author: leandro
 */

#ifndef OVERSIZEDRECORDEXCEPTION_H_
#define OVERSIZEDRECORDEXCEPTION_H_

class OversizedRecordException: public exception {
	  virtual const char* what() const throw()
	  {
	    return "The record exceeded it's maximum allowed size";
	  }
};



#endif /* OVERSIZEDRECORDEXCEPTION_H_ */
