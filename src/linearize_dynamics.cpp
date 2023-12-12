#include <cmath>
#include "robot_params.cpp"

class StateSpace
{
private:
    // Robot Parameters
    RobotParams robot_properties;

    // Matrix Components
    // std::unique_ptr<Eigen::Matrix<float, 3, 3>> X;         // Rotation Matrix - Extimated w/ small roll & pitch angles
    Eigen::Matrix<float, 3, 3> R;         // Rotation Matrix - Extimated w/ small roll & pitch angles
    Eigen::Matrix<float, 3, 3> I;         // Inertial Tensor - World Frame
    Eigen::Matrix<float, 3, 3> Eye;       // Identity Matrix
    Eigen::Vector<float, 12> G;           // Gravity Vector

    // State Space Matricies
    Eigen::Matrix<float, 12, 12> A;        // A Matrix
    Eigen::MatrixXf B;                     // B Matrix

    // Temporary Variables for Testing
    int numb_contacts = 2;
    int phi = 1;

public:
    StateSpace(/* args */);
    ~StateSpace();
    void Linearize();
};

StateSpace::StateSpace(/* args */)
{
    R = Eigen::MatrixXf::Zero(3,3);
    I = robot_properties.GetInertia();
    Eye = Eigen::MatrixXf::Identity(3,3);
    G = Eigen::VectorXf::Zero(12);

    A = Eigen::MatrixXf::Zero(12,12);
    B = Eigen::MatrixXf::Zero(12,numb_contacts*3);
}

StateSpace::~StateSpace()
{
}

void StateSpace::Linearize(){
    // Formulate the rotation matrix
    R << cos(phi), sin(phi),  0.0,
        -sin(phi), cos(phi),  0.0,
            0.0,      0.0,    1.0;

    // Find the body frame Inertia
    Eigen::Matrix<float, 3, 3> I_inv = I.inverse();
    Eigen::Matrix<float, 3, 3> I_body = R*I_inv*R.transpose();

    // Formulate the A Matrix
    A.block<3,3>(7,1) = R;
    A.block<3,3>(10,4) = Eye;

    // Formulate the B Matrix
    // r = list of vectors from contact location to COM



}