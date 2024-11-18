#ifndef WASH_H
#define WASH_H

#include <queue>
#include "car.h"

class WashCmp
{
private:
    std::queue<Car> carQueue;
    const static int FINISHAMOUNT;

    int numServedCars;
    int totalWaitingTime;
    double arrivalRate; // 到达率 λ
    double serviceRate; // 服务率 μ

    int getNextArrival(int currentTime); // 修改函数声明，接受一个参数
    void processArrivalNonEmptyQ(int currTime);
    void processArrivalEmptyQ(int currTime);
    void processDeparture();
    void processRemain();
public:
    WashCmp(); // 声明构造函数
    void simulation();
    void printStatistic();
    void setArrivalRate(double rate); // 设置到达率 λ
    void setServiceRate(double rate); // 设置服务率 μ
};

#endif