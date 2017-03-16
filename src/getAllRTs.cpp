#include "getAllRTs.h"

//A function which gets the retention times of all peptides, and sorts their vectors by the correct sample order

void getAllRTs(std::vector<std::vector<float> > &allRTs, std::vector<std::string> &rawNamesSorted){

	std::ifstream combiPeptDataFile("combiPeptData.csv");
	std::string cellValue;
		//std::getline(combiPeptDataFile,cellValue,'\n');

		//First we want to read in the list of sample names as they appear in combiPeptData (unsorted)
		//We can then use the IDs of this vector to know which RT to fill our allRTs vector with

		//Ignore first 35 columns since they don't contain retention time info
		for(int i=0; i<35; ++i){
			std::getline(combiPeptDataFile,cellValue,',');
		}
		std::vector<std::string> sampleNames;
		for(int i=0; i<882; ++i){
			std::getline(combiPeptDataFile,cellValue,',');
			sampleNames.push_back(cellValue);
		}
		std::getline(combiPeptDataFile,cellValue,'\n');
		sampleNames.push_back(cellValue);

	//Now get all RTs from combiPeptData. Remember, allRTs vector will be UNSORTED at this point
	for(int peptideNo=0; peptideNo<32322; ++peptideNo){
		//Ignore first 26 columns since they don't contain retention time info
		for(int i=0; i<26; ++i){
			std::getline(combiPeptDataFile,cellValue,'\"');
			std::getline(combiPeptDataFile,cellValue,'\"');
		}
		//Ignore the pFDR and MSMS ion columns
		std::getline(combiPeptDataFile,cellValue,',');
		std::getline(combiPeptDataFile,cellValue,',');
		//Ignore the next 6 columns
		for(int i=0; i<6; ++i){
			std::getline(combiPeptDataFile,cellValue,'\"');
			std::getline(combiPeptDataFile,cellValue,'\"');
		}
		std::getline(combiPeptDataFile,cellValue,',');
		//Ignore the blank column before the retention time columns
		std::getline(combiPeptDataFile,cellValue,',');

		std::vector<float> retentionTimes;
		for(int i=0; i<882; ++i){
			std::getline(combiPeptDataFile,cellValue,',');
			float rT = std::stod(cellValue.substr(1,cellValue.length()-2));
			retentionTimes.push_back(rT);
		}
		std::getline(combiPeptDataFile,cellValue,'\n');
		float rT = std::stod(cellValue.substr(1,cellValue.length()-2));
		retentionTimes.push_back(rT);
		allRTs.push_back(retentionTimes);
	}

	//Now we sort the allRTs vector based on the ordering of sample named from rawNamesSorted
	std::vector<std::vector<float> > allRTsSorted;
	for(int peptideNo=0, numPeptides=allRTs.size(); peptideNo<numPeptides; ++peptideNo){
		for(int sample=0, numSamples=allRTs[0].size(); sample<numSamples; ++sample){
			std::vector<float> RTs;
			for(int i=0; i<numSamples; ++i){
				if(rawNamesSorted[sample].compare(sampleNames[i])==0){
					RTs.push_back(allRTs[peptideNo][i]);
					break;
				}
			}
		}
	}
	allRTsSorted.swap(allRTs);

}