#ifndef MITCH_ROS_SERIAL_CONNECTION_H
#define MITCH_ROS_SERIAL_CONNECTION_H

#include <ros/ros.h>

#include <mitch/Mitch_SerialConnection.h>

#include <mitch_v2_driver/StopTransmission.h>
#include <mitch_v2_driver/Shutdown.h>
#include <mitch_v2_driver/Disconnect.h>

using namespace Mitch;
using namespace std;

const string DEFAULT_FRAME_ID = "";
const string DEFAULT_PORT_NAME = "";
const uint32_t DEFAULT_BAUDRATE = 115200;

namespace mitch_v2_driver {

	class Mitch
	{
	public:

		struct Params
		{
			string frame_id = DEFAULT_FRAME_ID;
			string port_name = DEFAULT_PORT_NAME;
			uint32_t baudrate = DEFAULT_BAUDRATE;
			Timeout timeout = Timeout();
		};

		Mitch(ros::NodeHandle& node) {
			setupParams(node);
			serial = new Mitch_SerialConnection(params.port_name, params.baudrate, params.timeout);
		};

		~Mitch() = default;

		Params params;
		Mitch_SerialConnection* serial;

		void setupParams(ros::NodeHandle& node);
		bool stopTransmission(StopTransmission::Request& req, StopTransmission::Response& res, Mitch* mitch);
		bool shutdown(Shutdown::Request& req, Shutdown::Response& res, Mitch* mitch, std::vector<ros::Subscriber>& sub_vect);
		bool disconnect(Disconnect::Request& req, Disconnect::Response& res, Mitch* mitch, std::vector<ros::Subscriber>& sub_vect);

	};
}

#endif 