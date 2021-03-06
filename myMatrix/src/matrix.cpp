#include "matrix.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

Matrix::Matrix(std::size_t r, std::size_t c) {
	_data = new int*[r];
	for (std::size_t i = 0; i < r; i++) {
		_data[i] = new int[c];
	}
	for (std::size_t i = 0; i < r; i++) {
		for (std::size_t j = 0; j < c; j++) {
			_data[i][j] = 0;
		}
	}
	_rows = r;
	_cols = c;
}

Matrix::Matrix() {
	_rows = 0;
	_cols = 0;
}

Matrix::~Matrix() {
	if (_cols != 0) {	
		for (std::size_t i = 0; i < _rows; i++) {
			delete [] _data[i];
		}
	}
	if (_rows != 0) {
		delete [] _data;
	}
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
	if (i >= _rows || j >= _cols) {
		std::cout << "matrix index out of range\n";
		exit(1);
	}
	_data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
	if (i >= _rows || j >= _cols) {
		throw MatrixException("ACCESS: bad index");
	}
  	return _data[i][j];
}

void Matrix::print(FILE* f) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			fprintf(f, "%d ", _data[i][j]);
		}
		fprintf(f, "\n");
	}
}

bool Matrix::operator==(Matrix& m) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			if (_data[i][j] != m.get(i,j)) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix& m) const {
	return !(*this == m);
}

Matrix& Matrix::operator+=(Matrix& m) {
	if (_cols != m.get_cols() || _rows != m.get_rows()) {
		throw MatrixException("ADD: dimensions do not match");
	}
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_data[i][j] += m.get(i,j);
		}
	}	
	return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_data[i][j] -= m.get(i,j);
		}
	}	
	return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
	if (_cols != m.get_rows()) {
		throw MatrixException("MUL: columns != rows");
	}
	Matrix prod(_rows, m.get_cols());
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m.get_cols(); j++) {
			for (std::size_t r = 0; r < _cols; r++) {
				prod.set(i,j, prod.get(i, j) + _data[i][r] * m.get(r, j));
			}
		}
	}
	*this = prod;
	return *this;
}

void Matrix::operator=(Matrix& m) {	
	std::size_t r = m.get_rows();
	std::size_t c = m.get_cols();

	for (std::size_t i = 0; i < _rows; i++) {
		delete [] _data[i];
	}
	delete [] _data;
	_data = new int*[r];
	for (std::size_t i = 0; i < r; i++) {
		_data[i] = new int[c];
	}
	for (std::size_t i = 0; i < r; i++) {
		for (std::size_t j = 0; j < c; j++) {
			_data[i][j] = m.get(i, j);
		}
	}
	_rows = r;
	_cols = c;
}

Matrix Matrix::operator+(Matrix& m) const{
	Matrix sum(_rows, _cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			sum.set(i, j, (_data[i][j] + m.get(i,j)));
		}
	}	
	return sum;
}

Matrix Matrix::operator-(Matrix& m) const{
	Matrix sub(_rows, _cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			sub.set(i, j, (_data[i][j] - m.get(i,j)));
		}
	}	
	return sub;
}

Matrix Matrix::operator*(Matrix& m) const{
	Matrix prod(_rows, m.get_cols());
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m.get_cols(); j++) {
			for (std::size_t r = 0; r < _cols; r++) {
				prod.set(i,j, prod.get(i, j) + _data[i][r] * m.get(r, j));
			}
		}
	}
	return prod;
}

std::ostream& operator<<(std::ostream& os, Matrix& m) {
	for (std::size_t i = 0; i < m._rows; i++) {
		os << m._data[i][0];
		for (std::size_t j = 1; j < m._cols; j++) {
			os << " " << m._data[i][j];
		}
		os << "\n";
	}
	return os;
}

std::ifstream& operator>>(std::ifstream& is, Matrix& m) {
	std::size_t r, c;
	is >> r;
	is >> c;

	if (m._cols != 0) {	
		for (std::size_t i = 0; i < m._rows; i++) {
			delete [] m._data[i];
		}
	}
	if (m._rows != 0) {
		delete [] m._data;	
	}

	m._data = new int*[r];
	for (std::size_t i = 0; i < r; i++) {
		m._data[i] = new int[c];
	}
	for (std::size_t i = 0; i < r; i++) {
		for (std::size_t j = 0; j < c; j++) {
			m._data[i][j] = 0;
		}
	}
	m._rows = r;
	m._cols = c;
	for (std::size_t i = 0; i < r; i++) {
		for (std::size_t j = 0; j < c; j++) {
			is >> m._data[i][j];
		}
	}
	return is;

}
