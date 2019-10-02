#include "PID.h"
#include <algorithm>
#include <iostream>

PID::PID() : p_error(0.0), i_error(0.0), d_error(0.0) {}

PID::~PID() {}

/**
 * Initialize PID coefficients (and errors, if needed)
 */
void PID::Init(double Kp_, double Ki_, double Kd_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}

/**
 * Update PID errors based on cte.
 */
void PID::UpdateError(double cte) {
  d_error  = cte - p_error;
  i_error += cte;
  p_error  = cte;
  std::cout << "d:" << d_error << ", i:" << i_error << ", p:" << p_error
            << std::endl;
}

/**
 * Calculate and return the total error,
 * remember the steering value is [-1, 1]
 */
double PID::TotalError() {
  double steer = (-Kp * p_error) - (Kd * d_error) - (Ki * i_error);
  return std::max(std::min(steer, 1.0), -1.0);
}
