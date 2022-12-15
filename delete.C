#include "catalog.h"
#include "query.h"

/*
 * Deletes records from a specified relation.
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */

const Status QU_Delete(const string &relation,
					   const string &attrName,
					   const Operator op,
					   const Datatype type,
					   const char *attrValue)
{
	Status status;
	// enum Datatype { STRING, INTEGER, FLOAT };    // attribute data types
	// enum Operator { LT, LTE, EQ, GTE, GT, NE };  // scan operators

	// map operator to enum Operator value where op is mapped by the array index
	// Operator opMap[] = {LT, LTE, EQ, GTE, GT, NE};
	// type is mapped by the array index
	// Datatype typeMap[] = {STRING, INTEGER, FLOAT};

	// attrName is the name of the attribute to be used in the comparison
	// relation is the name of the relation to be scanned

	// attrValue is the value to be used in the comparison using the Operator op

	// scan the relation
	// for each record in the relation
	// 	if the record satisfies the comparison
	// 		delete the record

	// add null value check
	if (attrValue == NULL)
	{
		return ATTRTYPEMISMATCH;
	}

	// get AttrDesc structure for the attribute
	AttrDesc attrDesc;
	status = attrCat->getInfo(relation.c_str(),
							  attrName.c_str(),
							  attrDesc);

	if (status != OK)
	{
		return status;
	}

	// check if the type of the attribute is the same as the type of the value
	if (attrDesc.attrType != type)
	{
		return ATTRTYPEMISMATCH;
	}

	


	// open the relation
	HeapFileScan outerScan(relation, status);
	if (status != OK)
	{
		return status;
	}

	// start scan on outer table
	status = outerScan.startScan(0,
								 0,
								 type,
								 NULL,
								 op);

	if (status != OK)
	{
		return status;
	}

	// scan outer table
	RID outerRID;

	// delete the record that satisfies the comparison
	while (outerScan.scanNext(outerRID) == OK)
	{
		status = outerScan.deleteRecord();
		if (status != OK)
		{
			return status;
		}
	}

	return OK;
}
