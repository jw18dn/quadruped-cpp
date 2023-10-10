#include "gait.h"
#include "optimization.h"

int main(){
    Gait temp;
    temp.SetGaitTime(1);
    temp.Print();

    // Optimization temp;
    // VectorXf q_n_body = VectorXf::Random(3);
    // MatrixXf u_n_body = VectorXf::Random(3,2);

    // temp.SetLinearDynamics(q_n_body, u_n_body);
}


