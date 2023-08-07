#include "optimization.h"

Optimization::Optimization(){
    // Initialize the Matrix sizes (these are not stored for every node, only a single node)
    A(num_states,num_states);  
    B(num_states,num_inputs);
    f(num_states);

    // Initialize the constraint Matrix
    geq(num_states*nodes,num_states*nodes);
    ceq(num_states*nodes);

    // Initialize and set values for identity matrix
    I(num_states,num_states);
    Z(num_states,num_states);
    for(int i = 0; i < num_states; i++){
        I(i,i) = 1;
    }

    // Initialize the previous states and inputs - check using random values
    prev_states = MatrixXf::Random(num_states,nodes);
    prev_states = MatrixXf::Random(num_inputs,nodes);
};
void Optimization::SetEqualityConstraints(){
    // Index replaced positions
    int rows = 2*num_states + 2*num_inputs;
    int cols = num_states;

    // Initialize the start & stop points
    int row_start = 0, row_stop = 0;
    int col_start = 0, col_stop = 0;

    // Set the constraint matrix
    for(int i = 1; i < nodes, i++){
        // Reset the stop points
        row_stop = row_start + rows;
        col_stop = col_start + cols;

        // Find the linear dynamics for a specific node - need to pass by value
        SetLinearDynamics(prev_states.col(i), prev_inputs.col(i));
        geq.block(row_start,col_start,row_stop,col_stop) = -A*optim_dt - I, I, -B*optim_dt;
        // ceq.block(row_start,row_stop) = 2*

        // Reset the start points
        row_start = row_stop + 1;
        col_start = col_stop + 1;
    }

    prev_states = MatrixXf::Random(num_states,nodes);
    prev_states = MatrixXf::Random(num_inputs,nodes);
};

void Optimization::SetInequalityConstraints(){

};

void Optimization::SetObjectiveFunction(){
    // Index replaced positions
    int rows = num_states + num_inputs;
    int cols = rows;
    
    // Initialize the start & stop points
    int row_start = 0, row_stop = 0;
    int col_start = 0, col_stop = 0;

    for(int i = 1; i < nodes, i++){
        // Reset the stop points
        row_stop = row_start + rows;
        col_stop = col_start + cols;

        // Find the linear dynamics for a specific node
        // H.block(row_start,col_start,row_stop,col_stop) = 2*Q, 0 , 0 , 2*R;
        // c.block(row_start,row_stop) = 2*Q*q_des;

        // Reset the start points
        row_start = row_stop + 1;
        col_start = col_stop + 1;
    }    

};

void Optimization::SetLinearDynamics(VectorXf prev_states, VectorXf prev_inputs){                              
    
}; 