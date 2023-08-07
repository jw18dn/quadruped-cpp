#include <iostream>
#include "components.h"
using namespace std;

// This will be a structure (one struct for each leg)

Body::Body(){
    qB_ic.setZero();
};

void Body::Print(){
    cout << qB_ic << endl;
};