#include "car.h"
#include "washCmp.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main()
{
    WashCmp cmp;

    double arrivalRate;
    cout << "请设置到达率 λ: ";
    cin >> arrivalRate;
    cmp.setArrivalRate(arrivalRate);

    double serviceRate;
    cout << "请设置服务率 μ: ";
    cin >> serviceRate;
    cmp.setServiceRate(serviceRate);

    cmp.simulation();
    cmp.printStatistic();

    return 0;
}