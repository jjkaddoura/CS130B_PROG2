#include <iostream>
#include <fstream>
#include <sstream>
#include "payoff_sched.h"
using namespace std;

int main(int argc, char** argv)
{

	Payoff_sched payoff;
	char input;
	string line;
	string arr[3];
	int i;

	while(getline(cin,line))
	{
		Job job;
		i = 0;
		stringstream str_stream(line);
		while(str_stream.good() && i < 3)
		{
			str_stream >> arr[i];
			i++;
		}
		try
		{
			job.start = stoi(arr[0]);
			job.end   = stoi(arr[1]);
			job.pay   = stoi(arr[2]);
		}
		catch(invalid_argument e)
		{
			printf("INVALID ARGUMENT ERROR\n");
			exit(1);
		}
		payoff.jobs.push_back(job);

	}

	payoff.optimal = new Node[payoff.jobs.size()];
	cout << "Max Payoff: " << payoff.calcMaxPayout() << endl;
	if(payoff.jobs.size() == 1){cout << payoff.jobs[0].start << " " << payoff.jobs[0].end << " " << payoff.jobs[0].pay << endl; return 0; }
	int iter = payoff.last; vector<Job> answers;
	while(iter >= 0){ if(payoff.optimal[iter].p.second != -1) answers.push_back(payoff.jobs[iter]);iter = payoff.optimal[iter].p.first; }
	for(int i = answers.size()-1; i >= 0; i--){ cout << answers[i].start << " " << answers[i].end << " " << answers[i].pay  << endl; }
	delete [] payoff.optimal;
	return 0;
}
