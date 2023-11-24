#include "gait.h"

// Constructor
Gait::Gait(){
    // Default Values
    opt_nodes = 11;
    gait_time = 1;
    horizon_time = 1.5;
    curr_time = 0.3;
    swing_time = 0.35;

    // Calculated Values
    gait_dt = gait_time/(opt_nodes-1);
    horz_nodes = horizon_time/gait_dt + 1;
};

// Setters ----------------------------------------------------------
void Gait::SetGaitTime(float new_gait_time){
   //  NEED TO: Error Check "gait_time" parameters 

   // update the time we are in the gait cycle
    gait_time = new_gait_time;

    // Update the time incraments
    gait_dt = gait_time/(opt_nodes-1);

    // Update the gait cycle time vec
    gait_cycle_time_vec.resize(opt_nodes);
    gait_cycle_time_vec = ModifyTimeVec(opt_nodes);

    // Update the gait cycle
    gait_cycle.resize(opt_nodes,4);
    gait_cycle = ModifyGait(opt_nodes,0.001);

    // Update the gait sequence
    gait_sequence.resize(horz_nodes,4);
    gait_sequence = ModifyGait(horz_nodes,curr_time);
};

void Gait::SetSwingTime(float new_swing_time){
    //  NEED TO: Error Check "swing_t" parameters 

    // update the time we are in the gait cycle
    swing_time = new_swing_time;

    // Update the gait cycle
    gait_cycle.resize(opt_nodes,4);
    gait_cycle = ModifyGait(opt_nodes,0.001);

    // Update the gait sequence
    gait_sequence.resize(horz_nodes,4);
    gait_sequence = ModifyGait(horz_nodes,curr_time);
};

// Auto Modifiers ----------------------------------------------------
VectorXf Gait::ModifyTimeVec(int iters){
    // Set the temp time vec size
    VectorXf temp_time_vec(iters);

    // Loop through changing values
    for(int i=  0; i < iters; i++){
        temp_time_vec(i) = i*gait_dt;
    }
    return temp_time_vec;
}


MatrixXi Gait::ModifyGait(int iters, float time_temp){
    // Temporary cycle
    MatrixXi temp_gait_cycle(iters,4);

    // Find the time variables
    float stance_time = (gait_time - swing_time*2.0)/2.0;

    // Loop through developing the new gait sequence
    for(int i = 0; i < iters; i++){
        if(time_temp <= stance_time){                                  // Double Stance
            temp_gait_cycle.row(i) << 1, 1, 1, 1;
        } else if(time_temp <= stance_time + swing_time){              // Single Stance
            temp_gait_cycle.row(i) << 1, 0, 1, 0;
        } else if(time_temp <= stance_time*2.0 + swing_time){          // Double Stance
            temp_gait_cycle.row(i) << 1, 1, 1, 1;
        } else if(time_temp <= stance_time*2.0 + swing_time*2.0){      // Single Stance
            temp_gait_cycle.row(i) << 0, 1, 0, 1;    
        } else {                                                       // Reset the time variable
            time_temp = 0;                                                    
            i--;
        }
        time_temp = time_temp + gait_dt;
    };
    return temp_gait_cycle;
}


void Gait::Print(){
    std::cout << gait_cycle_time_vec << "\n" << std::endl;
    std::cout << gait_cycle << "\n" << std::endl;
    std::cout << gait_sequence << "\n" << std::endl;
}
