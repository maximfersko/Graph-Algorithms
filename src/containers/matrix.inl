#include "matrix.h"

template <class T>
Matrix<T>::Matrix() : rows_(2), cols_(2) {
    createMatrix();
}

template <class T>
Matrix<T>::Matrix(int rows, int columns) : rows_(rows), cols_(columns) {
    if (rows <= 0 || columns <= 0) {
        throw std::out_of_range("Invalid values");
    }
    createMatrix();
}

template <class T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
    if (this != &other) {
        createMatrix();
        *this = other;
    }
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<T> const& items) {
    rows_ = cols_ = sqrt(items.size());
    createMatrix();
    auto iterator = items.begin();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = *iterator;
            iterator++;
        }
    }
}

template <class T>
Matrix<T>::Matrix(Matrix&& other) : rows_(0), cols_(0), matrix_(nullptr) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
}

template <class T>
Matrix<T>::~Matrix() {
    freeMatrix();
}

template <class T>
int Matrix<T>::getRows() const {
    return rows_;
}

template <class T>
int Matrix<T>::getColumn() const {
    return cols_;
}

template <class T>
void Matrix<T>::setRows(int rows) {
    if (rows <= 0) {
        throw std::out_of_range("Invalid values");
    } else {
        Matrix tmp(rows, cols_);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols_; j++) {
                if (i >= rows_) {
                    tmp.matrix_[i][j] = 0.0;
                } else {
                    tmp.matrix_[i][j] = matrix_[i][j];
                }
            }
        }
        *this = tmp;
    }
}

template <class T>
void Matrix<T>::setColumn(int columns) {
    if (columns <= 0) {
        throw std::out_of_range("Invalid values");
    } else {
        Matrix tmp(rows_, columns);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < columns; j++) {
                if (j >= cols_) {
                    tmp.matrix_[i][j] = 0.0;
                } else {
                    tmp.matrix_[i][j] = matrix_[i][j];
                }
            }
        }
        *this = tmp;
    }
}

template <class T>
void Matrix<T>::createMatrix() {
    matrix_ = new T*[rows_];
    for (int i = 0; i < rows_; i++) matrix_[i] = new T[cols_]{};
}

template <class T>
void Matrix<T>::freeMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; i++)
            if (matrix_[i]) delete[] matrix_[i];
        delete[] matrix_;
        matrix_ = nullptr;
        rows_ = 0;
        cols_ = 0;
    }
}

template <class T>
bool Matrix<T>::eq_matrix(const Matrix& other) {
    bool result = true;
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->validate() ||
        !other.validate())
        return false;
    double equal;
    for (int i = 0; i < rows_ || !result; i++) {
        for (int j = 0; j < cols_ || !result; j++) {
            equal = std::fabs(matrix_[i][j] - other.matrix_[i][j]);
            if (equal > 1E-7) result = false;
        }
    }
    return result;
}

template <class T>
T& Matrix<T>::operator()(int rows, int column) {
    if (cols_ <= column || rows_ <= rows || rows < 0 || column < 0)
        throw std::out_of_range("Incorrect values");
    return matrix_[rows][column];
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) {
    return eq_matrix(other);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        freeMatrix();
        rows_ = other.rows_;
        cols_ = other.cols_;
        createMatrix();
    }
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    if (this != &other) {
        freeMatrix();
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = other.matrix_;
        other.matrix_ = nullptr;
        other.cols_ = other.rows_ = 0;
    }
    return *this;
}

template <class T>
bool Matrix<T>::validate() const {
    bool result = false;
    if (this->matrix_ != nullptr || this->rows_ > 0 || this->cols_ > 0)
        result = true;
    return result;
}

template <class T>
void Matrix<T>::print() {
    std::cout << std::endl;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
