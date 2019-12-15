#ifndef _MATRIX
#define _MATRIX

// Класс матриц
class Matrix {
private:
	int rows;
	int cols;
	double ** matrix;

public:
	// Конструктор по умолчанию
	Matrix();

	// Конструктор с инициализацией полей
	Matrix(int _rows, int _cols);

	// Конструктор копирования
	Matrix(Matrix const & m);

	// Деструктор
	~Matrix();

	// Оператор присваивания
	Matrix & operator=(Matrix const & m);

	// Оператор индексации
	double * operator[](int n) const;

	// Случайная разреженная матрица
	void random();

	// Количество строк
	int rows_num() const;

	// Количество столбцов
	int cols_num() const;

	// Консольный вывод матрицы
	void console_out();
};

#endif // _MATRIX