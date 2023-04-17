#include<iostream>
#include<cmath>
using namespace std;

#include<Eigen/Core>
#include<Eigen/Geometry>
using namespace Eigen;

int main(int argc, char **argv0) {
    // Eigen/Geometry provides many types of transformation matrices
    // 3D matrices are used to represent 3D rotations and translations
    Matrix3d rotation_matrix = Matrix3d::Identity();
    // Rotation vector uses AngleAxis. It is not a Matrix, but can be treated as matrix when doing computation
    AngleAxisd rotation_vector(M_PI/4, Vector3d(0, 0, 1)); // Rotate 45 degrees around z-axis
    cout.precision(3);
    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;

    // Use AngleAxis to do rotation matrix conversion
    rotation_matrix = rotation_vector.toRotationMatrix();

    // Use AngleAixs to do coordinate transformation
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;

    // Or use rotation matrix
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;

    // Euler angles
    // Transform rotation matrix to Euler angles
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX order, yaw pitch roll
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

    // Use Eigen::Isometry to represent Euler Transformations
    Isometry3d T = Isometry3d::Identity(); // although its name 2d, but a 4-by-4 matrix
    T.rotate(rotation_vector); // Rotate based rotation_vector
    T.pretranslate(Vector3d(1, 3, 4)); // Translate 1, 3, 4
    cout << "Transform matrix = \n" << T.matrix() << endl;

    // Use Eigen::Isometry to do coordinate transformation
    Vector3d v_transformed = T * v; //similar to R*v+t
    cout << "v transformed = " << v_transformed.transpose() << endl;

    // Use Eigen::Affline3d and Eigen::Projective3d for affine and projective transformations

    // Quaternion
    // Use AngleAxis to initialize Quaternion, and vice versa
    Quaterniond q = Quaterniond(rotation_vector);
    cout << "quaternion from rotation vector = " << q.coeffs().transpose() << endl; // coefficients of quaternion (x, y, z, w), w is the real part.

    // Or use rotation matrix to initialize Quaternion
    q = Quaterniond(rotation_matrix);
    cout << "quaternion from rotation matrix = " << q.coeffs().transpose() << endl;

    // Use Quaternion to do coordinate transformation
    v_rotated = q * v; // mathematically, it is q*v*q^{-1}
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;
    // Or use vector product
    Vector3d v1_rotated = (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().head(3);
    cout << "(0, 1, 0) after rotation = " << v1_rotated.transpose() << endl;

    return 0;

}