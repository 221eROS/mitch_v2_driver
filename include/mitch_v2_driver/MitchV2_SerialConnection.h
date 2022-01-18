#ifndef MITCH_ROS_SERIAL_CONNECTION_H
#define MITCH_ROS_SERIAL_CONNECTION_H

#include <ros/ros.h>

#include <mitch_v2/MitchV2_SerialConnection.h>

#include <mitch_v2_driver/StopTransmission.h>
#include <mitch_v2_driver/Shutdown.h>
#include <mitch_v2_driver/Disconnect.h>

using namespace MitchV2;
using namespace std;

const string DEFAULT_FRAME_ID = "";
const string DEFAULT_PORT_NAME = "";
const uint32_t DEFAULT_BAUDRATE = 115200;

namespace mitch_v2_driver {

	class MitchV2
	{
	public:

		struct Params
		{
			string frame_id = DEFAULT_FRAME_ID;
			string port_name = DEFAULT_PORT_NAME;
			uint32_t baudrate = DEFAULT_BAUDRATE;
			Timeout timeout = Timeout();
		};

		MitchV2(ros::NodeHandle& node) {
			setupParams(node);
			serial = new MitchV2_SerialConnection(params.port_name, params.baudrate, params.timeout);
		};

		~MitchV2() = default;

		Params params;
		MitchV2_SerialConnection* serial;

		void setupParams(ros::NodeHandle& node);
		bool stopTransmission(StopTransmission::Request& req, StopTransmission::Response& res, MitchV2* mitch_v2);
		bool shutdown(Shutdown::Request& req, Shutdown::Response& res, MitchV2* mitch_v2, std::vector<ros::Subscriber>& sub_vect);
		bool disconnect(Disconnect::Request& req, Disconnect::Response& res, MitchV2* mitch_v2, std::vector<ros::Subscriber>& sub_vect);

	};
}

#endif 