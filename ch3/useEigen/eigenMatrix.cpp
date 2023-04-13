// include iostream for cout
#include <iostream>
using namespace std;

// include ctime for time()
#include <ctime>

// include Eigen/Core for core Eigen functions
#include <Eigen/Core>
// include Eigen/Dense for matrix operations
#include <Eigen/Dense>
using namespace Eigen;

// define a 3x3 matrix
#define MATRIX_SIZE 50

/********************
/This program shows how to use Eigen library to do matrix operations
********************/

int main(int argc, char **argv) {
    // All Eigen vectors and marices can be instantiated using Eigen::Matrix, which requirs three arguments: data type, rows, and columns
    // Declare a 2*3 float matrix
    Matrix<float, 2, 3> matrix_23;

    // Eigen also provide many built-in type like Vector3d, Matrix3d, but they are all Eigen::Matrix type at the bottom
    // For example, Vector3d is a special matrix with 3 rows and 1 column
    Vector3d v_3d;
    // Which is the same as 
    Matrix<float, 3, 1> vd_3d;

    // Matrix3d is a special matrix with 3 rows and 3 columns
    // and it is the same as Eigen::Matrix<double, 3, 3>
    Matrix3d matrix_33 = Matrix3d::Zero(); // initialize to zero

    // If you are not sure about the matrix size at compile time, you can use dynamic size
    Matrix< double, Dynamic, Dynamic > matrix_dynamic;

    // Even simpler
    MatrixXd matrix_x;


    // You can also use the typedef keyword
    typedef Matrix< double, 2, 3 > Matrix23d;
    Matrix23d matrix_23d;

    // Now lets do some matrix operations in Eigen
    // Initialize a 2x3 matrix by giving a list of values
    matrix_23 << 1, 2, 3, 4, 5, 6;
    // Print the matrix
    cout << matrix_23 << endl;

    // You can use () to access individual elements
    cout << "print matrix_23:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix_23(i, j) << "\t";
        }
        cout << endl;
    }

    // Multiplication between matrix and vector
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;

    // This code is wrong becasue types of matrix_23 (float) and v_3d (double) are different
    //Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    // Need to convert the type of v_3d to the same type of matrix_23
    Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << "[1,2,3;4,5,6]*[3,2,1]=" << result.transpose() << endl;

    Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
    cout << "[1,2,3;4,5,6]*[3,2,1]=" << result2.transpose() << endl;

    // Some operations
    matrix_33 = Matrix3d::Random(); // random value
    cout << "random matrix: " << endl << matrix_33 << "\n" << endl;
    cout << "transpose: " << endl << matrix_33.transpose() << "\n" << endl;
    cout << "sum: " << endl << matrix_33.sum() << "\n" << endl;
    cout << "trace: " << endl << matrix_33.trace() << "\n" << endl;
    cout << "times 10: " << endl << 10 * matrix_33 << "\n" << endl;
    cout << "inverse: " << endl << matrix_33.inverse() << "\n" << endl;
    cout << "det: " << endl << matrix_33.determinant() << "\n" << endl;

    // eigenvalues
    // real symmetric matrix can be diagonalized by the eigenvalue decomposition
    // SelfAdjointEigenSolver can only solve real symmetric matrix
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen values: " << endl << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors: " << endl << eigen_solver.eigenvectors() << endl;

    // solve linear equation
    // solve equation matrix_NN * x = v_Nd
    // N is at the head, and the values are randomly generated
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN * matrix_NN.transpose(); // make sure matrix_NN is symmetric and positive definite

    Matrix<double, MATRIX_SIZE, 1> v_Nd;
    v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock(); // record start time
    // direct solve using inverse, which is computationally expensive
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;

    cout << "time of normal inverse is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    // solve using QR decomposition
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of QR decomposition is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    // solve using Cholesky decomposition if the matrix is positive definite
    time_stt = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of Cholesky decomposition is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    return 0;

}


