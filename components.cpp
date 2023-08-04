#include <iostream>
#include "components.h"
using namespace std;


Body::Body(){
    qB_ic.setZero();
};

void Body::Print(){
    cout << qB_ic << endl;
};