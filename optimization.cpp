#include "optimization.h"

Optimization::Optimization(){
    // Initialize the Matrix sizes
    A(num_states,num_states);
    B(num_states,num_inputs);
    f(num_states);

    // Initialize the constraint Matrix
    geq(num_states*nodes,num_states*nodes);
    ceq(num_states*nodes);


    // Initialize and set values for identity matrix
    I*(num_states,num_states);
    for(int i = 0; i < num_states; i++){
        I(i,i) = 1;
    }
};
void Optimization::SetEqualityConstraints(){
    MatrixXf temp;

    temp = -A*optim_dt - I, I, -B*optim_dt;
};

void Optimization::SetInequalityConstraints(){

};

void Optimization::SetObjectiveFunction(){
    
};

void Optimization::SetLinearDynamics(VectorXf prev_states, VectorXf prev_inputs){                              
    
}; 