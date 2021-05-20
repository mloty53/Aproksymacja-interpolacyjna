#include "Matrix.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int number_of_nodes;
int Interval=31; 
const char* dataFile = "Data\\genoa_rapallo.txt";
double* array_of_x;
double* array_of_y;
double* coefficients;
matrix A;
matrix b; 
matrix x;

void matrixes(int size) {
	A = matrix(size, size);
	b = matrix(size, 1);
	x = matrix(size, 1);
}
matrix LU(int size) {
	matrix L(size, size);
	matrix U(size, size);
	for (int i = 0; i < size; i++) L[i][i] = 1.0;
	for (int j = 0; j < size; j++) {
		for (int i = 0; i <= j; i++) {
			U[i][j] += A[i][j];
			for (int k = 0; k <= i - 1; k++)
				U[i][j] -= L[i][k] * U[k][j];
		}
		for (int i = j + 1; i < size; i++) {
			for (int k = 0; k <= j - 1; k++) L[i][j] -= L[i][k] * U[k][j];
			L[i][j] += A[i][j];
			L[i][j] /= U[j][j];
		}
	}
	matrix y(size, 1);
	for (int i = 0; i < size; i++) {
		double val = b[i][0];
		for (int j = 0; j < i; j++) {
			if (j != i) val -= L[i][j] * y[j][0];
		}
		y[i][0] = val / L[i][i];
	}
	for (int i = size - 1; i >= 0; i--) {
		double val = y[i][0];
		for (int j = i; j < size; j++) {
			if (j != i) val -= U[i][j] * x[j][0];
		}
		x[i][0] = val / U[i][i];
	}
	return x;
}
void Pivot(int size) {
	for (int i = 2; i < size - 2; i += 4) {
		A.swapRows(i + 1, i + 3);
		b.swapRows(i + 1, i + 3);
		A.swapRows(i + 2, i + 3);
		b.swapRows(i + 2, i + 3);
	}
}
void createMatrix(double array_of_x[], double array_of_y[], int n,int size) {
	A = matrix(size, size);
	for (int i = 0; i < size; i++) {
		x[i][0] = 1.0;
		b[i][0] = 0.0;
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
	Pivot(size);
}
void create_data(int interval) {
	ofstream x_nodes("x_nodes.txt");
	ofstream y_nodes("y_nodes.txt");
	ifstream data(dataFile);
	vector<double> vaules_of_x;
	vector<double> values_of_y;
	int number_of_node = 0;
	while (!data.eof()) {
		double x, y;
		data >> x >> y;
		if (number_of_node++ % interval) continue;
		x_nodes << x << endl;
		y_nodes << y << endl;
		vaules_of_x.push_back(x);
		values_of_y.push_back(y);
	}
	number_of_nodes = vaules_of_x.size();
	array_of_x = new double[number_of_nodes];
	array_of_y = new double[number_of_nodes];
	for (int i = 0; i < number_of_nodes; i++) {
		array_of_x[i] = vaules_of_x[i];
		array_of_y[i] = values_of_y[i];
	}
}
void calculate_coefficients() {
	int size_of_matrix = 4 * (number_of_nodes - 1);
	coefficients = new double[size_of_matrix];
	matrixes(size_of_matrix);
	createMatrix(array_of_x, array_of_y, number_of_nodes, size_of_matrix);
	matrix Matrix = LU(size_of_matrix);
	for (int k = 0; k < size_of_matrix; k++) coefficients[k] = Matrix[k][0];
}
double SplineInterpolation(double x_value) {
	double result = 0.0;
	for (int i = 0; i < number_of_nodes - 1; i++)
		if (x_value >= array_of_x[i] && x_value <= array_of_x[i + 1]) {
			result = 0.0;
			for (int k = 0; k < 4; k++) result += coefficients[4 * i + k] * pow(x_value - array_of_x[i], k);
			return result;
		}
}
double LaGrangeInterpolation(double x_value) {
	double* LGI = new double[number_of_nodes];
	double result = 0.0;
	for (int i = 0; i < number_of_nodes; i++) {
		LGI[i] = 1.0;
		for (int j = 0; j < number_of_nodes; j++) {
			if (i != j) LGI[i] *= (x_value - array_of_x[j]) / (array_of_x[i] - array_of_x[j]);
		}
	}
	for (int i = 0; i < number_of_nodes; i++) result += array_of_y[i] * LGI[i];
	delete[] LGI;
	return result;
}
void create_chart() {
	ofstream x("x.txt");
	ofstream y("y.txt");
	create_data(1);
	for (int i = 0; i < number_of_nodes; i++) {
		x << array_of_x[i] << endl;
		y << array_of_y[i] << endl;
	}
}
int main() {
	create_chart();
	create_data(Interval);
	calculate_coefficients();
	ofstream xSpline("x_spline.txt");
	ofstream ySpline("y_spline.txt");
	ofstream xLG("x_lg.txt");
	ofstream yLG("y_lg.txt");
	for (double x = array_of_x[0]; x <= array_of_x[number_of_nodes - 1]; x += 0.1) {
		xLG << x << endl;
		xSpline << x << endl;
		yLG << LaGrangeInterpolation(x) << endl;
		ySpline << SplineInterpolation(x) << endl;
	}
}
