#include "ros/ros.h"
#include "mitch_v2_driver/StopTransmission.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "stop_transmission");

    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<mitch_v2_driver::StopTransmission>("stop_transmission");

    mitch_v2_driver::StopTransmission srv;

    srv.request.stop_transmission = true;

    if (client.call(srv))
    {
        ROS_INFO("Stop Transmission: %s", srv.response.transmission_stopped ? "true" : "false");
    }
    else
    {
        ROS_ERROR("Failed to stop transmission.");
        return 1;
    }

    return 0;
}