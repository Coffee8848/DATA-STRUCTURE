#include "washCmp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

WashCmp::WashCmp(double lambda) : lambda(lambda)
{
    totalWaitingTime = 0;
    numServedCars = 0;
}

void WashCmp::printStatistic()
{
    std::cout << "Number of served cars: " << numServedCars << std::endl;
    std::cout << "Total waiting time: " << totalWaitingTime << std::endl;
    if(numServedCars > 0)
        std::cout << "The average waiting time is: " << (double)totalWaitingTime / numServedCars << std::endl;
    else
        std::cout << "The average waiting time is not applicable!" << std::endl;
}

void WashCmp::simulation()
{
    int arrivalTime = getNextArrival(); // 获取第一个车辆的到达时间

    while(numServedCars < Maxcars) // 循环直到达到最大洗车数量
    {
        if (carQueue.empty()) // 队列为空，处理到达事件
        {
            processArrivalEmptyQ(arrivalTime);
            arrivalTime = getNextArrival(); // 获取下一个车辆的到达时间
        }
        else if (arrivalTime < carQueue.front().getDepartureTime()) // 到达事件先于离开事件，处理到达事件
        {
            processArrivalNonEmptyQ(arrivalTime);
            arrivalTime = getNextArrival(); // 获取下一个车辆的到达时间
        }
        else // 离开事件先于或等于到达事件，处理离开事件
        {
            processDeparture(); // 处理离开事件，不需要获取下一个到达时间
        }
    }

    // 没有更多的到达事件，处理队列中剩余的车辆
    processRemain();
}

int WashCmp::getNextArrival()
{
    static int currentTime = 0;
    double interArrivalTime = generateInterArrivalTime();
    currentTime += static_cast<int>(interArrivalTime);
    return currentTime;
}

double WashCmp::generateInterArrivalTime()
{
    double p;
    do {
        p = rand() / (RAND_MAX + 1.0); // 将 RAND_MAX 转换为 double 以避免整数溢出
    } while (p == 0); // 确保 p 不为 0，以避免 log(0) 的情况

    return -log(1 - p) / lambda;
}

void WashCmp::processArrivalEmptyQ(int arrivalTime)
{
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.setDepartAndWaitTime(arrivalTime); // 设置到达车辆的离开时间和等待时间
    arrivedCar.printCarArrival(); // 打印到达车辆的信息
    carQueue.push(arrivedCar); // 将到达车辆加入队列
}

void WashCmp::processArrivalNonEmptyQ(int arrivalTime)
{
    Car arrivedCar = Car(arrivalTime);
    arrivedCar.printCarArrival(); // 打印到达车辆的信息
    carQueue.push(arrivedCar); // 将到达车辆加入队列
}

void WashCmp::processDeparture()
{
    int currTime = carQueue.front().getDepartureTime(); // 获取当前时间

    totalWaitingTime += carQueue.front().getWaitingTime(); // 更新统计数据
    numServedCars++; // 更新统计数据

    carQueue.front().printCarDeparture(); // 打印离开车辆的信息
    carQueue.pop(); // 车辆离开

    if (!carQueue.empty())                                 // 设置队列中当前前端车辆的离开时间和等待时间
        carQueue.front().setDepartAndWaitTime(currTime);
}

void WashCmp::processRemain() // 处理队列中剩余的车辆
{
    while (!carQueue.empty())
        processDeparture();
}