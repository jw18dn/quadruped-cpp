#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;

// Header File Parts
class Gait{
    public:
        // Constructor
        Gait();
        ~Gait();

        // Setters
        void SetGaitTime(float);
        void SetSwingTime(float);

        // Modifiers
        MatrixXi ModifyGait(int,float);           
        VectorXf ModifyTimeVec(int);

        // Print
        void Print();

    private:
        // User Defined Variables
        int opt_nodes;
        float gait_time, horizon_time;
        float swing_time;                   // swing time for single leg
        float curr_time;

        // Valculated Values
        int horz_nodes;
        float gait_dt;
        VectorXf gait_seq_time_vec, gait_cycle_time_vec;      
        MatrixXi gait_cycle, gait_sequence;
};

