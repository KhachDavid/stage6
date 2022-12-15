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

	// print out the parameters
	cout << "relation: " << relation << endl;

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
	status = outerScan.startScan(attrDesc.attrOffset,
								 attrDesc.attrLen,
								 type,
								 attrValue,
								 op);



	if (status != OK)
	{
		return status;
	}

	status = outerScan.deleteRecord();

	if (status != OK)
	{
		return status;
	}

	// scan outer table

	// delete the record that satisfies the comparison
	//while (outerScan.scanNext(outerRID) == OK)
	//{
//
	//	// get the record
	//	Record outerRec;
	//	status = outerScan.getRecord(outerRec);
//
	//	// check if the record satisfies the comparison
	//	// if the record satisfies the comparison, delete the record
	//	if (status == OK)
	//	{
	//		// get the value of the attribute
	//		char *value = (char *)outerRec.data + attrDesc.attrOffset;
//
	//		// check if the value is null
	//		if (value == NULL)
	//		{
	//			return ATTRTYPEMISMATCH;
	//		}
//
	//		// check if the value is the same as the value to be compared
	//		switch (type)
	//		{
	//		case STRING:
	//			if (strcmp(value, attrValue) == 0)
	//			{
	//				status = outerScan.deleteRecord();
	//				if (status != OK)
	//				{
	//					return status;
	//				}
	//			}
	//			break;
	//		case INTEGER:
	//			// print value and attrValue
	//			cout << "value: " << *(int *)value << endl;
	//			cout << "attrValue: " << *(int *)attrValue << endl;
	//			if (*(int *)value == *(int *)attrValue)
	//			{
	//				status = outerScan.deleteRecord();
	//				if (status != OK)
	//				{
	//					return status;
	//				}
	//			}
	//			break;
	//		case FLOAT:
	//			if (*(float *)value == *(float *)attrValue)
	//			{
	//				status = outerScan.deleteRecord();
	//				if (status != OK)
	//				{
	//					return status;
	//				}
	//			}
	//			break;
	//		default:
	//			return ATTRTYPEMISMATCH;
	//		}
	//	}
//
	//	if (status != OK)
	//	{
	//		return status;
	//	}
	//}

	return OK;
}
