//
// Created by Matthew Jones on 7/17/17.
//

#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H


#include <vector>

class twiddle {
public:
    twiddle(double tolerance);
    virtual ~twiddle();

    // Initializer to set default values
    std::vector<double> Init(std::vector<double> init);

    std::vector<double> Iterate(double error);

private:
    // Values that we're changing
    std::vector<double> params;
    std::vector<double> saved;

    double current_step;
    double best_error;
    double prev_error;
    double step;
    double iteration;
    int current_param;
    int current_attempt;
    int attempts_before_switching;
    bool going_up;
};


#endif //PID_TWIDDLE_H
