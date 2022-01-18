#include <mitch_v2_driver/MitchV2_Request.h>
#include <muse_v2_driver/Battery.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "battery");

    ros::NodeHandle n;

    mitch_v2_driver::MitchV2Request request;

    request.setupRequest(n);

    ros::ServiceClient client = n.serviceClient<mitch_v2_driver::Battery>("battery");

    if (request.input_command == request.default_command_list) {
        ROS_ERROR("No request found.");
        ros::shutdown();
        return -1;
    }

    mitch_v2_driver::Battery srv;

    if (request.input_command.get_battery_charge)
        srv.request.get_battery_charge = true;

    if (request.input_command.get_battery_voltage)
        srv.request.get_battery_voltage = true;

    if (client.call(srv))
    {
        if (srv.request.get_battery_charge) 
            ROS_INFO("Battery charge (%%): %.2f", srv.response.battery_charge);

        if (srv.request.get_battery_voltage) 
            ROS_INFO("Battery voltage [mV]: %.2f", srv.response.battery_voltage);
    }
    else
    {
        ROS_ERROR("Failed to call battery service.");
        return 1;
    }

    return 0;
}