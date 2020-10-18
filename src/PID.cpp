#include "PID.h"

#include <algorithm>
#include <iostream>

PID::PID() {}

PID::~PID() {}

/**
 * Initialize PID coefficients (and errors, if needed)
 */
void PID::Init(double Kp_, double Ki_, double Kd_) {
  coefficients.p = Kp_;
  coefficients.i = Ki_;
  coefficients.d = Kd_;
}

/**
 * Update PID errors based on cte.
 */
void PID::UpdateError(double cte) {
  error.d = cte - error.p;
  error.i += cte;
  error.p = cte;
  std::cout << "d:" << error.d << ", i:" << error.i << ", p:" << error.p
            << std::endl;
}

/**
 * Calculate and return the total error,
 * remember the steering value is [-1, 1]
 */
double PID::TotalError() const {
  double steer = (-coefficients.p * error.p) - (coefficients.d * error.d) -
                 (coefficients.i * error.i);
  return std::max(std::min(steer, 1.0), -1.0);
}
