#include <yaml-cpp/yaml.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <vector>
#include <sstream>
#include "asig/setpoint.h"
using std::vector;
struct Point{
	double x;
	double y;
	double z;
};
class n1{
	public:
	YAML::Node pathConfig;
	ros::Subscriber sub;
	ros::Publisher pub;
	int currentPos ;
	int maxPos ;
	void onPointReach(const std_msgs::String::ConstPtr& msg){
		std::cout << "Recieved: " << msg->data << std::endl;
		sendNext();
	}
	void init(ros::NodeHandle &n){
		
		pathConfig = YAML::LoadFile("path.yaml");
		
		currentPos = -1;
		maxPos = pathConfig["points"].size();
		
		sub = n.subscribe("t1", 1000, &n1::onPointReach,this);
		pub = n.advertise<asig::setpoint>("targetpoint", 1000);
		ros::Duration(2).sleep();
		sendNext();	
		ros::spin();
	}

	void sendNext(){
		currentPos++;
		ros::Rate loop_rate(10);
		while(pub.getNumSubscribers() == 0 && ros::ok()){
			loop_rate.sleep();
		}
	
		
		
		
		int tpos = currentPos;
		if(currentPos < maxPos){
			std::string row =  pathConfig["points"][currentPos].as<std::string>();

			std::stringstream rs(row);
			Point p;
			rs >> p.x >> p.y >> p.z;
			
			asig::setpoint pmsg;
			pmsg.x = p.x;
			pmsg.y = p.y;
			pmsg.z = p.z;
			
			
			pub.publish(pmsg);
		
			std::cout << "Sent New Point: " << row << std::endl;
			
				
		}
	}
};

int main(int argc, char **argv) {
	ros::init(argc,argv,"n1");

	n1 a;
	ros::NodeHandle n;

	a.init(n);
	return 0;
}
