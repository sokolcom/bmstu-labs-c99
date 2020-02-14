// Задача 2.02

#include <stdio.h>
#include <stdbool.h>

#define EIGHT_VAR 8 // количество переменных на вводе
#define ZERO 0 
#define NO_ERROR 0
#define ERROR_1 1
#define ERROR_2 2



bool does_intersects(float ax, float ay, float bx, float by, float px, float py, float nx, float ny)
{
    float x, y;
    float p_x, p_y;
    float n_x, n_y;
    float vector_1, vector_2;

    x = bx - ax;
    y = by - ay;

    p_x = px - ax;
    p_y = py - ay;

    n_x = nx - ax;
    n_y = ny - ay;

    vector_1 = x * p_y - p_x * y;
    vector_2 = x * n_y - n_x * y;

    if (vector_1 * vector_2 < ZERO)
        return true;
    else
        return false;
}


int main()
{
    float ax, ay;
    float bx, by;
    float cx, cy;
    float dx, dy;
    int check;

    printf("Enter coordinates of the first line segment and then second "
        "(ax, ay, bx, by, cx, cy, dx, dy):\n");
    check = scanf("%f %f %f %f %f %f %f %f", &ax, &ay, &bx, &by, &cx, &cy, &dx, &dy);

    if (check != EIGHT_VAR)
    {
        printf("Invalid input!");
        return ERROR_1;
    }
    else
    {
        if (((ax == bx) && (ay == by)) || ((cx == dx) && (cy == dy)))
        {
            printf("Invalid input!");
            return ERROR_2;
        }
        else
        {
            if (does_intersects(ax, ay, bx, by, cx, cy, dx, dy) &&
                does_intersects(cx, cy, dx, dy, ax, ay, bx, by))
                printf("1");
            else
                printf("0");

            return NO_ERROR;
        }
    }
}
