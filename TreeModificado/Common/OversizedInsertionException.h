/*
 * OverSizeBucketInsertionExeption.h
 *
 *  Created on: 24/04/2010
 *      Author: sebastian
 */

#ifndef OVERSIZEDINSERTIONEXEPTION_H_
#define OVERSIZEDINSERTIONEXEPTION_H_

class OversizedInsertionException: public exception {
	  virtual const char* what() const throw()
	  {
	    return "The record to insert exceeded it's maximum allowed size";
	  }
};

#endif /* OVERSIZEBUCKETINSERTIONEXEPTION_H_ */
