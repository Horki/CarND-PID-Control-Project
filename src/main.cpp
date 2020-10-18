#include <uWS/uWS.h>

#include <iostream>
#include <string>

#include "PID.h"
#include "helper.hpp"
#include "json.hpp"

int main() {
  uWS::Hub h;

  PID pid;
  /**
   * Initialize the pid variable.
   */
  pid.Init(0.1, 0.001, 2.0);

  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    std::string income = std::string(data);
    if (length && length > 2 && income.substr(0, 2) == "42") {
      std::string s = hasData(income);

      if (s != "") {
        nlohmann::json j = nlohmann::json::parse(s);

        std::string event = j[0].get<std::string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          double speed = std::stod(j[1]["speed"].get<std::string>());
          double angle = std::stod(j[1]["steering_angle"].get<std::string>());

          /**
           * Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          pid.UpdateError(cte);
          double steer_value = pid.TotalError();

          std::cout << "CTE:" << cte << ", speed:" << speed
                    << ", angle:" << angle << ", Steering Value:" << steer_value
                    << std::endl;
          Output o = Output(steer_value, 0.3);
          std::string msg = o.to_string();
          std::cout << o << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        std::string msg = R"(42["manual",{}])";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  });  // end h.onMessage

  h.onConnection([](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    uS::Socket::Address address = ws.getAddress();
    std::cout << "Request headers: " << req.headers->toString() << std::endl;
    std::cout << "Websocket address: " << address.address << ":" << address.port
              << ", family: " << address.family << std::endl;
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([](uWS::WebSocket<uWS::SERVER> ws, int code, char *message,
                       size_t length) {
    std::cout << "Disconnected; code: " << code << ", message: " << message
              << ", length: " << length << std::endl;
    ws.close();
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port\n";
    return -1;
  }

  h.run();
}
