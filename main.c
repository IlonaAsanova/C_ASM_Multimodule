#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "externs.c"
 
int cnt_iter; //count of iterations in function root
 
int n = 10; // begin iterations if integral
int flag = 0; //if something has calculated = -1/1, else = 0

double integr = 0, prev_integral = 0; // start for integrals
 
// r1, r2, r3, rh1, rh2, rh3 functions for test function root
 
double r1(double x) {
	double ans;
	ans = sqrt(x + 3);
	return ans;
}
 
double r2(double x) {
	double ans;
	ans = 0.5 * x * x * x - 13.0 / 4 * x * x;
	return ans;
}
 
double r3(double x) {
	double ans;
	ans = (-4) * x + 5.0 / 4;
	return ans;
}
 
// rhi = dri / dx
 
double rh1(double x) {
	double ans;
	ans = 1.0 / (2 * sqrt(x + 3));
	return ans;
}
 
double rh2(double x) {
	double ans;
	ans = 1.5 * x * x - 13.0 / 2 * x;
	return ans;
}
 
double rh3(double x) {
	double ans;
	ans = -4.0;
	return ans;
}
 
// i1, i2, i3 functions for test function integral
 
double i1(double x) {
	return x * x;	
}
 
double i2(double x) {
	return 3 * exp(x);
}
 
double i3(double x) {
	return 10 * x * x * x - 6 * x * x + 5 * x + 10;
}
 
double sub(double (*f)(double), double (*g)(double), 
	    double x) {
	return f(x) - g(x);
} 

double root(double (*f)(double), double (*g)(double),
		double (*df)(double), double (*dg)(double),
		double a, double b, double eps1) {
 
	cnt_iter = 0;
 
	double x1, x2, x0, d;
 
	do {
 
		cnt_iter++;
 
		x1 = a - (b - a) * sub(f, g, a) / (sub(f, g, b) - sub(f, g, a));
 
		if (sub(df, dg, a) * (sub(df, dg, a + eps1) - sub(df, dg, a)) < 0)
			x0 = a;
		else
			x0 = b;
 		
		cnt_iter++;

		d = sub(df, dg, x0);
		x2 = x0 - (d != 0) * sub(f, g, x0) / d;
		if (x1 > x2) {
 
			a = x2;
			b = x1;
 
		} else {
 
			a = x1;
			b = x2;
 
		}
 
 
	} while (fabs(sub(f, g, b) - sub(f, g, a)) >= eps1);
 
	return a;
 
}
 
double integral(double (*f)(double), double a, double b, double eps2)
{
    n *= 2;
    integr = 0;
    double q = (b - a) / n;
    double t = b - q;
    if (flag == 1) 	
	q *= 2;
    double temp = 0;
    while (t > a)
    {
        temp += f(t);
        t -= q;
    }
    if (flag == 0) 
	temp += f(a);
    temp *= q;
    if (flag == 1) 
	integr += temp / 2 + prev_integral / 2;
    else 
	integr += temp;
    if(fabs(integr - prev_integral) < eps2)
    {
        return integr;
    }
    prev_integral = integr;
    flag = 1;
    return integral(f, a, b, eps2);
}
 
/*
	root r1 = r2 is 6.640813
	root r1 = r3 is 0.112376
	roots r2 = r3 are 0.5, 1, 5
*/
 
void test(void) {
 
	printf("\n");
 
    printf("To exit the test, enter the command: 0\n");
    printf("A single test can't be completed ahead of schedule\n");
 
    int op, f1, f2;
    double res, a, b, eps;
 
    while (1) {
 
	printf("\n");
 
        printf("Select the function you want to test\n");
        printf("1 \t root\n2 \t integral\n0 \t finish\n");
        scanf("%d", &op);
        if (!op)
            break;
        else {
            if ( !(op >= 1 && op <= 2)) {
                printf("Sorry, we have only two functions and command finish\n");
                printf("Let's try again\n");
                continue;
            } else {
                if (op == 1) {
                    printf("Enter two function numbers for which you want to solve equation Fi(x) = Fj(x)\n");
                    printf("1 \t sqrt(x+3)\n2 \t 0.5x^3-3.25x^2\n3 \t -4x+1.25\n");
                    scanf("%d%d", &f1, &f2);
                    if ( !(f1 >= 1 && f1 <= 3 || f2 >= 1 && f2 <= 3)) {
                        printf("Sorry, we have only three functions\n");
                        printf("Let's try again\n");
                        continue;
                    } else {
                        printf("Enter the segment at which the root is interested\n");
                        printf("I remind you that the segment must be correct\n");
                        scanf("%lf%lf", &a, &b);
                        printf("Enter epsilon\n");
                        scanf("%lf", &eps);
                        if ((f1 == 1 && f2 == 2) || (f1 == 2 && f2 == 1))
                            res = root(r1, r2, rh1, rh2, a, b, eps);
                        if ((f1 == 1 && f2 == 3) || (f1 == 3 && f2 == 1))
                            res = root(r1, r3, rh1, rh3, a, b, eps);
                        if ((f1 == 2 && f2 == 3) || (f1 == 3 && f2 == 2))
                            res = root(r2, r3, rh2, rh3, a, b, eps);
                        if ( !(a <= res  && res <= b))
				printf("On [%lf, %lf] this equation has no root\n", a, b);
			else
                        	printf("Root in [%lf, %lf] is %lf\n", a, b, res);
 
                    }
                } else {
                    printf("Enter the function under the graph of which you want to calculate area\n");
                    printf("1 \t x^2\n2 \t 3e^x\n3 \t 10x^3-6x^2+5x+10\n");
                    scanf("%d", &f1);
                    if ( !(f1 >= 1 && f1 <= 3)) {
                        printf("Sorry, we have only three functions\n");
                        printf("Let's try again\n");
                        continue;
                    } else {
                        printf("Enter the integration segment\n");
                        //printf("I remind you that the segment must be correct\n");
                        scanf("%lf%lf", &a, &b);
                        printf("Enter epsilon\n");
                        scanf("%lf", &eps);
                        if (f1 == 1)
                            res = integral(i1, a, b, eps);
                        if (f1 == 2)
                            res = integral(i2, a, b, eps);
                        if (f1 == 3)
                            res = integral(i3, a, b, eps);
 
                        printf("Square under graph in [%lf; %lf] is %lf\n", a, b, res);
 
                    }
                }
            }
        }
    }
 
	printf("\n");
 
}
 
int main(int argc, char *argv[]) {
 
	int flag_root = 0, flag_iter = 0, flag_test = 0, flag_help = 0;
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-root"))
			flag_root = 1;
		else if (!strcmp(argv[i], "-iter"))
				flag_iter = 1;
			else if (!strcmp(argv[i], "-test"))
				flag_test = 1;
			else if(!strcmp(argv[i], "-help") && !flag_help) {
				printf("Commands:\n");
				printf("\t -root \t print roots\n");
				printf("\t -iter \t print number of iterations in function root\n");
				printf("\t -test \t function testing\n");
				flag_help = 1;
				return 0;
			} else {
				if (!strcmp(argv[i], "-help") && flag_help)
					continue;
				printf("I don't know command: %s\n", argv[i]);
			}
	}
 
	if (flag_test) {
		test();
		return 0;		
	}
 
	double root1, root2, root3;
 
	double eps1 = 0.00001, eps2 = 0.00025;
 
 
	root1 = root(F1, F2, H1, H2, 1.5, 2.0, eps1);
 
	if (flag_iter) {
		printf("Number of iterations when calculating ");
		printf("root of 3/((x-1)^2+1)=(x+1/2)^(1/2): %d\n", cnt_iter);
	}
 
	if (flag_root)
		printf("Root of 3/((x-1)^2+1)=(x+1/2)^(1/2): %lf\n", root1);
 
	root2 = root(F1, F3, H1, H3, -0.6, 0.0, eps1);
 
	if (flag_iter) {
		printf("Number of iterations when calculating ");
		printf("root of 3/((x-1)^2+1)=e^(-x): %d\n", cnt_iter);
	}
 
	if (flag_root)
		printf("Root of 3/((x-1)^2+1)=e^(-x): %lf\n", root2);
 
	root3 = root(F2, F3, H2, H3, 0.0, 0.5, eps1);
	if (flag_iter) {
		printf("Number of iterations when calculating ");
		printf("root of (x+1/2)^(1/2)=e^(-x): %d\n", cnt_iter);
	}
 
	if (flag_root)
		printf("Root of (x+1/2)^(1/2)=e^(-x): %lf\n", root3);
 
	double ans = 0.0;
	ans += integral(F1, root2, root1, eps2);
	n = 10;
	ans -= integral(F2, root3, root1, eps2);
	n = 10;
	ans -= integral(F3, root2, root3, eps2);
 
	printf("\n");
	printf("Resulting area is %lf\n", ans);
 
	return 0;
	
}
