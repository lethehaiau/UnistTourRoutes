#include <bits/stdc++.h>
using namespace std;
#define NUM_BLD 7

void loadData(vector<int>& bldCodeMap, vector<int>& bldVisitTime, vector<vector<int> >& travelTime){
	freopen("../data/UnistTour.txt", "r", stdin);
	for(int i = 0; i < NUM_BLD; ++i){
		int bldCode;
		cin >> bldCode;
		bldCodeMap[i] = bldCode;
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

//Heap algorithm
//generate all routes which are permutation of 6 blds

void routesGenerator(vector<vector<int> >& routeList, vector<int>& route){
	vector<int> stackState(NUM_BLD - 1, 0);
	routeList.push_back(route);
	int i = 0;
	while(i < NUM_BLD - 1){
		if(stackState[i] < i){
			if(i % 2 == 0) swap(route[0], route[i]);
			else swap(route[stackState[i]], route[i]);
			routeList.push_back(route);
			stackState[i]++;
			i = 0;
		}
		else stackState[i++] = 0;
	}
}

int main(){
	vector<int> bldCodeMap(NUM_BLD, 0);
	vector<int> bldVisitTime(NUM_BLD, 0);
	vector<vector<int> > travelTime;
	travelTime.resize(NUM_BLD);
	loadData(bldCodeMap, bldVisitTime, travelTime);
	vector<vector<int> > routeList;
	int initialRoute[] = {1, 2, 3, 4, 5, 6};
	vector<int> route(initialRoute, initialRoute + NUM_BLD - 1);
	routesGenerator(routeList, route);
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < NUM_BLD - 1; ++j)
			cout << routeList[i][j] << " ";
		cout << endl;
	}
	return 0;
}