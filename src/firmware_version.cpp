#include <mitch_v2_driver/MitchV2_Request.h>
#include <mitch_v2_driver/FirmwareVersion.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "firmware version");

    ros::NodeHandle n;

    mitch_v2_driver::MitchV2Request request;

    request.setupRequest(n);

    ros::ServiceClient client = n.serviceClient<mitch_v2_driver::FirmwareVersion>("firmware_version");

    if (request.input_command == request.default_command_list) {
        ROS_ERROR("No request found.");
        ros::shutdown();
        return -1;
    }

    mitch_v2_driver::FirmwareVersion srv;

    if (request.input_command.get_firmware_version)
        srv.request.get_firmware_version = true;

    if (client.call(srv))
    {

        if (srv.request.get_firmware_version)
            ROS_INFO("Firmware version: %s", srv.response.firmware_version.c_str());
    }
    else
    {
        ROS_ERROR("Failed to call firmware version service.");
        return 1;
    }

    return 0;
}