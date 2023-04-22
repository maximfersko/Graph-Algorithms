#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>
#include <fstream>
#include <iostream>

template <class T>
class Matrix {
   public:
    //  Constructor & Destructor

    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    explicit Matrix(std::initializer_list<T> const& items);
    ~Matrix();

    //  Methods

    int getRows() const;
    int getColumn() const;
    void setRows(int rows);
    void setColumn(int columns);
    bool eq_matrix(const Matrix& other);

    //  operators

    T& operator()(int rows, int column);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    bool operator==(const Matrix& other);

    // utilities
    void print();

   private:
    // Attributes
    int rows_{}, cols_{};  // Rows and columns
    T** matrix_{};  // Pointer to the memory where the matrix is allocated

    bool validate() const;
    void createMatrix();
    void freeMatrix();
};
#include "matrix.inl"
#endif  // MATRIX_H_
