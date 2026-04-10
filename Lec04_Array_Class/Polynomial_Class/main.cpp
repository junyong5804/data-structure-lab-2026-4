#include "Polynomial.h"

int main()
{
    Polynomial a, b, c;

    a.read("Polynomial a");
    b.read("Polynomial b");

    printf("\n");
    a.print("a(x) = ");
    b.print("b(x) = ");

    c.add(a, b);
    c.print("c(x) = a(x) + b(x) = ");

    printf("\nAfter negate\n");
    c.negate();
    c.print("c(x) = ");

    return 0;
}
