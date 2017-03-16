#include "groupSamples.h"

void groupSamples(std::vector<std::vector<std::string> > &sampleListRepeatGroups){
	std::ifstream sampleListFile("sampleList.csv");
	std::string cellValue;

	std::vector<std::string> sampleList;
	for(int i=0, repeatGroup=0; i<827; ++i){
		std::getline(sampleListFile,cellValue,',');
		sampleList.push_back(cellValue);
		if((i+1)%4==0){
			++repeatGroup;
			sampleListRepeatGroups.push_back(sampleList);
			sampleList.clear();
		}			
	}
	std::getline(sampleListFile,cellValue,'\n');
	sampleList.push_back(cellValue);
	sampleListRepeatGroups.push_back(sampleList);
}