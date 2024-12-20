#include <ctime>
#include <cstdlib> 
#include <iostream>
using namespace std;

int main()
{
	//random number generation
	srand((unsigned int)time(0)); //seed

	cout << "Three random numbers: " << rand() << ", " << rand() << ", " << rand() << endl;
	cout << "Maximum random number: " << RAND_MAX << endl;


	//runtime analysis
	clock_t start_t, end_t, elapsed_t;

	start_t = clock();

	// code segment whose time cost is to be measured
	for (int i = 0; i < 100000000; i++);
	end_t = clock();

	elapsed_t = end_t - start_t; //in ticks (per second); milliseconds
	cout << "Clock ticks per second: " << CLOCKS_PER_SEC << endl;
	cout << "Time elapsed: " << elapsed_t << " (in ticks)" << endl;

	return 0;
}