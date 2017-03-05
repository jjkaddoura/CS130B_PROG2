#include <vector>
using namespace std;

#ifndef PAYOFF_SCHED_H
#define PAYOFF_SCHED_H


struct Job {
  int start;
  int end;
  int pay;
};

class Payoff_sched {

public:
	
	void printJobs();
	vector<Job> jobs;

private:	

	int payout;

};

#endif


