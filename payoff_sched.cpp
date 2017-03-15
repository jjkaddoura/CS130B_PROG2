#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "payoff_sched.h"
using namespace std;

void Payoff_sched::printJobs(){
	for(int i = 0; i < jobs.size(); i++){
		printf("Job %d: start=%d end=%d pay=%d\n",i,jobs[i].start,jobs[i].end,jobs[i].pay);
	}
}

int Payoff_sched::calcMaxPayout(){
	sort(&jobs[0],&jobs[jobs.size()], sortByEndTime);
	if(jobs.size() == 1) return jobs[0].pay;
	optimal[0].val = jobs[0].pay;
	last = 0; optimal[0].p = make_pair(-1,0);
	for(int i = 1; i < jobs.size(); i++){
		int latestNonconflict = findLatestNonconflictBefore(i); 
		int currentProfit = jobs[i].pay;
		if(latestNonconflict != -1){
			currentProfit += optimal[latestNonconflict].val;
		}
		if(currentProfit > optimal[i-1].val){
			optimal[i].val = currentProfit;
			last = i;
			if(latestNonconflict != -1) optimal[i].p = make_pair(latestNonconflict, i);
			else optimal[i].p = make_pair(-1,i);
		}
		else{
			optimal[i].val = optimal[i-1].val; optimal[i].p = make_pair(i-1,-1);
		}
	}
	return optimal[jobs.size()-1].val;
}

int Payoff_sched::findLatestNonconflictBefore(int index){
	if(index == 0) return 0;
	int max = index-1;
	int min = 0;
	int i;
	int startTime = jobs[index].start;
	while(min <= max){
		int mid = (min+max)/2;
		if(jobs[mid].end <= startTime){
			if(jobs[mid+1].end <= startTime)
				min = mid+1;
			else
				return mid;
		}
		else
			max = mid-1;
	}
	return -1;
}
