#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;

class Optimization
{
private:
    // Linear Dynamics
    MatrixXf A, B;
    VectorXf f;   

    // Constraint Matricies geq*q = ceq, qiq <= ciq 
    MatrixXf geq, giq;
    VectorXf ciq, ceq;

    // Objective Function Matricies
    MatrixXf H;
    VectorXf c;

    // Objective Function Weights
    MatrixXf QR;

    // Desired States
    VectorXf q_des;

    // Optimization results
    MatrixXf q_body, u_body;        

    // Constant Variables
    int nodes = 5;        
    int num_legs = 2;
    int num_body_states = 6;                                // number of pos & vel states
    int num_body_inputs = 4;
    float optim_dt = 0.1;                                     // time step
    MatrixXi I, Z;                                      // Identity Matrix and Zero matrix


public:
    // Constructor
    Optimization();

    // Functions
    void SetLinearDynamics(VectorXf, MatrixXf);
    // void SetEqualityConstraints();
    // void SetInequalityConstraints();
    // void SetObjectiveFunction();
};

 