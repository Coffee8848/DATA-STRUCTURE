#include <iostream>
using namespace std;

int fact(int n)
{
	if (n == 0)
		return 1;
	else
		return n * fact(n - 1);
}

int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}


int main()
{
	int n = 5;
	cout << "The factorial of " << n << " is: " << fact(n) << endl;

	int m = 7;
	cout << "The " << n << "th fibonacci number is: " << fib(m) << endl;
}
