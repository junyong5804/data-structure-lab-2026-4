#pragma once
#include "Car.h"

class SportsCar : public Car
{
public:
    bool bTurbo;

    SportsCar() : Car()
    {
        bTurbo = false;
    }

    SportsCar(int s, const char* n, int g, bool t) : Car(s, n, g)
    {
        bTurbo = t;
    }

    void setTurbo(bool bTur)
    {
        bTurbo = bTur;
    }

    void speedUp()
    {
        if (bTurbo)
            speed += 20;
        else
            Car::speedUp();
    }
};

