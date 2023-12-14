#include <cmath>
#include "robot_params.cpp"

// IN: simulated states, footstep plan
// OUT: A, B, f for individual nodes


class LinearDynamics
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
    static Eigen::Matrix<float, 12, 12> A;        // A Matrix
    static Eigen::MatrixXf B;                     // B Matrix

    // Temporary Variables for Testing
    int numb_contacts = 2;
    int phi = 1;

public:
    LinearDynamics(/* args */);
    ~LinearDynamics();
    void StateSpace();
};

LinearDynamics::LinearDynamics(/* args */)
{
    R = Eigen::MatrixXf::Zero(3,3);
    I = robot_properties.GetInertia();
    Eye = Eigen::MatrixXf::Identity(3,3);
    G = Eigen::VectorXf::Zero(12);

    A = Eigen::MatrixXf::Zero(12,12);
    B = Eigen::MatrixXf::Zero(12,numb_contacts*3);
}

LinearDynamics::~LinearDynamics()
{
}

void LinearDynamics::StateSpace(){
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

void LinearDynamics::StepLengthVector(){
    r = v_des*ts + (v_des - v_act)*ts;

}