#include <iostream>
#include <string>
#include <memory>
#include <Eigen/Dense>
#include "gait_params.cpp"

// IN: 
// OUT: 

class GaitSequence
{
private:
    // Variables
    int rows;                   // stack allocation
    int cols;                   // stack allocation
    const GaitParams params;        

public:
    // Variables
    std::unique_ptr<Eigen::MatrixXf> sequence;  // Creates pointer to data type

    // Constructors
    GaitSequence();
    ~GaitSequence();        // Dont technically need this since we use smart pointers

    // Setters
    void StandingGait();
    void TrottingGait();

    // Getters
    void Print() {std::cout << *sequence << '\n';};
};

GaitSequence::GaitSequence() : rows(params.Nodes), cols(4*params.Nodes)
{
    sequence = std::make_unique<Eigen::MatrixXf>(Eigen::MatrixXf::Zero(rows, cols));
}

void GaitSequence::StandingGait()
{
    for(int node = 0; node <= params.Nodes; node++){
        sequence->block<1,4>(node,4*node) << 1.0, 1.0, 1.0, 1.0;
    }
};

void GaitSequence::TrottingGait()
{
    // Import the gait parameters as a constant
    float gait_time = params.Curr_Gait_Time;

    // Make this a list of matricies 
    for(int node = 0; node <= params.Nodes; node++){
        if(gait_time <= params.Stance_Time/2.0){                                // Double Stance
            sequence->block<1,4>(node,4*node) << 1.0, 1.0, 1.0, 1.0;
            gait_time = gait_time + params.Horizon_dt;
        } else if(gait_time <= params.Stance_Time/2.0 + params.Swing_Time/2){   // Single Stance
            sequence->block<1,4>(node,4*node) << 1.0, 0.0, 1.0, 0.0;
            gait_time = gait_time + params.Horizon_dt;
        } else if(gait_time <= params.Stance_Time + params.Swing_Time/2){       // Double Stance
            sequence->block<1,4>(node,4*node) << 1.0, 1.0, 1.0, 1.0;
            gait_time = gait_time + params.Horizon_dt;
        } else if(gait_time <= params.Gait_Time){                               // Single Stance
            sequence->block<1,4>(node,4*node) << 0.0, 1.0, 0.0, 1.0;    
            gait_time = gait_time + params.Horizon_dt;
        } else {                                                                // Reset the time variable
            gait_time = gait_time - params.Gait_Time;                                                    
        }
        // std::cout << node << " " << gait_time << " " << sequence->block<1,4>(node,4*node) << '\n';
    }
};


GaitSequence::~GaitSequence()
{
    std::cout << "Gait Sequence Object Destroyed" << '\n';
}