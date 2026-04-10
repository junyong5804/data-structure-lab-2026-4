#include "ImageArray.h"

int main()
{
    ImageArray img;

    img.print();
    printf("\nMax Pixel Value = %d\n", img.getMaxPixel());

    return 0;
}