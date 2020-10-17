#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <string>

class Output {
  double steering_angle;
  double throttle;

 public:
  Output(double steering_angle, double throttle)
      : steering_angle(steering_angle), throttle(throttle) {}
  // Serialize for WebSocket output
  std::string to_string() const {
    return R"(42["steer",{"steering_angle":)" + std::to_string(steering_angle) +
           R"(,"throttle":)" + std::to_string(throttle) + "}]";
  }
  friend std::ostream& operator<<(std::ostream& os, const Output& o);
};

std::ostream& operator<<(std::ostream& os, const Output& o) {
  return os << o.to_string();
}

#endif  // OUTPUT_H
