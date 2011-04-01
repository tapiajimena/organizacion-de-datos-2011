/*
 * OverflowdedBucketException.h
 *
 *  Created on: 24/04/2010
 *      Author: sebastian
 */

#ifndef OVERFLOWDEDBUCKETEXCEPTION_H_
#define OVERFLOWDEDBUCKETEXCEPTION_H_

class OverflowdedBucketException: public exception {
	  virtual const char* what() const throw()
	  {
	    return "The bucket exceeded it's maximum allowed size";
	  }
};

#endif /* OVERFLOWBUCKETEXCEPRION_H_ */
