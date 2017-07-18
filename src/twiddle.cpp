//
// Created by Matthew Jones on 7/17/17.
//
#include <iostream>

#include "twiddle.h"

using namespace std;

twiddle::twiddle(double first_step) {
    current_step = first_step;
    cout << "Twiddle Initialized with first step at " << first_step << endl;
}

twiddle::~twiddle() {}

std::vector<double> twiddle::Init(std::vector<double> init) {
    params = init;
    saved = init;
    step = 0;
    iteration = 0;
    best_error = 9999999;
    prev_error = 9999999;

    current_param = 0;
    going_up = false;

    attempts_before_switching = 3;
    current_attempt = 0;

    cout << "Params: (" << params[0] << ", " << params[1] << ", " << params[2] << ")" << endl;

    return params;
}

/**
 * Trying a different approach.  Lets step through one value until the error consistently stops rising
 * @param error - The current error value
 * @return New values to try.
 */
std::vector<double> twiddle::Iterate(double error=999999) {
    cout << "Iterating.  Best error: " << best_error << "  Current Error: " << error << endl;
    if (error < best_error) {
        // We're moving in the right direction
        best_error = error;
        saved = params;
        current_attempt = 0;
        if (going_up) {
            cout << "Param " << current_param << " going up by " << current_step << endl;
            params[current_param] += current_step;
        } else {
            cout << "Param " << current_param << " going down by " << current_step << endl;
            params[current_param] -= current_step;
        }
    } else {
        current_attempt++;
        if (current_attempt > attempts_before_switching) {
            cout << "Flipping" << endl;
            going_up = !going_up;
            iteration++;
            current_attempt = 0;
            if (going_up) {
                cout << "Param " << current_param << " going up by " << current_step << endl;
                params[current_param] += current_step;
            } else {
                cout << "Param " << current_param << " going down by " << current_step << endl;
                params[current_param] -= current_step;
            }
            if (iteration > 6) {
                iteration = 0;
                // By now we bounced back and forth a few times, so we'll just go to the last saved value and step through params.
                cout << "Stepping Params" << endl;
                params = saved;
                current_param ++;
                if (current_param > params.size()) {
                    current_param = 0;
                    // Stepping down
                    cout << "Moving from a step of " << current_step;
                    current_step /= 10;
                    cout << " to a step of " << current_step << endl;
                }
            }
        }

    }

    cout << "Params: (" << params[0] << ", " << params[1] << ", " << params[2] << ")" << endl;
    return params;
}


/*
 * Reference:
 def twiddle(tol=0.2):
    p = [0, 0, 0]
    dp = [1, 1, 1]
    robot = make_robot()
    x_trajectory, y_trajectory, best_err = run(robot, p)

    it = 0
    while sum(dp) > tol:
        print("Iteration {}, best error = {}".format(it, best_err))
        for i in range(len(p)):
            p[i] += dp[i]
            robot = make_robot()
            x_trajectory, y_trajectory, err = run(robot, p)

            if err < best_err:
                best_err = err
                dp[i] *= 1.1
            else:
                p[i] -= 2 * dp[i]
                robot = make_robot()
                x_trajectory, y_trajectory, err = run(robot, p)

                if err < best_err:
                    best_err = err
                    dp[i] *= 1.1
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9
        it += 1
    return p
 */