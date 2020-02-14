#include <stdio.h>
#include <math.h>

#define SUCCESS 0
#define INPUT_ERROR 1
#define INCORRECT_VAR 2

#define ZERO 0
#define ONE 1
#define NUMERATOR_DIFF 2
#define VARS 2


double f(double x)
{
    return (ONE / sqrt(ONE - x * x));
}


double s(double x, double eps)
{
    double function = 0;
    double fraction = 1;
    double numerator = 1;

    while (fabs(fraction) > eps)
    {
        function += fraction;
        fraction = fraction * x * x * numerator / (numerator + ONE);
        numerator += NUMERATOR_DIFF;
    }

    return function;
}


double abs_error(double f_x, double s_x)
{
    return fabs(f_x - s_x);
}


double rel_error(double absol_er, double f_x)
{
    return fabs(absol_er / f_x);
}

int main()
{
    double x;
    double eps;

    int check = scanf("%lf %lf", &x, &eps);

    if (check == VARS)
    {
        if ((fabs(x) < ONE) && (eps > ZERO) && (eps <= ONE))
        {
            double real = f(x);
            double approx = s(x, eps);

            double absolute = abs_error(real, approx);
            double relative = rel_error(absolute, real);

            printf("%lf\n", approx);
            printf("%lf\n", real);
            printf("%lf\n", absolute);
            printf("%lf\n", relative);

            return SUCCESS;
        }
        else
        {
            printf("Error in varriables.");
            return INCORRECT_VAR;
        }
    }
    else
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }
}
