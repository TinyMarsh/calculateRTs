#include "getDeltaRTs.h"

std::vector<std::pair<float, float> > getDeltaRTs(int i, int j, const std::vector<std::vector<std::string> > &sampleListRepeatGroups, std::vector<std::vector<float> > &allRTs){
	std::vector<std::pair<float, float> > deltaRTs;
	for(int peptide=0, numPeptides=allRTs.size(); peptide<numPeptides; ++peptide){
		float RT1 = allRTs[peptide][i];
		float RT2 = allRTs[peptide][j];
		if(RT1!=0 && RT2!=0){
			std::pair<float, float> deltaRTPair;
			deltaRTPair.first() = RT1;
			deltaRTPair.second() = RT1-RT2;
			deltaRTs.push_back(deltaRTPair);
		}
	}

	return deltaRTs;
}