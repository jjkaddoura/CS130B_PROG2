#include <iostream>
#include "payoff_sched.h"
using namespace std;

void Payoff_sched::printJobs(){
	for(int i = 0; i < jobs.size(); i++){
		printf("Job %d: start=%d end=%d pay=%d\n",i+1,jobs[i].start,jobs[i].end,jobs[i].pay);
	}
}

