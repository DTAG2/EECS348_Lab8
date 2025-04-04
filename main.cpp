#include <iostream> //library for I/O operations
#include <fstream> //file handling library
#include <vector> //dynamic arrays
#include <iomanip> //formatting output
#include <stdexcept> //handling excpetions

using Matrix = std::vector<std::vector<int>>; //type alias for a 2d vector named Matrix

// Function to print matrix with proper formatting
void PrintMatrix(const Matrix &mat) {
    for (const auto &row : mat) { //looping over the matrix rows
        for (const auto &col : row) { //looping over the matrix columns
            std::cout << std::setw(4) << col; //print the matrix value with a specified character width for the output
        }
        std::cout << "\n"; //print new line character after each row
    }
    std::cout << "\n"; //print new line character after printing matrix
}

//1. Read values from a file into the matrix:
bool ReadMatrixValues(const std::string &filename, Matrix &mat1, Matrix &mat2, int &N) { //changes the values of the passed in matrix variables (mat1, mat2)
    std::ifstream infile(filename); //open the file for reading
    if (!infile) { //check if the file opened properly
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }
    
    infile >> N; //get matrix size from file
    if (N <= 0) { //if the matrix is size is less than or equal to zero
        std::cerr << "Invalid matrix size.\n"; //print an error
        return false; //return false
    }
    
    // Resize matrices as NxN
    mat1.resize(N, std::vector<int>(N, 0));
    mat2.resize(N, std::vector<int>(N, 0));
    
    // Read first matrix
    for (int i = 0; i < N; ++i) //looping over the the matrix rows
        for (int j = 0; j < N; ++j) //looping over the matrix columns 
            infile >> mat1[i][j]; //assign the next value in the file to this matrix index
    
    // Read second matrix
    for (int i = 0; i < N; ++i) //looping over the matrix rows
        for (int j = 0; j < N; ++j) //looping over the matrix columns
            infile >> mat2[i][j]; //assign the next value in the file to this matrix index
    
    infile.close(); //close the file

    std::cout << "Matrix 1:\n"; //print the first matrix
    PrintMatrix(mat1);
    
    std::cout << "Matrix 2:\n"; //print the second matrix
    PrintMatrix(mat2);

    return true; //return true
}

//2. Add two matrices and display the result:
void AddMatrices(const Matrix &A, const Matrix &B) {
    int N = A.size(); //get the size of the matrices (NxN)
    Matrix added_matrix(N, std::vector<int>(N, 0)); //create added_matrix variable of type Matrix
    for (int i = 0; i < N; ++i) //looping over both matrix's rows
        for (int j = 0; j < N; ++j) //looping over both matrix's columns
            added_matrix[i][j] = A[i][j] + B[i][j]; //add the values from both matrices

    std::cout << "Added Matrix (Matrix1 + Matrix2):\n"; //print the added matrix
    PrintMatrix(added_matrix);
}

//3. Multiply two matrices and display the result:
void mult_mat(const Matrix &A, const Matrix &B) {
    int N = A.size(); //get the size of the matrices (NxN)
    Matrix m_matrix(N, std::vector<int>(N, 0)); //create m_matrix variable of type Matrix
    for (int i = 0; i < N; ++i) { //looping over matrix A rows
        for (int j = 0; j < N; ++j) { //looping over matrix B columns
            for (int k = 0; k < N; ++k) { //looping over matrix A columns
                m_matrix[i][j] += A[i][k] * B[k][j]; //multiply according rows to add in new matrix value
            }
        }
    }

    std::cout << "Multiplied Matrix (Matrix1 x Matrix2):\n"; //print multiplied matrix
    PrintMatrix(m_matrix);

}

//4. Get the sum of matrix diagonal elements:
void diag_sum(const Matrix &mat) {
    int N = mat.size(); //get the size of the matrix (NxN)
    int sum = 0; //initialize sum integer variable
    for (int i = 0; i < N; ++i) { //loop over the rows in the matrix
        sum += mat[i][i]; // main diagonal
        sum += mat[i][N - i - 1]; // secondary diagonal
    }
    // If N is odd, the center element was added twice
    if (N % 2 == 1) {
        sum -= mat[N/2][N/2];
    }

    std::cout << "Sum of main and secondary diagonal elements: " << sum << "\n\n"; //print the sum of the diagonal elements
}

//5. Swap matrix rows and display the result:
void swap_rows(Matrix &mat, int row1, int row2) {
    int N = mat.size(); //get the size of the matrix (NxN)
    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) { //check if row indices are out of bounds
        std::cerr << "Row indices out of bounds.\n";
        return;
    }
    std::swap(mat[row1], mat[row2]); // use the swap function to swap the rows

    std::cout << "Swapped rows " << row1 << " and " << row2 << ":\n"; //print matrix with swapped rows
    PrintMatrix(mat);
}

//6. Swap matrix columns and display the result:
void swap_cols(Matrix &mat, int col1, int col2) {
    int N = mat.size(); //get the size of the matrix (NxN)
    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) { //check if column indices are out of bounds
        std::cerr << "Column indices out of bounds.\n";
        return;
    }
    for (int i = 0; i < N; ++i) { //looping over all rows
        std::swap(mat[i][col1], mat[i][col2]); //in each row swap the corresponding columns
    }
    std::cout << "Swapped columns " << col1 << " and " << col2 << ":\n"; //print the matrix with the swapped columns
    PrintMatrix(mat);
}

//7. Update matrix rows and display the result:
void upd_mat_elm(Matrix &mat, int row, int col, int newValue) {
    int N = mat.size(); //get the size of the matrix (NxN)
    if (row < 0 || row >= N || col < 0 || col >= N) { //checks if indices are valid
        std::cerr << "Index out of bounds.\n";
        return;
    }
    mat[row][col] = newValue; //changes the value in the specified position with the newValue

    std::cout << "Updated matrix:\n"; //print updated matrix
    PrintMatrix(mat);

}

int main() {

    std::string filename;
    std::cout << "Enter input file name: ";
    std::cin >> filename;
    
    Matrix matrix1, matrix2;

    int N;

    //read matrix values
    if (!ReadMatrixValues(filename, matrix1, matrix2, N)) {
        return 1;
    }
    
    // Matrix addition
    AddMatrices(matrix1, matrix2);
    
    // Matrix multiplication
    mult_mat(matrix1, matrix2);
    
    // Diagonal sum of first matrix
    std::cout <<"For matrix 1\n";
    diag_sum(matrix1);

    // Swap rows
    int row1, row2;
    std::cout <<"For matrix 1\n";
    std::cout << "Enter row index1 to swap (0 to " << N-1 << "): ";
    std::cin >> row1;
    std::cout << "Enter row index2 to swap (0 to " << N-1 << "): ";
    std::cin >> row2;
    swap_rows(matrix1, row1, row2);
    
    // Swap columns
    int col1, col2;
    std::cout <<"For matrix 1\n";
    std::cout << "Enter column index1 to swap (0 to " << N-1 << "): ";
    std::cin >> col1;
    std::cout << "Enter column index2 to swap (0 to " << N-1 << "): ";
    std::cin >> col2;
    swap_cols(matrix1, col1, col2);
    
    // Update a matrix element
    int updateRow, updateCol, newValue;
    std::cout <<"For matrix 1\n";
    std::cout << "Enter row index (0 to " << N-1 << "): ";
    std::cin >> updateRow;
    std::cout << "Enter column index (0 to " << N-1 << "): ";
    std::cin >> updateCol;
    std::cout << "Enter new value: ";
    std::cin >> newValue;
    upd_mat_elm(matrix1, updateRow, updateCol, newValue);

    
    return 0;
}
