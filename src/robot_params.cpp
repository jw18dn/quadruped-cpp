#include <Eigen/Dense>

// This is where all the predefined parameters are set
class RobotParams
{

public:
    // Variables
    Eigen::Matrix<float, 3, 3> I;         // Inertial Tensor - Body Frame
    const float trunk_m = 4.713;
    const float hip_m = 0.696; 
    const float thigh_m = 1.013; 
    const float calf_m = 0.226;

    // Functions
    const Eigen::MatrixXf GetInertia(){return I;}
};

RobotParams::RobotParams(){
    I << 0.0158533, -3.66e-05, -6.11e-05, 
         -2.75e-05, 0.0377999, -2.75e-05, 
         -6.11e-05, -3.66e-05, 0.0456542;  
}

RobotParams::~RobotParams(){

}

