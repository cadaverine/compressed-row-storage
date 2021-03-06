#include <iostream>
#include <iomanip> // setw()

#include "matrix.h"
#include "crs.h"

using namespace std;

// Конструктор по умолчанию
CRS::CRS() {}

// Конструктор копирования
CRS::CRS(CRS const &crs) : values_num(crs.vnum()), cols_num(crs.cnum()),
pointers_num(crs.pnum()), m_rows_num(crs.m_rows()), m_cols_num(crs.m_cols()) {
	cols 	 = new int	  [cols_num];
	values 	 = new double [values_num];
	pointers = new int	  [pointers_num];

	for (int i = 0; i < cols_num; i++) {
		cols[i] = crs.cols_r()[i];
	}

	for (int i = 0; i < values_num; i++) {
		values[i] = crs.values_r()[i];
	}

	for (int i = 0; i < pointers_num; i++) {
		pointers[i] = crs.pointers_r()[i];
	}
}

// Конструктор, принимающий матрицу в качестве аргумента
CRS::CRS(Matrix const &m) {
	collapse_matrix(m);
}

// Оператор присваивания
CRS & CRS::operator=(CRS const &crs) {
	if (this != &crs) {
		delete[] cols;
		delete[] values;
		delete[] pointers;

		values_num 	 = crs.vnum();
		cols_num 	 = crs.cnum();
		pointers_num = crs.pnum();
		m_cols_num   = crs.m_cols();
		m_rows_num   = crs.m_rows();

		for (int i = 0; i < cols_num; i++) {
			cols[i] = crs.cols_r()[i];
		}

		for (int i = 0; i < values_num; i++) {
			values[i] = crs.values_r()[i];
		}

		for (int i = 0; i < pointers_num; i++) {
			pointers[i] = crs.pointers_r()[i];
		}
	}
	return * this;
}

// Деструктор
CRS::~CRS() {
	delete[] cols;
	delete[] values;
	delete[] pointers;
}

// Свертка матрицы
void CRS::collapse_matrix(Matrix const &m) {
	m_cols_num = m.cols_num();
	m_rows_num = m.rows_num();

	// Считаем количество ненулевых элементов матрицы
	int num_of_values = 0;
	for (int i = 0; i < m_rows_num; i++) {
		for (int j = 0; j < m_cols_num; j++) {
			if (m[i][j] != 0) num_of_values++;
		}
	}

	// Создаем массивы разреженного строчного формата
	pointers_num = m_rows_num + 1;
	pointers = new int[pointers_num];

	values_num = num_of_values;
	values = new double[values_num];

	cols_num = num_of_values;
	cols = new int[cols_num];

	// Свертка исходной матрицы
	int counter = 0;
	pointers[0] = 0;

	for (int i = 0; i < m_rows_num; i++) {
		for (int j = 0; j < m_cols_num; j++) {
			if (m[i][j] != 0) {
				values[counter] = m[i][j];
				cols[counter] = j;
				counter++;
			}
		}
		pointers[i + 1] = counter;
	}
}

// Развертка матрицы
Matrix CRS::expand_matrix() {
	Matrix m(m_rows_num, m_cols_num);

	for (int i = 0; i < m_rows_num; i++) {
		for (int k = pointers[i]; k < pointers[i + 1]; k++) {
			m[i][cols[k]] = values[k];
		}
	}

	return m;
}

// Размер массива values
int CRS::vnum() const {
	return values_num;
}

// Размер массива cols
int CRS::cnum() const {
	return cols_num;
}

// Размер массива pointers
int CRS::pnum() const {
	return pointers_num;
}

// Указатель на массив values
double * CRS::values_r() const {
	return values;
}

// Указатель на массив cols
int * CRS::cols_r() const {
	return cols;
}

// Указатель на массив pointers
int * CRS::pointers_r() const {
	return pointers;
}

// Количество столбцов исходной матрицы
int CRS::m_cols() const {
	return m_cols_num;
}

// Количество строк исходной матрицы
int CRS::m_rows() const {
	return m_rows_num;
}

// Консольный вывод CRS
void CRS::console_out() {
	cout << endl << endl;

	cout << setw(11) << "Values:  ";
	for (int i = 0; i < values_num; i++) {
		cout << setw(4) << values[i];
	}
	cout << endl << endl;

	cout << setw(11) << "Cols:  ";
	for (int i = 0; i < cols_num; i++) {
		cout << setw(4) << cols[i];
	}
	cout << endl << endl;

	cout << setw(11) << "Pointers:  ";
	for (int i = 0; i < pointers_num; i++) {
		cout << setw(4) << pointers[i];
	}
	cout << endl << endl << endl << endl;
}
