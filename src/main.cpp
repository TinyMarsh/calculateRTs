// Pick best match sample based on linear fit and R-squared value
// Pick the best PSM based on regional mean of surrounding peptide RTs

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "getDeltaRTs.h"
#include "groupSamples.h"
#include "getAllRTs.h"

int main(){
	
	// We want to get the best match sample. Since this is likely to be one of the repeats we will only test each sample against each repeat (4 in the CTAM project)
	// Let's import the list of samples which have been organised into groups of repeats
	std::vector<std::vector<std::string> > sampleListRepeatGroups;
	groupSamples(sampleListRepeatGroups);

	// Read in the sample list to vectors with corresponding mzid vector
	std::vector<std::string> rawNames;
	std::vector<std::string> mzidNames;
	std::ifstream rawVsMzidFile("rawVsMzid.csv");
	std::string cellValue;
	for(int i=0; i<828; ++i){
		std::getline(rawVsMzidFile,cellValue,',');
		rawNames.push_back(cellValue);
		std::getline(rawVsMzidFile,cellValue,'\n');
		mzidNames.push_back(cellValue);		
	}

	// Read all retention times into a vector
	std::vector<std::vector<float> > allRTs; // RTs stored per peptide (not per sample)
	getAllRTs(allRTs, rawNames);

	// Now for each sample, find the best match sample in the group of repeats based on the R-squared of a linear fit
	for(int repeatGroup=0, numGroups=sampleListRepeatGroups.size(); repeatGroup<numGroups; ++repeatGroup){
		// Start by getting the pairwise delta-RT for every other sample in the repeat group
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j){
				if(!(i==j)&&!(i>j)){
					getDeltaRTs(i,j,sampleListRepeatGroups, allRTs);
				}
			}
		}
	}
/*
	for(int i=0, noGroups=sampleListRepeatGroups.size(); i<noGroups; ++i){
		for(int j=0; j<4; ++j){
			std::cout << sampleListRepeatGroups[i][j] << ",";
		}
		std::cout << std::endl;
	}
*/
}