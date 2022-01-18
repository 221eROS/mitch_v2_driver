#ifndef MITCH_V2_REQUEST_H
#define MITCH_V2_REQUEST_H

#include <mitch_v2_driver/MitchV2_SerialConnection.h>
#include <mitch_v2_driver/Battery.h>
#include <mitch_v2_driver/FirmwareVersion.h>

namespace mitch_v2_driver {

	class MitchV2Request
	{
	public:

		struct CommandList
		{
			bool get_battery_charge = false;
			bool get_battery_voltage = false;
			bool get_firmware_version = false;

			bool operator==(const CommandList& rhs) const {
				return  (
					(get_battery_charge == rhs.get_battery_charge) &&
					(get_battery_voltage == rhs.get_battery_voltage) &&
					(get_firmware_version == rhs.get_firmware_version)
					);
			}

		} default_command_list;

		CommandList input_command, received_command;

		MitchV2Request() = default;
		~MitchV2Request() = default;

		void setupRequest(ros::NodeHandle& node);
		bool getBattery(Battery::Request& req, Battery::Response& res, MitchV2* mitch_v2);
		bool getFirmwareVersion(FirmwareVersion::Request& req, FirmwareVersion::Response& res, MitchV2* mitch_v2);


	};
}

#endif 