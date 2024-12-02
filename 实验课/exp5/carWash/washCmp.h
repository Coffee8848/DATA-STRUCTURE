#ifndef WASH_H
#define WASH_H

#include <queue>
#include "car.h"

class WashCmp
{
private:
	std::queue<Car> carQueue;
	const static int Maxcars = 10;

	int numServedCars;
	int totalWaitingTime;
	double lambda;//到达率

	int getNextArrival(); //accept user input to get the next arrival time
	void processArrivalNonEmptyQ(int currTime); //a car arrives and the waiting queue is not empty
	void processArrivalEmptyQ(int currTime); //a car arrives and the waiting queue is empty
	void processDeparture();
	void processRemain(); //no more arriving cars, process the remaining cars in the waiting queue
	double generateInterArrivalTime();
public:
	WashCmp(double labmda);
	void simulation();
	void printStatistic();
};


#endif