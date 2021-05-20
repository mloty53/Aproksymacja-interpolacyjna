#pragma once
#include "Matrix.h"
class Equation {
private:
	matrix A;
	matrix x;
	matrix b;
	int N;
public:

	matrix& LU() {
		matrix L(N, N);
		matrix U(N, N);
		for (int i = 0; i < N; i++) L[i][i] = 1.0;
		for (int j = 0; j < N; j++) {
			for (int i = 0; i <= j; i++) {
				U[i][j] += A[i][j];
				for (int k = 0; k <= i - 1; k++)
					U[i][j] -= L[i][k] * U[k][j];
			}
			for (int i = j + 1; i < N; i++) {
				for (int k = 0; k <= j - 1; k++) L[i][j] -= L[i][k] * U[k][j];
				L[i][j] += A[i][j];
				L[i][j] /= U[j][j];
			}
		}
		matrix y(N, 1);
		for (int i = 0; i < N; i++) {
			double val = b[i][0];
			for (int j = 0; j < i; j++) {
				if (j != i) val -= L[i][j] * y[j][0];
			}
			y[i][0] = val / L[i][i];
		}
		for (int i = N - 1; i >= 0; i--) {
			double val = y[i][0];
			for (int j = i; j < N; j++) {
				if (j != i) val -= U[i][j] * x[j][0];
			}
			x[i][0] = val / U[i][i];
		}
		return x;
	}
	void Pivot() {
		for (int i = 2; i < N - 2; i += 4) {
			A.swapRows(i + 1, i + 3);
			b.swapRows(i + 1, i + 3);
			A.swapRows(i + 2, i + 3);
			b.swapRows(i + 2, i + 3);
		}
	}
	void createMatrix(double array_of_x[], double array_of_y[], int n) {
		A = matrix(N, N);
		for (int i = 0; i < N; i++) {
			this->x[i][0] = 1.0;
			this->b[i][0] = 0.0;
		}
		A[0][0] = 1.0;
		b[0][0] = array_of_y[0];
		A[1][2] = 2.0;
		b[1][0] = 0;
		double h = (array_of_x[1] - array_of_x[0]);
		A[1][1] += 1.0;
		A[1][2] += 2 * h;
		A[1][3] += 3 * h * h;
		A[1][5] += -1.0;
		b[1][0] += 0.0;
		for (int i = 1; i < n - 1; i++) {
			double h = (array_of_x[i] - array_of_x[i - 1]);
			A[2 + 4 * (i - 1) + 0][4 * (i - 1)] = 1.0;
			A[2 + 4 * (i - 1) + 0][4 * (i - 1) + 1] = h;
			A[2 + 4 * (i - 1) + 0][4 * (i - 1) + 2] = h * h;
			A[2 + 4 * (i - 1) + 0][4 * (i - 1) + 3] = h * h * h;
			b[2 + 4 * (i - 1) + 0][0] = array_of_y[i];

			A[2 + 4 * (i - 1) + 1][4 * i] = 1.0;
			b[2 + 4 * (i - 1) + 1][0] = array_of_y[i];

			A[2 + 4 * (i - 1) + 2][4 * (i - 1) + 1] = 1.0;
			A[2 + 4 * (i - 1) + 2][4 * (i - 1) + 2] = 2 * h;
			A[2 + 4 * (i - 1) + 2][4 * (i - 1) + 3] = 3 * h * h;
			A[2 + 4 * (i - 1) + 2][4 * i + 1] = -1.0;
			b[2 + 4 * (i - 1) + 2][0] = 0.0;

			A[2 + 4 * (i - 1) + 3][4 * (i - 1) + 2] = 2.0;
			A[2 + 4 * (i - 1) + 3][4 * (i - 1) + 3] = 6.0 * h;
			A[2 + 4 * (i - 1) + 3][4 * i + 2] = -2.0;
			b[2 + 4 * (i - 1) + 3][0] = 0.0;
		}
		for (int i = n - 1; i < n; i++) {
			double h = (array_of_x[i] - array_of_x[i - 1]);
			A[2 + 4 * (i - 1) + 0][4 * (i - 1)] = 1.0;
			A[2 + 4 * (i - 1) + 0][4 * (i - 1) + 1] = h;
			A[2 + 4 * (i - 1) + 0][4 * (i - 1) + 2] = h * h;
			A[2 + 4 * (i - 1) + 0][4 * (i - 1) + 3] = h * h * h;
			b[2 + 4 * (i - 1) + 0][0] = array_of_y[i];
			A[2 + 4 * (i - 1) + 1][4 * (i - 1) + 2] = 2.0;
			A[2 + 4 * (i - 1) + 1][4 * (i - 1) + 3] = 6.0 * h;
			A[2 + 4 * (i - 1) + 1][0] = 0;
		}
		Pivot();
	}
	Equation(int Size) {
		N = Size;
		A = matrix(N, N);
		x = matrix(N, 1);
		b = matrix(N, 1);
	}
};