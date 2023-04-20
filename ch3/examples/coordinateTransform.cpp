#include<iostream>
#include<vector>
#include<algorithm>
#include<Eigen/Core>
#include<Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    // define quaternion for the rotation: q1 is the rotation from world to camera 1, 
    // and q2 is the rotation from world to camera 2
    Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);
    // dont forget to normalize the quaternion
    q1.normalize();
    q2.normalize();
    cout << "q1 = " << q1.coeffs().transpose() << endl;
    cout << "q2 = " << q2.coeffs().transpose() << endl;
    // define translation vector from world to camera 1 and 2
    Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
    // define position 1
    Vector3d p1(0.5, 0, 0.2);

    // calculate eulean transformation matrix from world to camera 1 and 2
    Isometry3d T1w(q1), T2w(q2);
    cout << "\n" << endl;
    cout << "T1w = " << T1w.matrix() << endl;
    cout << "T2w = " << T2w.matrix() << endl;
    T1w.pretranslate(t1);
    T2w.pretranslate(t2);
    cout << "T1w = " << T1w.matrix() << endl;
    cout << "T2w = " << T2w.matrix() << endl;

    // calculate position 2 in coordinate of camera 1
    // p2 = T2w * Tw1 * p1
    Isometry3d T2wT1w_inverse = T2w*T1w.inverse();
    // This part is a transformation matrix of shape (4, 4) times a vector in 3-d space of shape (3, 1)
    // How is this done in eigen? 
    // This is how to reconstruct the vector from transformation matrix
    // T = [R, t; 0, 1] -> v2 = T*v1 = R*v1 + t
    Vector3d p2 = T2wT1w_inverse * p1;
    cout << "\n" << endl;
    cout << "T2w*Tw1_inverse = " << T2wT1w_inverse.matrix() << endl;
    cout << "p2 = " << p2.transpose() << endl;

    return 0;
}