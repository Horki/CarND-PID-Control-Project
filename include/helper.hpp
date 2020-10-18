#ifndef OUTPUT_H
#define OUTPUT_H

#include <cmath>  // M_PI
#include <iostream>
#include <string>

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  unsigned long found_null = s.find("null");
  unsigned long b1 = s.find_first_of("[");
  unsigned long b2 = s.find_last_of("]");

  if (found_null != std::string::npos) {
    return "";
  } else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  } else {
    return "";
  }
}

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
