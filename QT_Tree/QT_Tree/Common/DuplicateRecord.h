/*
 * DuplicateRecord.h
 *
 *  Created on: 28/04/2010
 *      Author: sebastian
 */

#ifndef DUPLICATERECORD_H_
#define DUPLICATERECORD_H_

class DuplicateRecord: public exception {
	  virtual const char* what() const throw()
	  {
	    return "Record exist";
	  }
};

#endif /* DUPLICATERECORD_H_ */
