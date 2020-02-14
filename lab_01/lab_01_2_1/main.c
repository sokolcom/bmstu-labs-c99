// Задача 1.01

#include <stdio.h>
#include <math.h>

#define NO_ERROR 0


int main()
{
    float x1, y1, x2, y2, x3, y3;
    float a, b, c;
    
    printf("Calculate perimeter of the triangle\n\n");
    printf("Enter coordinates of the first vertex (x1, y1): \n");
    scanf("%f %f", &x1, &y1);
    printf("Enter coordinates of the second vertex (x2, y2): \n");
    scanf("%f %f", &x2, &y2);
    printf("Enter coordinates of the third vertex (x3, y3): \n");
    scanf("%f %f", &x3, &y3);


    a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    b = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));

    if ((a == b + c) || (b == a + c) || (c == a + b))
        printf("Entered triangle is degenerate");
    else
        printf("\nPerimeter of the triangle: %.5f", a + b + c);


    return NO_ERROR;
}
