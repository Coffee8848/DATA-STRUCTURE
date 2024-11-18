#include "washCmp.h"
#include <iostream>
#include <random>

const int WashCmp::FINISHAMOUNT = 10; // 清洗车辆数量上限

WashCmp::WashCmp()
{
    totalWaitingTime = 0;
    numServedCars = 0;
    arrivalRate = 1.0; // 默认到达率 λ
    serviceRate = 1.0; // 默认服务率 μ
}

void WashCmp::setArrivalRate(double rate)
{
    arrivalRate = rate;
}

void WashCmp::setServiceRate(double rate)
{
    serviceRate = rate;
}

void WashCmp::printStatistic()
{
    std::cout << "Number of served cars: " << numServedCars << std::endl;
    std::cout << "Total waiting time: " << totalWaitingTime << std::endl;
    if (numServedCars > 0)
        std::cout << "The average waiting time is: " << (double)totalWaitingTime / numServedCars << std::endl;
    else
        std::cout << "The average waiting time is not applicable!" << std::endl;
}

void WashCmp::simulation()
{
    int currentTime = 0;
    int arrivalTime = getNextArrival(currentTime); // get the next arrival time from keyboard input

    while (numServedCars < FINISHAMOUNT)
    {
        std::cout << "Current number of served cars: " << numServedCars << std::endl;
        std::cout << "FINISHAMOUNT: " << FINISHAMOUNT << std::endl;

        if (carQueue.empty()) // queue empty, process arrival
        {
            processArrivalEmptyQ(arrivalTime);
            currentTime = arrivalTime;
            arrivalTime = getNextArrival(currentTime); // get next arrival
        }
        else if (arrivalTime < carQueue.front().getDepartureTime()) // arrival first, process arrival
        {
            processArrivalNonEmptyQ(arrivalTime);
            currentTime = arrivalTime;
            arrivalTime = getNextArrival(currentTime); // get next arrival
        }
        else // departure first or of the same time, process departure
        {
            processDeparture(); // no need to get next arrival
        }
    }

    // no more arrival, process the remaining cars in the queue
    processRemain();
}

int WashCmp::getNextArrival(int currentTime)
{
    static std::default_random_engine generator;
    std::exponential_distribution<double> distribution(arrivalRate);

    double deltaT = distribution(generator);
    int nextArrivalTime = currentTime + static_cast<int>(deltaT);

    std::cout << "Next arrival time interval: " << deltaT << ", Next arrival time: " << nextArrivalTime << std::endl;
    return nextArrivalTime;
}

void WashCmp::processArrivalEmptyQ(int arrivalTime)
{
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.setDepartAndWaitTime(arrivalTime); // set the departure and waiting time of the arrived car
    arrivedCar.printCarArrival(); // print the arrival information of the arrived car
    carQueue.push(arrivedCar); // set the arrival time of the arrived car
}

void WashCmp::processArrivalNonEmptyQ(int arrivalTime)
{
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.printCarArrival(); // print the arrival information of the arrived car
    carQueue.push(arrivedCar); // set the arrival time of the arrived car
}

void WashCmp::processDeparture()
{
    int currTime = carQueue.front().getDepartureTime(); // get the current time

    totalWaitingTime += carQueue.front().getWaitingTime(); // update statistics
    numServedCars++; // update statistics

    carQueue.front().printCarDeparture(); // print departure information
    carQueue.pop(); // departs

    if (!carQueue.empty()) // set the departure and waiting time of
        carQueue.front().setDepartAndWaitTime(currTime); // the current front car in the queue
}

void WashCmp::processRemain() // wash the remaining cars in the queue
{
    while (!carQueue.empty())
        processDeparture();
}