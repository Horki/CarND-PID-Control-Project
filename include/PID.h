#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError() const;

 private:
  struct Data {
    double p;
    double i;
    double d;
    Data() : p(0), i(0), d(0) {}
  };

  /**
   * PID Errors
   */
  struct Data error;

  /**
   * PID Coefficients
   */
  struct Data coefficients;
};

#endif  // PID_H