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
	payoff.quicksortEndTime();
	payoff.printJobs();
	cout << endl;
	cout << "The max payout is: " << payoff.calcMaxPayout() << endl;
	return 0;
}
