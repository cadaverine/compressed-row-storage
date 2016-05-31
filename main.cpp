#include <iostream>
#include <cstdlib> // srand()
#include <ctime>

#include "matrix.h"
#include "crs.h"


using namespace std;


int main()
{
	srand(time(NULL));


	cout << endl << "Исходная матрица: " << endl;

	Matrix m(6, 9);
	m.random();
	m.console_out();


	cout << "Разреженный строчный формат CRS (свертка): " << endl;

	CRS crs(m);
	crs.console_out();
	

	cout << "Развертка матрицы из CRS: " << endl;

	Matrix b = crs.expand_matrix();
	b.console_out();

	return 0;
}