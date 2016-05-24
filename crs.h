#ifndef _CRS
#define _CRS


#include "matrix.h"

// Класс "разреженный строчный формат" (хранение матриц)
class CRS
{
private:
	int values_num;
	int cols_num;
	int pointers_num;

	double * values;
	int * cols;
	int * pointers;

public:
	// Конструктор по умолчанию
	CRS();

	// Конструктор копирования
	CRS(CRS const &crs);

	// Конструктор, принимающий матрицу в качестве аргумента
	CRS(Matrix const &m);

	// Деструктор
	~CRS();

	// Оператор присваивания
	CRS & operator=(CRS const &crs);

	// Свертка матрицы
	void collapse_matrix(Matrix const &m);

	// Развертка матрицы
	Matrix expand_matrix();

	// Размер массива values
	int vnum() const;

	// Размер массива cols
	int cnum() const;

	// Размер массива pointers
	int pnum() const;

	// Указатель на массив values
	double * values_r() const;

	// Указатель на массив cols
	int * cols_r() const;

	// Указатель на массив pointers
	int * pointers_r() const;

	// Консольный вывод CRS
	void console_out();
};


#endif // _CRS