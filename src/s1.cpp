#include <yaml-cpp/yaml.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <vector>
#include <sstream>
#include "asig/displace.h"
#include <math.h>




bool navigate(asig::displace::Request  &req,
         asig::displace::Response &res)
{
  char dir = ' ';
  int mode = req.mode;
  int param = req.param;
  if(mode == 0){
      dir = 'x';
  }else if(mode == 1){
      dir = 'y';
  }else if(mode == 2){
      dir = 'z';
  }
  
  if(dir == ' '){
      std::cerr << "Unknown DOF" << std::endl;
      return false;
  }
  
  std::cout << "Going: d" << dir << ": " <<  param << std::endl;
  
  ros::Duration( std::abs(param) ).sleep();
  
  std::cout << "Motion Completed" << std::endl;
  
  return true;
}




int main(int argc, char **argv) {
	ros::init(argc,argv,"s1");

	ros::NodeHandle n;
	
	ros::ServiceServer service = n.advertiseService("s1", navigate);
      
	
	ros::spin();
	return 0;
}
