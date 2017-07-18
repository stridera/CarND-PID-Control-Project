#include <iostream>

#include "PID.h"


using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    cout << "PID Initialized with values: (" << Kp << ", " << Ki << ", " << Kd << ")" << endl;

    // Set errors to 0;
    p_error = 0;
    i_error = 0;
    d_error = 0;
}

// cte = p_error, diff_cte = d_error, int_cti = i_error

// cte = robot.y
// diff_cte = cte - prev_cte
// prev_cte = cte
// int_cte += cte
void PID::UpdateError(double cte) {
    // then add the current cte term to the count int_cte += cte.
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
}

// steer = -tau_p * cte     - tau_d * diff_cte - tau_i * int_cte
// error = - Kp   * p_error - Kd    * d_error  - Ki    * i_error
double PID::TotalError() {
    // Finally we update the steering value, -tau_p * cte - tau_d * diff_cte - tau_i * int_cte with the new tau_i parameter.
    double error = -Kp * p_error - Kd * d_error - Ki * i_error;

    return error;
}

