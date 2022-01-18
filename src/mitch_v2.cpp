#include <mitch_v2_driver/MitchV2_Request.h>
#include <mitch_v2_driver/MitchV2_SerialConnection.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "muse");

	ros::NodeHandle n;

	mitch_v2_driver::MitchV2 mitch_v2(n);

	std::string port = mitch_v2.params.port_name;
	ROS_INFO("Port name: %s", port.c_str());
	ROS_INFO("Baudrate: %d", mitch_v2.params.baudrate);

	int publisher_queue_size;

	if (!n.getParam("publisher_queue_size", publisher_queue_size))
		ROS_WARN("No publisher_queue_size parameter found on server. Use default one.");

	mitch_v2_driver::MitchV2Request request;

	vector<ros::Subscriber> sub_vect;

	//ros::Subscriber stream_sub = n.subscribe<muse_v2_driver::Transmission>("start_transmission", 1, boost::bind(&muse_v2_driver::Stream::StreamRawData, &stream, _1, &muse));
	//sub_vect.push_back(stream_sub);

	//ros::ServiceServer stop_transmission_srv = n.advertiseService<muse_v2_driver::StopTransmission::Request, muse_v2_driver::StopTransmission::Response>
	//	("stop_transmission", boost::bind(&muse_v2_driver::Muse::stopTransmission, &muse, _1, _2, &muse));

	ros::ServiceServer shutdown_srv = n.advertiseService<mitch_v2_driver::Shutdown::Request, mitch_v2_driver::Shutdown::Response>
		("shutdown", boost::bind(&mitch_v2_driver::MitchV2::shutdown, &mitch_v2, _1, _2, &mitch_v2, sub_vect));

	ros::ServiceServer battery_srv = n.advertiseService<mitch_v2_driver::Battery::Request, mitch_v2_driver::Battery::Response>
		("battery", boost::bind(&mitch_v2_driver::MitchV2Request::getBattery, &request, _1, _2, &mitch_v2));


	ROS_INFO("Mitch V2 ready.");

	ros::spin();

	return 0;

}
