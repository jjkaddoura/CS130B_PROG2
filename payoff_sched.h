#include <vector>

#ifndef PAYOFF_SCHED_H
#define PAYOFF_SCHED_H


struct Job {
  int start;
  int end;
  int pay;

  Job& operator=(const Job &j){
  	this->start = j.start;
  	this->end = j.end;
  	this->pay = j.pay;
  	return *this;
  }
};

class Payoff_sched {

public:
	
	///////////////////
	/// METHODS
	///////////////////
	int calcMaxPayout();
	int calcMaxPayout(int start, int end);
	int findLatestNonconflicting(int index);
	void printJobs();
	void quicksortEndTime();
	void quicksortEndTime(int start, int end);
	int partition(int start, int end);
	void swap(int index1, int index2);

	///////////////////
	/// MEMBERS
	///////////////////
	std::vector<Job> jobs;
	Job* optimal;

private:	

	int payout;

};

#endif


