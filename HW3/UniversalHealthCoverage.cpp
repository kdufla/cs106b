/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);
bool check(Set<string>& cities, Vector< Set<string> >& result);

int main() {
    /* TODO: Add testing code here! */
    return 0;
}


bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations,int numHospitals, Vector< Set<string> >& result){
	if(numHospitals==0) return check(cities,result);
	foreach(Set<string> curLocation in locations){
		result.add(curLocation);
		Vector<Set<string> > elseLocs;
		foreach(Set<string> cL in locations)
			if(cL!=curLocation)
				elseLocs += cL;
		if(canOfferUniversalCoverage(cities, elseLocs, numHospitals-1, result))return true;
		result.remove(result.size()-1);	
	}
	return false;
}

bool check(Set<string>& cities, Vector< Set<string> >& result){
	Set<string> c;
	foreach(Set<string> cur in result)
		c += cur;
	return cities.isSubsetOf(c);
}

