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


struct Node {
	int val;
	std::string opt;
	Node(){
		val = 0;
		opt = "";
	}
};

class Payoff_sched {

public:
	
	///////////////////
	/// METHODS
	///////////////////
	static bool sortByEndTime(const Job &j1, const Job &j2){ return j1.end < j2.end; }
	int calcMaxPayout();
	int calcMaxPayout(int start, int end);
	int findLatestNonconflictBefore(int index);
	void printJobs();
	int max(int a, int b);
	void quicksortEndTime();
	void quicksortEndTime(int start, int end);
	int partition(int start, int end);
	void swap(int index1, int index2);

	///////////////////
	/// MEMBERS
	///////////////////
	std::vector<Job> jobs;
	Node* optimal;


};


#endif


