#pragma once
#include <cstdio>

class Polynomial
{
    int degree;
    int coef[20];

public:
    Polynomial()
    {
        degree = 0;
        for (int i = 0; i < 20; i++)
            coef[i] = 0;
    }

    void read(const char* msg = "Polynomial input")
    {
        printf("[%s]\n", msg);
        printf("degree = ");
        scanf_s("%d", &degree);

        for (int i = 0; i <= degree; i++)
        {
            printf("coef[%d] = ", i);
            scanf_s("%d", &coef[i]);
        }
    }

    void print(const char* msg = "Polynomial = ")
    {
        printf("%s", msg);

        bool first = true;

        for (int i = 0; i <= degree; i++)
        {
            if (coef[i] == 0)
                continue;

            int power = degree - i;
            int value = coef[i];

            if (!first && value > 0)
                printf(" + ");

            if (value < 0)
            {
                if (first) printf("-");
                else printf(" - ");
            }

            int absValue = (value < 0) ? -value : value;

            if (!(absValue == 1 && power != 0))
                printf("%d", absValue);

            if (power > 0)
            {
                printf("x");
                if (power > 1)
                    printf("^%d", power);
            }

            first = false;
        }

        if (first)
            printf("0");

        printf("\n");
    }

    void add(Polynomial a, Polynomial b)
    {
        if (a.degree > b.degree)
        {
            *this = a;
            for (int i = 0; i <= b.degree; i++)
                coef[i + (degree - b.degree)] += b.coef[i];
        }
        else
        {
            *this = b;
            for (int i = 0; i <= a.degree; i++)
                coef[i + (degree - a.degree)] += a.coef[i];
        }
    }

    bool isZero()
    {
        if (degree != 0)
            return false;
        return coef[0] == 0;
    }

    void negate()
    {
        for (int i = 0; i <= degree; i++)
            coef[i] = -coef[i];
    }
};