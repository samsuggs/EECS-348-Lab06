#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
int size;
using std::cout;
//1.
int** read_file(std::string name){
    std::ifstream file(name);
    if (!size){
        std::string msize;
        std::string line;
        std::getline(file, msize);
        size = std::stoi(msize);
        int** matrix = new int*[size];
        for(int i=0; i<size; i++){
            getline(file, line);
            std::stringstream ss(line);
            matrix[i] = new int[size];
            for(int j=0; j<size; j++){
                int num;
                ss >> num;
                matrix[i][j] = num;
            }
        }   
        return matrix;  
    }
    else{
        std::string line;
        int** matrix = new int*[size];
        for(int i=0; i<(size*2)+1; i++){
            std::getline(file, line);
            if(i<size+1) 
                continue;
            std::stringstream ss(line);
            matrix[i-size-1] = new int[size];
            for(int j=0; j<size; j++){
                int num;
                ss >> num;
                matrix[i-size-1][j] = num;
            }
        }
        return matrix;
    }   
}
//2.
void print (int** matrix){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (matrix[i][j] > 100 || matrix[i][j] < -100){
                cout << matrix[i][j] << " ";
            }
            else if (matrix[i][j]>10 || matrix[i][j] < -10){
                cout << matrix[i][j] << "  ";
            }
            else{
                cout << matrix[i][j] << "   ";
            }
        }
        cout << "\n";
    }
}
//3.
void add (int** matrix1, int** matrix2){
    int** matrix3 = new int*[size];
    for(int i=0; i<size; i++){
        matrix3[i] = new int[size];
        for(int j=0; j<size; j++){
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    print(matrix3);
}
//4.
void multiply(int** matrix1, int** matrix2){
    int** matrix3 = new int*[size];
    for(int i=0; i<size; i++){
        matrix3[i] = new int[size];
        for(int j=0; j<size; j++){
            matrix3[i][j] = 0;
            for(int k=0; k<size; k++){
                matrix3[i][j] += matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    print(matrix3);
}
//5.
void subtract(int** matrix1, int** matrix2){
    int** matrix3 = new int*[size];
    for(int i=0; i<size; i++){
        matrix3[i] = new int[size];
        for(int j=0; j<size; j++){
            matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    print(matrix3);
}
//6.
int** update(int** matrix, int row, int col, int val){
    if(row>size || col>size){
        cout << "Invalid row/column. It must not exceed " << size << std::endl;
        return matrix;
    }
    else{
        matrix[row-1][col-1] = val;
        print(matrix);
        return matrix;
    }
}
//7.
inline int max(int** matrix){
    int num = matrix[0][0];
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (matrix[i][j] > num){
                num = matrix[i][j];
            }
        }
    }
    return num;
}
//8.
int** transpose(int** matrix){
    int** new_matrix = new int*[size];
    for(int i=0; i<size; i++){
        new_matrix[i] = new int[size];
        for(int j=0; j<size; j++){
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}
int main(){
    int** matrix1 = read_file("matrix_input.txt");
    cout << "Printing the first matrix:" << std::endl;
    print(matrix1);
    int** matrix2 = read_file("matrix_input.txt");
    cout << std::endl << "Printing the second matrix:" << std::endl;
    print(matrix2);
    cout << std::endl << "Matrix 1 + Matrix 2:" << std::endl;
    add(matrix1, matrix2);
    cout << std::endl << "Matrix 1 * Matrix 2:" << std::endl;
    multiply(matrix1, matrix2);
    cout << std::endl << "Matrix 1 - Matrix 2:" << std::endl;
    subtract(matrix1, matrix2);
    cout << std::endl << "Updating an element of Matrix 1:" << std::endl;
    int row, col, val;
    cout << "Enter row number: ";
    std::cin >> row;
    cout << "Enter column number: ";
    std::cin >> col;
    cout << "Enter new value: ";
    std::cin >> val;
    matrix1 = update(matrix1, row, col, val);
    cout << std::endl << "The max of Matrix 1 is: " << max(matrix1) << std::endl;
    matrix1 = transpose(matrix1);
    cout << std::endl << "Matrix 1 Transposed:" << std::endl;
    print(matrix1);
    return 0;
}