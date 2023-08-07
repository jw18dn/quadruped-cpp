#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;

class Optimization
{
private:
    // Linear Dynamics
    MatrixXf A, B;
    VectorXf f;   

    // Constraint Structures geq*q = ceq, qiq <= ciq 
    MatrixXf geq, giq;
    VectorXf ciq, ceq;

    // Objective Function parameters
    MatrixXf H;
    VectorXf c;

    // Constant Variables
    int num_states, num_inputs, nodes;
    float optim_dt;
    MatrixXi prev_states, prev_inputs;       // Most recent optimization results
    MatrixXi I, Z;                          // Identity Matrix and Zero matrix

public:
    // Constructor
    Optimization();
    void SetLinearDynamics(VectorXf,VectorXf);
    void SetEqualityConstraints();
    void SetInequalityConstraints();
    void SetObjectiveFunction();
};

