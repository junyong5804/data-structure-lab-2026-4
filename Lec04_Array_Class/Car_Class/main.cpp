#include "SportsCar.h"

int main()
{
    Car c1(50, "Avante", 3);
    SportsCar s1(80, "Porsche", 5, false);

    printf("=== Car Object ===\n");
    c1.display();
    c1.speedUp();
    c1.changeGear();
    c1.display();
    c1.whereAmI();

    printf("\n=== SportsCar Object ===\n");
    s1.display();
    s1.speedUp();
    s1.display();

    s1.setTurbo(true);
    s1.speedUp();
    s1.display();
    s1.whereAmI();

    return 0;
}