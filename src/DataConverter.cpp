#include <bits/stdc++.h>
using namespace std;
#define NUM_BLD 7
#define NUM_ROAD 15

void convertData(){
	freopen("../data/in.txt", "r", stdin);
	freopen("../data/UnistTour.txt", "w", stdout);
	for(int i = 0; i < NUM_BLD; ++i){
		int bldCode;
		float time;
		cin >> bldCode >> time;
		cout << bldCode << " " << int(time*60) << endl;
	}

	for(int i = 0; i < NUM_BLD; ++i){
		for(int j = 0; j < NUM_BLD; ++j){
			float time;
			cin >> time;
			int formatedTime = trunc(time);
			formatedTime = formatedTime * 60 + round(time*100.0 - formatedTime*100.0);
			cout << formatedTime << " ";
		}
		cout << "\n";
	}
}

int main(){
	loadData();
	return 0;
}