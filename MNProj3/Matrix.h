#pragma once
#include <iostream>
using namespace std;
class matrix {
private:
	double** Matrix;
public:
	int rows;
	int columns;
	void newMatrix(int a1, int a2, int a3) {
		for (int i = 0; i < rows - 2; i++) {
			for (int j = 0; j < columns - 2; j++) {
				if (i == j) {
					Matrix[i][j] = a1;
					Matrix[i + 1][j] = a2;
					Matrix[i][j + 1] = a2;
					Matrix[i + 2][j] = a3;
					Matrix[i][j + 2] = a3;
				}
			}
		}
		Matrix[rows - 2][columns - 2] = a1;
		Matrix[rows - 1][columns - 1] = a1;
		Matrix[rows - 1][columns - 2] = a2;
		Matrix[rows - 2][columns - 1] = a2;
	}
	static double norm(matrix Matrix) {
		double value = 0.0;
		for (int i = 0; i < Matrix.rows; i++) value += pow(Matrix[i][0], 2);
		return sqrt(value);
	}
	void allocMemory() {
		Matrix = new double* [rows];
		for (int i = 0; i < rows; i++) Matrix[i] = new double[columns];
	}
	void swapRows(int first, int second) {
		for (int k = 0; k < columns; k++) {
			swap(Matrix[first][k], Matrix[second][k]);
		}
	}
	matrix() : rows(1), columns(1) {
		allocMemory();
		Matrix[0][0] = 0;
	}
	matrix(int rows, int columns) {
		this->rows = rows;
		this->columns = columns;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Matrix[i][j] = 0;
			}
		}
	}
	matrix(const matrix& Matrix1) {
		this->rows = Matrix1.rows;
		this->columns = Matrix1.columns;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Matrix[i][j] = Matrix1[i][j];
			}
		}
	}
	~matrix() {
		for (int i = 0; i < rows; i++) delete[] Matrix[i];
		delete[] Matrix;
	}
	matrix& operator=(const matrix& Matrix1) {
		if (this == &Matrix1) return *this;
		this->~matrix();
		this->rows = Matrix1.rows;
		this->columns = Matrix1.columns;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Matrix[i][j] = Matrix1[i][j];
			}
		}
		return *this;
	}
	matrix& operator+=(const matrix& Matrix1)
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Matrix[i][j] += Matrix1[i][j];
			}
		}
		return *this;
	}
	matrix& operator-=(const matrix& Matrix1)
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Matrix[i][j] -= Matrix1[i][j];
			}
		}
		return *this;
	}
	matrix& operator*=(const matrix& Matrix1) {
		matrix temp(rows, Matrix1.columns);
		for (int i = 0; i < temp.rows; ++i) {
			for (int j = 0; j < temp.columns; ++j) {
				for (int k = 0; k < columns; ++k) {
					temp[i][j] += (Matrix[i][k] * Matrix1[k][j]);
				}
			}
		}
		return (*this = temp);
	}
	double* operator[](size_t number_of_element) {
		return Matrix[number_of_element];
	}
	double* operator[](size_t number_of_element)const {
		return Matrix[number_of_element];
	}
};
matrix operator+(const matrix& Matrix1, const matrix& Matrix2)
{
	matrix temp(Matrix1);
	return (temp += Matrix2);
}
matrix operator-(const matrix& Martix1, const matrix& Matrix2)
{
	matrix temp(Martix1);
	return (temp -= Matrix2);
}
matrix operator*(const matrix& Matrix1, const matrix& Matrix2)
{
	matrix temp(Matrix1);
	return (temp *= Matrix2);
}