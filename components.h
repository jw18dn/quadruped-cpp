#include <Eigen/Dense>

using namespace Eigen;


// Header File Parts
class Body{
public:
    Body();
    void Print();
    // state_vec Calc_Des_States();

private:
    Matrix <float,6,1> qB_ic;
    Matrix <float,6,1> qB_des;
    Matrix <float,6,1> dqB_ic;
    Matrix <float,6,1> dqB_des;

};

/*
class Leg{
public:
    Leg();
    state_vec Calc_Des_States();
private:
    state_vec leg_states;
    state_vec des_leg_states;
};

class Toe{
public:
    Toe();
    state_vec Calc_Des_States();
private:
    state_vec toe_states;
    state_vec des_toe_states;
};
*/
