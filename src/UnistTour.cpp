#include <bits/stdc++.h>
using namespace std;
#define NUM_BLD 7

void loadData(map<int, int>& bldCodeMap, vector<int>& bldVisitTime, vector<vector<int> >& travelTime){
	freopen("../data/UnistTour.txt", "r", stdin);
	for(int i = 0; i < NUM_BLD; ++i){
		int bldCode;
		cin >> bldCode;
		bldCodeMap[bldCode] = i;
		cin >> bldVisitTime[i];
	}

	for(int i = 0; i < NUM_BLD; ++i){
		for(int j = 0; j < NUM_BLD; ++j){
			int time;
			cin >> time;
			travelTime[i].push_back(time);
		}
	}
}

int main(){
	map<int, int> bldCodeMap;
	vector<int> bldVisitTime(NUM_BLD, 0);
	vector<vector<int> > travelTime;
	travelTime.resize(NUM_BLD);
	loadData(bldCodeMap, bldVisitTime, travelTime);
	return 0;
}