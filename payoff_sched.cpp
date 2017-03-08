#include <iostream>
#include <cstdlib>
#include "payoff_sched.h"
using namespace std;

void Payoff_sched::printJobs(){
	for(int i = 0; i < jobs.size(); i++){
		printf("Job %d: start=%d end=%d pay=%d\n",i,jobs[i].start,jobs[i].end,jobs[i].pay);
	}
}

void Payoff_sched::quicksortEndTime(){
	quicksortEndTime(0,jobs.size());
}

void Payoff_sched::quicksortEndTime(int start, int end){
	int r;
	int partitionIndex;
	if(start < end){
		r = partition(start,end);
		quicksortEndTime(start,r);
		quicksortEndTime(r+1,end);
	}
}

int Payoff_sched::partition(int start, int end){
	int partitionIndex = start;
	int p = jobs[partitionIndex].end;
	int i = partitionIndex;
	for(int j = partitionIndex+1; j < end; j++){
		if(jobs[j].end <= p){
			i++;
			swap(i,j);
		}
	}
	if(jobs[i].end < jobs[partitionIndex].end && i > partitionIndex)
		swap(partitionIndex,i);
	return i;
}

void Payoff_sched::swap(int index1, int index2){
	Job tmp = jobs[index1];
	jobs[index1] = jobs[index2];
	jobs[index2] = tmp;
}


int Payoff_sched::calcMaxPayout(){
	quicksortEndTime();
	if(jobs.size() == 1) return jobs[0].pay;
	optimal[0] = jobs[0].pay;
	for(int i = 1; i < jobs.size(); i++){
		int latestNonconflict = findLatestNonconflictBefore(i); 
		int currentProfit = jobs[i].pay;
		cout << "At job: " << i << ", the latestNonconflict is: " << latestNonconflict << endl;
		if(latestNonconflict != -1){
			currentProfit += optimal[latestNonconflict];
		}
		optimal[i] = max(currentProfit, optimal[i-1]);

	}
	return optimal[jobs.size()-1];
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

int Payoff_sched::max(int a, int b){
	if(a > b) 
		return a;
	return b;
}