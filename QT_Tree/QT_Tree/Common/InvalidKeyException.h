/*
 * InvalidKeyException.h
 *
 *  Created on: 22/04/2010
 *      Author: sebastian
 */

#ifndef INVALIDKEYEXCEPTION_H_
#define INVALIDKEYEXCEPTION_H_

class InvalidKeyException: public exception {
	  virtual const char* what() const throw()
	  {
	    return "The record is invalid";
	  }
};

#endif /* INVALIDKEYEXCEPTION_H_ */
