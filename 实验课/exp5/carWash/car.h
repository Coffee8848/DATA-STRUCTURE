#ifndef CAR_H
#define CAR_H

class Car
{
private:
    int arrivalTime;
    int departureTime;
    int waitingTime;
    double serviceTime; // 添加服务时间成员变量

public:
    Car();
    Car(int arrivalT);

    int getArrivalTime();
    int getDepartureTime();
    int getWaitingTime();
    double getServiceTime(); // 添加获取服务时间的方法

    void setDepartAndWaitTime(int currTime); // 修改方法签名
    void printCarDeparture();
    void printCarArrival();
	double generateServiceTime();
};

#endif