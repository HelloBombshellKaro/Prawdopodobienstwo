#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

const int N = 20000;

int m;
int s;

void printN();
void interpret(string);
double getNormal(double);
double simpsonsMetod(double, double);

int main()
{
	m = 0;
	s = 1;
	printN();
	string str;

	while (getline(cin,str))
	{
		interpret(str);
	}
	return 0;
}

void interpret(string str)
{
	stringstream ss(str);
	string op;
	double a1, a2;
	ss >> op;
	ss >> a1;
	if (op.compare("Both") == 0)
	{
		ss >> a2;
		m = a1;
		s = a2;
		printN();
	}
	else if (op.compare("Mean") == 0)
	{
		m = a1;
		printN();
	}
	else if (op.compare("Std") == 0)
	{
		s = a1;
		printN();
	}
	else if (op.compare("Over") == 0)
	{
		ss >> a2;
		printf("%f\n", simpsonsMetod(a1, a2));
	}
	else if (op.compare("Final") == 0)
	{
		printf("%f\n", simpsonsMetod(m, a1) + 0.5);
	}
	else if (op.compare("Initial") == 0)
	{
		double ret = simpsonsMetod(a1, m);
		ret += 0.5;
		printf("%f\n", ret);
	}
	else if (op.compare("Outside") == 0)
	{
		ss >> a2;
		printf("%f\n", 1.0 - simpsonsMetod(a1, a2));
	}
	else if (op.compare("N") == 0)
	{
		printf("%f\n", getNormal(a1));
	}
}

void printN()
{
	printf("N(%i,%i)\n", m, s);
}

double getNormal(double x)
{
	return (1.0 / (sqrt(2.0 * M_PI) * (double)s)) * exp( - pow(x - (double)m, 2.0) / (2.0 * pow((double)s, 2.0)));
}

double simpsonsMetod(double a, double b)
{
	double H = (b - a) / N;
	double ret = 0;
	for (int i = 1; i < N; i += 2)
	{
		double x = a + i * H;
		ret += 4 * abs(getNormal(x));
	}
	for (int i = 2; i < N - 1; i += 2)
	{
		double x = a + i * H;
		ret += 2 * abs(getNormal(x));
	}
	return (1.0 / 3.0) * H * ((getNormal(a) + getNormal(b)) + ret);
}