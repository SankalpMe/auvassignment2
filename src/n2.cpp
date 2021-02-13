#include <yaml-cpp/yaml.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <vector>
#include <sstream>
#include "asig/setpoint.h"
#include "asig/displace.h"


double px = 0;
double py = 0;
double pz = 0;
ros::ServiceClient client;
ros::Publisher pub;

using std::to_string;
void onSetTarget(const asig::setpoint::ConstPtr& p) {
      double x = p->x ;
      double y = p->y;
      double z = p->z;
      
     
      
      asig::displace srv;
      srv.request.mode = 0;
      srv.request.param = x-px;
      std::cout << "Navigating To : " << p->x << "," << py << "," << pz << std::endl;
      if(client.call(srv)){
	std::cout << "Navigated To : " << p->x << "," << py << "," << pz << std::endl;
      }else{
	std::cerr << "Failed To Navigate To : " << p->x << "," << py << "," << pz << std::endl;
      }
      
    
      srv.request.mode = 1;
      srv.request.param = y-py;
       std::cout << "Navigating To : " << p->x << "," << p->y << "," << pz << std::endl;
      if(client.call(srv)){
	std::cout << "Navigated To : " << p->x << "," << p->y << "," << pz << std::endl;
      }else{
	std::cerr << "Failed To Navigate To : " << p->x << "," << p->y << "," << pz << std::endl;
      }
      
    
      srv.request.mode = 2;
      srv.request.param = z-pz;
      std::cout << "Navigating To : " << p->x << "," << p->y << "," << p->z << std::endl;
      if(client.call(srv)){
	std::cout << "Navigated To : " << p->x << "," << p->y << "," << p->z << std::endl;
      }else{
	std::cerr << "Failed To Navigate To : " << p->x << "," << p->y << "," << p->z << std::endl;
      }
      
      
      std::cout << "Navigation Complete" << std::endl << std::endl;
      
      std_msgs::String fmsg;
      std::string tstr = "Reached: ";
      tstr += to_string(x);
      tstr += ",";
      tstr += to_string(y);
      tstr += ",";
      tstr += to_string(z);
      tstr += " .";
      
      fmsg.data = tstr.c_str();
      
      pub.publish(fmsg);
      px = x;
      py = y;
      pz = z;
}



int main(int argc, char **argv) {
	ros::init(argc,argv,"n2");

	ros::NodeHandle n;
	
	ros::Subscriber sub = n.subscribe("targetpoint",1000,onSetTarget);
	pub = n.advertise<std_msgs::String>("t1", 1000);
	client =  n.serviceClient<asig::displace>("s1");
	
	ros::spin();
	return 0;
}
