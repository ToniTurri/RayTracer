#ifndef _MATRIX_H
#define _MATRIX_H

using std::vector;

template <typename T> class Matrix {
public:
	unsigned rows, cols;

	Matrix() {};
	~Matrix() {};
	Matrix(unsigned _rows, unsigned _cols);

	vector<vector<T>> matrix;
	Matrix<T>& operator=(Matrix<T> rhs);

	//Matrix mathematical operations                                                                                                                                                                                               
	Matrix<T> operator+(const Matrix<T>& rhs);
	Matrix<T>& operator+=(const Matrix<T>& rhs);
	Matrix<T> operator-(const Matrix<T>& rhs);
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	Matrix<T> operator*(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const Matrix<T>& rhs);
	Matrix<T> transpose();

	// Matrix scalar operations
	Matrix<T> operator+(const T& rhs);
	Matrix<T> operator-(const T& rhs);
	Matrix<T> operator*(const T& rhs);
	Matrix<T> operator/(const T& rhs);

	// Matrix/vector operations
	vector<T> operator*(const vector<T>& rhs);
	vector<T> diag_vec();
	
	// Access the individual elements                                                                                                                                                                                               
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	void swap(Matrix<T>& rhs);
	void print_matrix();
};
                                                                                                                                                   
template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols) {
	matrix.resize(_rows);

	for (unsigned i = 0; i < _rows; i++)
		matrix[i].resize(_cols, 0.0);

	rows = _rows;
	cols = _cols;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> rhs) {
	swap(rhs);
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
	Matrix<T> result(*this);
	result += rhs;
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			this->matrix[i][j] += rhs(i, j);

	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
	Matrix<T> result(*this);
	result -= rhs;
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			this->matrix[i][j] -= rhs(i, j);

	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
	Matrix<T> result(*this);
	result *= rhs;
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
	unsigned _rows = rows;
	unsigned _cols = rhs.get_cols();

	Matrix<T> result(_rows, _cols);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < _cols; j++)
			for (unsigned k = 0; k < cols; k++)
				result(i, j) += this->matrix[i][k] * rhs(k, j);

	*this = result;
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> result(cols, rows);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			result(j, i) = this->matrix[i][j];

	*this = result;
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T& rhs) {
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			this->matrix[i][j] += rhs;

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T& rhs) {
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			this->matrix[i][j] -= rhs;

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs) {
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			this->matrix[i][j] *= rhs;

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& rhs) {
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			this->matrix[i][j] /= rhs;

	return *this;
}

template <typename T>
vector<T> Matrix<T>::operator*(const vector<T>& rhs) {
	std::vector<T> result(rows);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			result[i] += this->matrix[i][j] * rhs[j];

	return result;
}

template<typename T>
vector<T> Matrix<T>::diag_vec() {
	vector<T> result(rows);

	for (unsigned i = 0; i < rows; i++)
		result[i] = this->matrix[i][i];

	return result;
}
                                                                                                                                             
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
	return this->matrix[row][col];
}
                                                                                                                                    
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
	return this->matrix[row][col];
}

template<typename T>
void Matrix<T>::swap(Matrix<T>& rhs) {
	using std::swap;

	swap(this->rows, rhs.rows);
	swap(this->cols, rhs.cols);
	swap(this->matrix, rhs.matrix);
}

template<typename T>
void Matrix<T>::print_matrix() {
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << " " << std::endl;
	}
	std::cout << std::endl;
}

#endif