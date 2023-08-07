#include "optimization.h"

Optimization::Optimization(){
    // Initialize the Matrix sizes (these are not stored for every node, only a single node)
    A.resize(num_body_states,num_body_states);  
    B.resize(num_body_states,num_body_inputs);
    f.resize(num_body_states);

    // Initialize and set values for identity and zero matrix
    I.resize(num_body_states,num_body_states);
    Z.resize(num_body_states,num_body_states);
    for(int i = 0; i < num_body_states; i++){
        I(i,i) = 1;
    }
    // Initialize the Constraint Matrix
    int eq_rows = num_body_states*nodes;
    int eq_cols = num_body_states*nodes;
    geq.resize(eq_rows,eq_cols);
    ceq.resize(eq_rows);

    // Initialize the Objective Function Matricies
    int of_rows = nodes*(num_body_states + num_body_inputs);
    int of_cols = nodes*(num_body_states + num_body_inputs);
    H.resize(of_rows,of_cols);
    c.resize(of_rows);

    // Initialize the objective function weight matrix
    QR.resize(num_body_states + num_body_inputs, num_body_states + num_body_inputs);
    for(int i = 0; i < num_body_states; i++){
        QR(i) = i;
    }
    for(int i = num_body_states; i < num_body_inputs + num_body_states; i++){
        QR(i) = i;
    }

    // Initialize the previous states and inputs - check using random values
    q_body = MatrixXf::Random(num_body_states,nodes);
    u_body = MatrixXf::Random(num_body_inputs,nodes);
    q_des = VectorXf::Random(num_body_states);
};

void Optimization::SetLinearDynamics(VectorXf q_n_body, MatrixXf u_n_body){      
    // Setup for planar quadruped (or technically a biped) 
    // func inputs are vectors of states for a specific node
    // Physical Properties
    int M = 10;          // Mass
    int Iyy = 2;          // Inertia

    // Reference Position
    int num_body_pos = num_body_states/2;
    int start_pos = num_body_pos + 1;

    // Euler Integration dx = Ax + Bu + C
    // A Matrix----------------------------------------------------------------------------------
    for(int i = start_pos; i < num_body_states; i++){
        A(i,i) = 1;
    }

    // B Matrix ---------------------------------------------------------------------------------
    // Vector from body to toe - single node 
    MatrixXf q_n_leg = MatrixXf::Random(3,2);
    MatrixXf r(3,2); 

    for(int i = 0; i < num_legs; i++){
        r.col(i) = q_n_leg.block(0,i,3,1) - q_n_body;
    }

    // Replace a block of the B matrix using toe positions
    int col_start = 0;
    int mat_block_size = num_body_inputs/num_legs;
    for(int i=0; i< num_legs; i++){
        B.block(3, col_start, 2, mat_block_size) << 1/M, 0, 0, 1/M;
        B.block(5, col_start, 1, mat_block_size) << r(2,i)/Iyy, -r(0,i)/Iyy;
    }

    std::cout << B << std::endl;

    // f Vector - WRONG
    f(4) = -9.81;
    for(int i=0; i<num_legs; i++){
        f(3) += u_n_body(0,i)/M;                    // X forces
        f(4) += u_n_body(2,i)/M;                    // Z forces
        f(5) += u_n_body(0,i) + u_n_body(2,i);      // <-- This needs to be fixed for sure
    }
}; 

/*
void Optimization::SetEqualityConstraints(){
    // Index replaced positions
    int rows = 2*num_body_states + 2*num_body_inputs;
    int cols = num_body_states;

    // Initialize the start & stop points
    int row_start = 0, col_start = 0;

    // Set the constraint matrix
    for(int i = 1; i < nodes; i++){
        // Reset the stop points

        // Find the linear dynamics for a specific node - need to pass by value
        SetLinearDynamics(q_body.col(i), u_body.col(i));
        geq.block(row_start,col_start,rows,cols) << -A*optim_dt - I, I, -B*optim_dt;
        // ceq.block(row_start,row_stop) = 2*

        // Reset the start points
        row_start = row_start + rows + 1;
        col_start = col_start + cols + 1;
    }

    // Mock state values by reseting them
    q_body = MatrixXf::Random(num_body_states,nodes);
    u_body = MatrixXf::Random(num_body_inputs,nodes);
};

void Optimization::SetInequalityConstraints(){

};

void Optimization::SetObjectiveFunction(){
    // Index replaced positions
    int rows = num_body_states + num_body_inputs;
    int cols = num_body_states + num_body_inputs;
    
    // Initialize the start & stop points
    int row_start = 0, col_start = 0;

    for(int i = 1; i < nodes; i++){
        // Find the linear dynamics for a specific node
        H.block(row_start,col_start,rows,cols) = 2*QR;
        // c.segment(row_start,rows) = -2*QR*q_des;

        // Reset the start points
        row_start = row_start + rows + 1;
        col_start = col_start + cols + 1;
    }    
};

*/