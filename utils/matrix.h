/******************************************************************************
* File:             matrix.h
*
* Author:           yychi  
* Created:          2019-10-31 09:35 
* Description:      This file implements a simple matrix interface.
*****************************************************************************/

#ifndef __YMAT_H__
#define __YMAT_H__

#include <iostream>

template <typename T>
class Matrix
{
public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

public:
  Matrix(int nr = 0, int nc = 0);
  Matrix(int nr, int nc, std::initializer_list<T> il);
  Matrix(const Matrix&);
  Matrix& operator=(const Matrix&);
  Matrix(Matrix&&) noexcept;
  Matrix& operator=(Matrix&&) noexcept;
  ~Matrix() { delete [] data_; }

public:
  // selectors
  T* operator[](int) const;
  int row() const { return row_; }
  int col() const { return col_; }
  T* data() const { return data_; }

  // opeators
  Matrix operator+(const Matrix&) const;
  Matrix operator-(const Matrix&) const;
  Matrix operator-() const; // unary minus, -1, -2, etc.
  Matrix operator*(const Matrix&) const;
  Matrix& operator+=(const Matrix&);
  Matrix& operator-=(const Matrix&);

  // operations
  Matrix transpose() const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream&, const Matrix<U>&);

private:
  int row_;
  int col_;
  T* data_;
};

// ================ impl ==================
template <typename T>
Matrix<T>::Matrix(int nr, int nc)
{
  if (nr <= 0 || nc <= 0)
    throw std::invalid_argument("row/col size must > 0");
  row_ = nr;
  col_ = nc;
  data_ = new T [nr * nc];
}

template <typename T>
Matrix<T>::Matrix(int nr, int nc, std::initializer_list<T> il)
  : Matrix(nr, nc)
{
  if (il.size() != nr * nc)
    throw std::invalid_argument("initializer_list doesn't fit the matrix");
  std::copy(il.begin(), il.end(), data_);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
  row_ = other.row_;
  col_ = other.col_;
  data_ = new T [row_ * col_];
  std::copy(other.data_, other.data_ + row_ * col_, data_);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
  if (this == &other) return *this;
  delete [] data_;
  row_ = other.row_;
  col_ = other.col_;
  data_ = new T [row_ * col_];
  std::copy(other.data_, other.data_ + row_ * col_, data_);
  return *this;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
  : row_(other.row_), col_(other.col_), data_(other.data_)
{
  other.data_ = nullptr;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
  if (this != &other)
  {
    delete [] data_;
    row_ = other.row_;
    col_ = other.col_;
    data_ = other.data_;
    other.data_ = nullptr;
  }
  return *this;
}

template <typename T>
T* Matrix<T>::operator[](int row) const
{
  if (row < 0 || row >= row_)
    throw std::range_error("invalid row index");
  return data_ + col_ * row;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const
{
  if (row_ != rhs.row_ || col_ != rhs.col_)
    throw std::invalid_argument("matrix size mismatch");
  Matrix<T> ret(row_, col_);
  for (int i = 0; i < row_*col_; ++i)
    ret.data_[i] = data_[i] + rhs.data_[i];
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) const
{
  if (row_ != rhs.row_ || col_ != rhs.col_)
    throw std::invalid_argument("matrix size mismatch");
  Matrix<T> ret(row_, col_);
  for (int i = 0; i < row_*col_; ++i)
    ret.data_[i] = data_[i] - rhs.data_[i];
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
  Matrix<T> ret(row_, col_);
  for (int i = 0; i < row_*col_; ++i)
    ret.data_[i] = (-data_[i]);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const
{
  if (col_ != rhs.row_)
    throw std::invalid_argument("matrix size mismatch");
  Matrix<T> ret(row_, rhs.col_);
  // perform matrix multiplication
  for (int i = 0; i < row_; ++i)
  {
    for (int k = 0; k < col_; ++k)
    {
      for (int j = 0; j < rhs.col_; ++j)
        ret[i][j] += (*this)[i][k] * rhs[k][j];
    }
  }
  return ret;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
  if (row_ != rhs.row_ || col_ != rhs.col_)
    throw std::invalid_argument("matrix size mismatch");
  for (int i = 0; i < row_*col_; ++i)
    data_[i] += rhs.data_[i];
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs)
{
  if (row_ != rhs.row_ || col_ != rhs.col_)
    throw std::invalid_argument("matrix size mismatch");
  for (int i = 0; i < row_*col_; ++i)
    data_[i] -= rhs.data_[i];
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix<T> ret(col_, row_);
  for (int i = 0; i < row_; ++i)
  {
    for (int j = 0; j < col_; ++j)
      ret[j][i] = (*this)[i][j];
  }
  return ret;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
{
  for (int i = 0; i < mat.row_; ++i)
  {
    for (int j = 0; j < mat.col_; ++j)
      os << mat[i][j] << ' ';
    os << '\n';
  }
  return os;
}

#endif // __YMAT_H__
