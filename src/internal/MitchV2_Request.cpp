#include <mitch_v2_driver/MitchV2_Request.h>

void mitch_v2_driver::MitchV2Request::setupRequest(ros::NodeHandle& node) {
	node.getParam("get_battery_charge", input_command.get_battery_charge);
	node.getParam("get_battery_voltage", input_command.get_battery_voltage);
	node.getParam("get_firmware_version", input_command.get_firmware_version);
}

bool mitch_v2_driver::MitchV2Request::getBattery(Battery::Request& req, Battery::Response& res, MitchV2* mitch_v2)
{
	bool out = false;

	ROS_INFO("request: get_battery_charge=%s, get_battery_voltage=%s",
		req.get_battery_charge ? "true" : "false",
		req.get_battery_voltage ? "true" : "false");

	if (req.get_battery_charge) {
		if (!received_command.get_battery_charge) {
			received_command.get_battery_charge = true;
			ROS_INFO("Asking Battery Charge.");
		}

		if (mitch_v2->serial->getBatteryCharge() > -1) {
			res.battery_charge = mitch_v2->serial->getBatteryCharge();
			out = true;
			ROS_INFO("Sending back battery charge (%%): %.2f", res.battery_charge);
		}
	}
	if (req.get_battery_voltage) {
		if (!received_command.get_battery_voltage) {
			received_command.get_battery_voltage = true;
			ROS_INFO("Asking Battery Voltage.");
		}
		if (mitch_v2->serial->getBatteryVoltage() > -1) {
			res.battery_voltage = mitch_v2->serial->getBatteryVoltage();
			out = true;
			ROS_INFO("Sending back battery voltage [mV]: %.2f", res.battery_voltage);
		}
	}

	return out;
}

bool mitch_v2_driver::MitchV2Request::getFirmwareVersion(FirmwareVersion::Request& req, FirmwareVersion::Response& res, MitchV2* mitch_v2){

	bool out = false;

	ROS_INFO("request: get_firmware_version=%s",
		req.get_firmware_version ? "true" : "false");

	if (req.get_firmware_version) {
		if (!received_command.get_firmware_version) {
			received_command.get_firmware_version = true;
			ROS_INFO("Asking Firmware Version.");
		}

		if (!mitch_v2->serial->getFirmwareVersion().empty()) {
			res.firmware_version = mitch_v2->serial->getFirmwareVersion();
			out = true;
			ROS_INFO("Sending back firmware version: %s", res.firmware_version.c_str());
		}
	}
	
	return out;
}