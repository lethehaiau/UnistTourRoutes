#include <bits/stdc++.h>
using namespace std;
#define NUM_BLD 7

void loadData(map<int, int>& bldIndexMap, vector<int>& bldCodeMap, vector<int>& bldVisitTime, vector<vector<int> >& travelTime){
	freopen("../data/UnistTour.txt", "r", stdin);
	for(int i = 0; i < NUM_BLD; ++i){
		int bldCode;
		cin >> bldCode;
		bldCodeMap[i] = bldCode;
		bldIndexMap[bldCode] = i;
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

int calTourTime(const vector<int>& route, const vector<vector<int> >& travelTime, const vector<int>& bldVisitTime){
	int time = bldVisitTime[0];
	int previousBld = 0, currentBld = 0;
	for(int i = 0; i < NUM_BLD - 1; ++i){
		currentBld = route[i];
		time += travelTime[previousBld][currentBld];
		time += bldVisitTime[currentBld];
		previousBld = currentBld;
	}
	return time;
}

void addTourTime(vector<vector<int> >& routeList, const vector<vector<int> >& travelTime, const vector<int>& bldVisitTime){
	for(int i = 0; i < routeList.size(); ++i){
		int time = calTourTime(routeList[i], travelTime, bldVisitTime);
		routeList[i].push_back(time);
	}
}

bool cmp(const vector<int>& first, const vector<int>& second){
	return first[first.size() - 1] < second[second.size() - 1];
}

bool cmpval(int val, const vector<int>& element){
	return val < element[element.size() - 1];
}

int calOverLapTime(int firstArrivalTime, int secondArrivalTime, int visitTime){
	if(abs(firstArrivalTime - secondArrivalTime) >= visitTime) return 0;
	if(firstArrivalTime <= secondArrivalTime)
		return firstArrivalTime + visitTime - secondArrivalTime;
	else return secondArrivalTime + visitTime - firstArrivalTime;
}

int twoRoutesOverlapTime(const vector<int>& firstRoute, const vector<int>& secondRoute, 
	const vector<vector<int> >& travelTime, const vector<int> bldVisitTime){
	vector<vector<int> > arrivalTime(2);
	for(int routeNum = 0; routeNum < 2; ++routeNum){
		arrivalTime[routeNum].resize(NUM_BLD);
		int time = bldVisitTime[0];
		int previousBld = 0, currentBld = 0;
		for(int i = 0; i < NUM_BLD - 1; ++i){
			if(routeNum == 0) currentBld = firstRoute[i];
			else currentBld = secondRoute[i];
			time += travelTime[previousBld][currentBld];
			arrivalTime[routeNum][currentBld] = time;
			time += bldVisitTime[currentBld];
			previousBld = currentBld;
		}
	}
	int overlapTime = 0;
	for(int i = 1; i < NUM_BLD; ++i){
		overlapTime += calOverLapTime(arrivalTime[0][i], arrivalTime[1][i], bldVisitTime[i]);
	}

	return overlapTime;
}
void twoGroupsPlanner(vector<vector<int> >& twoRoutesList, const vector<vector<int> >& routeList,
	const vector<vector<int> >& travelTime, const vector<int> bldVisitTime){
	int num_route = routeList.size();
	for(int i = 0; i < num_route - 1; ++i){
		for(int j = i + 1; j < num_route; ++j){
			int time = twoRoutesOverlapTime(routeList[i], routeList[j], travelTime, bldVisitTime);
			twoRoutesList.push_back({i, j, time});
		}
	}
}
vector<int> threeGroupsMinOverlapTime(const vector<vector<int> >& twoRoutesList, const vector<vector<int> >& routeList,
	const vector<vector<int> >& travelTime, const vector<int> bldVisitTime){
	vector<int> optimalRoute(4, 0);
	int minOverlapTime = INT_MAX;
	for(int i = 0; i < twoRoutesList.size(); ++i){
		if(twoRoutesList[i][2] >= minOverlapTime) return optimalRoute;
		int firstRoute = twoRoutesList[i][0];
		int secondRoute = twoRoutesList[i][1];
		for(int thirdRoute = secondRoute + 1; thirdRoute < routeList.size(); ++thirdRoute){
			int overlapTime = twoRoutesList[i][2];
			overlapTime += twoRoutesOverlapTime(routeList[firstRoute], routeList[thirdRoute], travelTime, bldVisitTime);
			overlapTime += twoRoutesOverlapTime(routeList[secondRoute], routeList[thirdRoute], travelTime, bldVisitTime);
			minOverlapTime = min(minOverlapTime, overlapTime);
			if(overlapTime == 0){
				optimalRoute[0] = firstRoute;
				optimalRoute[1] = secondRoute;
				optimalRoute[2] = thirdRoute;
				optimalRoute[3] = minOverlapTime;
			}
		}
	}
	return optimalRoute;
}

vector<int> fourGroupsMinOverlapTime(const vector<vector<int> >& twoRoutesList, const vector<vector<int> >& routeList,
	const vector<vector<int> >& travelTime, const vector<int> bldVisitTime){
	vector<int> optimalRoute(5, 0);
	int minOverlapTime = INT_MAX;
	int count = 0;
	for(int i = 0; i < twoRoutesList.size() - 1; ++i)
		for(int j = i + 1; j < twoRoutesList.size(); ++j){
			if(twoRoutesList[i][2] + twoRoutesList[j][2] >= minOverlapTime){
				break;
			} 
			vector<int> fourRoutes;
			fourRoutes.push_back(twoRoutesList[i][0]);
			fourRoutes.push_back(twoRoutesList[i][1]);
			fourRoutes.push_back(twoRoutesList[j][0]);
			fourRoutes.push_back(twoRoutesList[j][1]);
			int overlapTime = 0;
			for(int u = 0; u < 3; ++u)
				for(int v = u + 1; v < 4; ++v){
					overlapTime += twoRoutesOverlapTime(routeList[fourRoutes[u]], routeList[fourRoutes[v]], travelTime, bldVisitTime);
				}
			if(overlapTime < minOverlapTime){
				minOverlapTime = overlapTime;
				optimalRoute = fourRoutes;
				optimalRoute[4] = minOverlapTime;
			}
			++count;
		}
	return optimalRoute;
}

void printRoute(const vector<int>& bldCodeMap, const vector<int>& route){
	cout << bldCodeMap[0];
	for(int i = 0; i < NUM_BLD - 1; ++i){
		cout << " " << bldCodeMap[route[i]];
	}
	cout << "\n";
}

void loadOriginalPlan(const map<int, int>& bldIndexMap, vector<vector<int> >& originThreeGroupsPlan, vector<vector<int> >& originFourGroupsPlan){
	ifstream originData("../data/originalPlan.txt");
	vector<int> route(NUM_BLD - 1, 0);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < NUM_BLD; ++j){
			int bldCode;
			originData >> bldCode;
			if(j > 0)
			route[j - 1] = bldIndexMap.find(bldCode)->second;
		}
		originThreeGroupsPlan.push_back(route);
	}
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < NUM_BLD; ++j){
			int bldCode;
			originData >> bldCode;
			if(j > 0)
			route[j - 1] = bldIndexMap.find(bldCode)->second;
		}
		originFourGroupsPlan.push_back(route);
	}
}

int main(){
	freopen("result.txt", "w", stdout);
	map<int, int> bldIndexMap;
	vector<int> bldCodeMap(NUM_BLD, 0);
	vector<int> bldVisitTime(NUM_BLD, 0);
	vector<vector<int> > travelTime;
	travelTime.resize(NUM_BLD);
	loadData(bldIndexMap, bldCodeMap, bldVisitTime, travelTime);
	vector<vector<int> > routeList;
	int initialRoute[] = {1, 2, 3, 4, 5, 6};
	vector<int> route(initialRoute, initialRoute + NUM_BLD - 1);
	routesGenerator(routeList, route);
	addTourTime(routeList, travelTime, bldVisitTime);
	sort(routeList.begin(), routeList.end(), cmp);

	//drop all the route has total travel time 10% longer than optimal route
	int optimalSingleRoute = routeList[0][routeList[0].size() - 1];
	int pivot = (upper_bound(routeList.begin(), routeList.end(), 
		round(optimalSingleRoute * 1.1), cmpval) - routeList.begin());
	routeList.resize(pivot);

	//two groups plan
	vector<vector<int> > twoRoutesList;
	twoGroupsPlanner(twoRoutesList, routeList, travelTime, bldVisitTime);
	sort(twoRoutesList.begin(), twoRoutesList.end(), cmp);
	cout << "Two Groups Plan:\n";
	cout << "total overlap time: " << twoRoutesList[0][2] << endl;
	printRoute(bldCodeMap, routeList[twoRoutesList[0][0]]);
	printRoute(bldCodeMap, routeList[twoRoutesList[0][1]]);

	//three groups plan
	vector<int> threeGroupsCase = threeGroupsMinOverlapTime(twoRoutesList, routeList, travelTime, bldVisitTime);
	cout << "Three Groups Plan:\n";
	cout << "total overlap time: " << threeGroupsCase[3] << endl;
	for(int i = 0; i < 3; ++i){
		printRoute(bldCodeMap, routeList[threeGroupsCase[i]]);
	}

	//four groups plan
	vector<int> fourGroupsCase = fourGroupsMinOverlapTime(twoRoutesList, routeList, travelTime, bldVisitTime);
	cout << "Four Groups Plan:\n";
	cout << "total overlap time: " << fourGroupsCase[4] << endl;
	for(int i = 0; i < 4; ++i){
		printRoute(bldCodeMap, routeList[fourGroupsCase[i]]);
	}
	vector<vector<int> > originThreeGroupsPlan;
	vector<vector<int> > originFourGroupsPlan;
	loadOriginalPlan(bldIndexMap, originThreeGroupsPlan, originFourGroupsPlan);
	
	int overlapTime = 0;
	for(int i = 0; i < 2; ++i){
		for(int j = i + 1; j < 3; ++j){
			overlapTime += twoRoutesOverlapTime(originThreeGroupsPlan[i], originThreeGroupsPlan[j],
				travelTime, bldVisitTime);
		}
	}
	//cout << overlapTime << endl;
	overlapTime = 0;
	for(int i = 0; i < 3; ++i){
		for(int j = i + 1; j < 4; ++j){
			overlapTime += twoRoutesOverlapTime(originFourGroupsPlan[i], originFourGroupsPlan[j],
				travelTime, bldVisitTime);
		}
	}
	//cout << overlapTime << endl;
	return 0;
}