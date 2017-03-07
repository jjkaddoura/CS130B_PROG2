#include <iostream>
#include <cstdlib>
#include "payoff_sched.h"
using namespace std;

void Payoff_sched::printJobs(){
	for(int i = 0; i < jobs.size(); i++){
		printf("Job %d: start=%d end=%d pay=%d\n",i+1,jobs[i].start,jobs[i].end,jobs[i].pay);
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
		quicksortEndTime(start,r-1);
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
	return calcMaxPayout(0, jobs.size()/2) + calcMaxPayout(jobs.size()/2,jobs.size()-1);
}

int Payoff_sched::calcMaxPayout(int start, int end){
	if(end-start <= 1) return jobs[start].pay;
	int i;
	for(i = end; i >= start; i--){
		int latestNonconflict = findLatestNonconflicting(i); 
		cout << "At index: " << i << ", the latestNonconflict is: " << latestNonconflict << endl;
	}
	return -1;
}

int Payoff_sched::findLatestNonconflicting(int index){
	if(index == 0) return 0;
	int high = index-1;
	int low = 0;
	int i;
	int startTime = jobs[index].start;
	
	while(low <= high){
		int mid = (low+high)/2;
		if(jobs[mid].end <= startTime){
			if(jobs[mid+1].end < startTime)
				low = mid+1;
			else
				return mid;
		}
		else
			high = mid-1;
	}
	return -1;
}