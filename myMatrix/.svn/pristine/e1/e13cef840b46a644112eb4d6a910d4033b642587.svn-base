#ifndef LAB_14_MATRIX_H
#define LAB_14_MATRIX_H

#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);
  Matrix();
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j) const;
  void print(FILE *f) const;

  void operator=(Matrix& m);
  Matrix operator+(Matrix& m) const;
  Matrix operator-(Matrix& m) const;
  Matrix operator*(Matrix& m) const;

  Matrix& operator+=(Matrix& m);
  Matrix& operator-=(Matrix& m);
  Matrix& operator*=(Matrix& m);

  bool operator==(Matrix& m) const;
  bool operator!=(Matrix& m) const;

  friend std::ostream& operator<<(std::ostream& os, Matrix& m);
  friend std::ifstream& operator>>(std::ifstream& is, Matrix& m);
private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

class MatrixException {
public:
  MatrixException(const char* m) {
    strcpy(message, m);
  };
  const char* get() {
    return message;
  }
private:
  char message[256];
};
#endif
