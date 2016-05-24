#include <iostream>
#include <iomanip> // setw()
#include <cstdlib> // rand()

#include "matrix.h"


using namespace std;


// Конструктор по умолчанию
Matrix::Matrix(){}

// Конструктор с инициализацией полей
Matrix::Matrix(int _rows, int _cols)
{
	rows = _rows;
	cols = _cols;

	// Создаем двумерный массив 
	matrix = new double * [rows];
	matrix[0] = new double[rows * cols];
	for (int i = 1; i < rows; i++)
	{
		matrix[i] = matrix[i - 1] + cols;
	}

	// Заполняем матрицу нулями по умолчанию.
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

// Конструктор копирования
Matrix::Matrix(Matrix const & m)
{
	rows = m.rows_num();
	cols = m.cols_num();

	// Создаем двумерный массив 
	matrix = new double * [rows];
	matrix[0] = new double[rows * cols];
	for (int i = 1; i < rows; i++)
	{
		matrix[i] = matrix[i - 1] + cols;
	}

	// Копируем значения
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = m.matr()[i][j];
		}
	}
}

Matrix::~Matrix()
{
	// Освобождаем память из под двумерного массива
	delete[] matrix[0];
	delete[] matrix;
}

// Оператор присваивания
Matrix & Matrix::operator=(Matrix const & m)
{
	if(this != &m)
	{
		delete[] matrix[0];
		delete[] matrix;

		rows = m.rows_num();
		cols = m.cols_num();

		matrix    = new double * [rows];
		matrix[0] = new double   [rows * cols];

		for (int i = 1; i < rows; i++)
		{
			matrix[i] = matrix[i - 1] + cols;
		}


		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j] = m.matr()[i][j];
			}
		}
	}
	return * this;
}

// Случайная разреженная матрица
void Matrix::random()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if ( rand() % 2 == 0  && rand() % 3 != 0 )
			{
				if ( rand() % 2 != 0 ) matrix[i][j] = 	  rand() % 20;
				if ( rand() % 2 == 0 ) matrix[i][j] = - ( rand() % 20 );
			}
		}
	}
}

// Количество строк
int Matrix::rows_num() const
{
	return rows;
}

// Количество столбцов
int Matrix::cols_num() const
{
	return cols;
}

// Указатель на матрицу
double ** Matrix::matr() const
{
	return matrix;
}

// Консольный вывод матрицы
void Matrix::console_out()
{
	cout << endl << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(4) << matrix[i][j];
		}
		cout << endl << endl;
	}
	cout << endl;
}
