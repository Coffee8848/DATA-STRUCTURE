#include "car.h"
#include <iostream>
#include <cmath>
#include <cstdlib>


Car::Car()
{
    arrivalTime = 0;
    departureTime = 0;
    waitingTime = 0;
    serviceTime = generateServiceTime(); // 生成随机服务时间
}

Car::Car(int arrivalT)
{
    arrivalTime = arrivalT;
    departureTime = 0; //to be set later
    waitingTime = 0; //to be set later
    serviceTime = generateServiceTime(); // 生成随机服务时间
}

int Car::getArrivalTime()
{
    return arrivalTime;
}

int Car::getDepartureTime()
{
    return departureTime;
}

int Car::getWaitingTime()
{
    return waitingTime;
}

double Car::getServiceTime()
{
    return serviceTime;
}

void Car::setDepartAndWaitTime(int startServiceTime)
{
    departureTime = startServiceTime + static_cast<int>(serviceTime);
    waitingTime = startServiceTime - arrivalTime;
}

void Car::printCarDeparture()
{
    std::cout << "A car is washed and departs!\n";
    std::cout << "\tArrival time: " << arrivalTime << std::endl;
    std::cout << "\tDeparture time: " << departureTime << std::endl;
    std::cout << "\tWaiting time: " << waitingTime << std::endl;
    std::cout << "\tService time: " << serviceTime << std::endl;
}

void Car::printCarArrival()
{
    std::cout << "A car arrives!\n";
    std::cout << "\tArrival time: " << arrivalTime << std::endl;
}

double Car::generateServiceTime()
{
    double mu = 0.3; // 服务率，假设平均服务时间为10分钟
    double p;
    do {
        p = rand() / (RAND_MAX + 1.0); // 将 RAND_MAX 转换为 double 以避免整数溢出
    } while (p == 0); // 确保 p 不为 0，以避免 log(0) 的情况

    return -log(1 - p) / mu;
}