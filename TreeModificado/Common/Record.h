/*
 * Record.h
 *
 *  Created on: Apr 7, 2010
 *      Author: igor
 */

#ifndef RECORD_H_
#define RECORD_H_

#include <list>
#include <algorithm>
#include "Comparable.h"
#include "Serializable.h"
#include <string.h>
#include <sstream>

#include <iomanip>

using namespace std;

class Record : public Serializable, public Comparable {
private:
	char* data;
	int key;
	int dataSize;
	string setTabs(int level);

public:
	Record();
	Record(int key);
	Record(int key, char* data);
	virtual ~Record();

	Record* clone();
	void serialize(iostream* ios);
	void deserialize(iostream* ios);
	void edit(int key, iostream* ios);

	int getKey();
	int getSize() const;
	char* getData();
	void setData(char *data);
	void setKey(int key);
	void setDataSize(int size);
	int getDataSize();

	/*
	 * Compares actual record with an external record.
	 * Returns:
	 * -1 if actual record is less than external
	 * 0 if they are equal
	 * 1 if actual is greater than external
	 *
	 * */
	int compareTo(void* external);
	void toString(iostream* ios, int rootLevel);
	string toString();
	void toStringXML(iostream* ios, int rootLevel);
	string setTabsXML(int level);


};


#endif /* RECORD_H_ */
