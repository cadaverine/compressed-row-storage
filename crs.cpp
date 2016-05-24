#include <iostream>
#include <iomanip> // setw()

#include "matrix.h"
#include "crs.h"


using namespace std;

// Конструктор по умолчанию
CRS::CRS(){}

// Конструктор копирования
CRS::CRS(CRS const &crs)
// Инициализация полей до входа в тело конструктора
	: values_num(crs.vnum()), cols_num(crs.cnum()), pointers_num(crs.pnum())
{
	cols 	 = new int	  [cols_num];
	values 	 = new double [values_num];
	pointers = new int	  [pointers_num];

	for (int i = 0; i < cols_num; i++)
	{
		cols[i] = crs.cols_r()[i];
	}

	for (int i = 0; i < values_num; i++)
	{
		values[i] = crs.values_r()[i];
	}

	for (int i = 0; i < pointers_num; i++)
	{
		pointers[i] = crs.pointers_r()[i];
	}
}

// Конструктор, принимающий матрицу в качестве аргумента
CRS::CRS(Matrix const &m)
{
	// Считаем количество ненулевых элементов матрицы
	int num_of_values = 0;
	for (int i = 0; i < m.rows_num(); i++)
	{
		for (int j = 0; j < m.cols_num(); j++)
		{
			if (m.matr()[i][j] != 0) num_of_values++;
		}
	}
	// Создаем массивы разреженного строчного формата
	pointers_num = m.rows_num() + 1;
	pointers = new int[pointers_num];

	values_num = num_of_values;
	values = new double[values_num];

	cols_num = num_of_values;
	cols = new int[cols_num];

	// Свертка исходной матрицы
	int counter = 0;
	pointers[0] = 0;

	for (int i = 0; i < m.rows_num(); i++)
	{
		for (int j = 0; j < m.cols_num(); j++)
		{
			if (m.matr()[i][j] != 0)
			{
				values[counter] = m.matr()[i][j];
				cols[counter] = j;
				counter++;
			}
		}
		pointers[i + 1] = counter;
	}
}

// Оператор присваивания
CRS & CRS::operator=(CRS const &crs)
{
	if (this != &crs)
	{
		delete[] cols;
		delete[] values;
		delete[] pointers;

		values_num 	 = crs.vnum();
		cols_num 	 = crs.cnum();
		pointers_num = crs.pnum();

		for (int i = 0; i < cols_num; i++)
		{
			cols[i] = crs.cols_r()[i];
		}

		for (int i = 0; i < values_num; i++)
		{
			values[i] = crs.values_r()[i];
		}

		for (int i = 0; i < pointers_num; i++)
		{
			pointers[i] = crs.pointers_r()[i];
		}
	}
	return * this;
}

// Деструктор
CRS::~CRS()
{
	delete[] cols;
	delete[] values;
	delete[] pointers;
}

// Свертка матрицы
void CRS::collapse_matrix(Matrix const &m)
{
	delete[] cols;
	delete[] values;
	delete[] pointers;

	// Считаем количество ненулевых элементов матрицы
	int num_of_values = 0;
	for (int i = 0; i < m.rows_num(); i++)
	{
		for (int j = 0; j < m.cols_num(); j++)
		{
			if (m.matr()[i][j] != 0) num_of_values++;
		}
	}
	// Создаем массивы разреженного строчного формата
	pointers_num = m.rows_num() + 1;
	pointers = new int[pointers_num];

	values_num = num_of_values;
	values = new double[values_num];

	cols_num = num_of_values;
	cols = new int[cols_num];

	// Свертка исходной матрицы
	int counter = 0;
	pointers[0] = 0;

	for (int i = 0; i < m.rows_num(); i++)
	{
		for (int j = 0; j < m.cols_num(); j++)
		{
			if (m.matr()[i][j] != 0)
			{
				values[counter] = m.matr()[i][j];
				cols[counter] = j;
				counter++;
			}
		}
		pointers[i + 1] = counter;
	}
}

// Развертка матрицы
Matrix CRS::expand_matrix()
{
	int rows = pointers_num - 1;
	int columns = 0;

	for (int i = 0; i < cols_num; i++)
	{
		if (columns < cols[i]) columns = cols[i];
	}
	columns++;

	Matrix m(rows, columns);

	for (int i = 0; i < m.rows_num(); i++)
	{
		for (int k = pointers[i]; k < pointers[i + 1]; k++)
		{
			m.matr()[i][cols[k]] = values[k];
		}
	}
	
	return m;
}

// Размер массива values
int CRS::vnum() const
{
	return values_num;
}

// Размер массива cols
int CRS::cnum() const
{
	return cols_num;
}

// Размер массива pointers
int CRS::pnum() const
{
	return pointers_num;
}

// Указатель на массив values
double * CRS::values_r() const
{
	return values;
}

// Указатель на массив cols
int * CRS::cols_r() const
{
	return cols;
}

// Указатель на массив pointers
int * CRS::pointers_r() const
{
	return pointers;
}

// Консольный вывод CRS
void CRS::console_out()
{
	cout << endl << endl;

	cout << setw(11) << "Values:  ";
	for (int i = 0; i < values_num; i++)
	{
		cout << setw(4) << values[i];
	}
	cout << endl << endl;

	cout << setw(11) << "Cols:  ";
	for (int i = 0; i < cols_num; i++)
	{
		cout << setw(4) << cols[i];
	}
	cout << endl << endl;

	cout << setw(11) << "Pointers:  ";
	for (int i = 0; i < pointers_num; i++)
	{
		cout << setw(4) << pointers[i];
	}
	cout << endl << endl;

	cout << endl << endl;
}
