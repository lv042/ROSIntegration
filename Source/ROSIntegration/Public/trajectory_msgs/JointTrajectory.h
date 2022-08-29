#pragma once

#include "ROSBaseMsg.h"
#include "std_msgs/Header.h"
#include "Math/Vector.h" 

namespace ROSMessages {
	namespace trajectory_msgs {
		class JointTrajectory : public FROSBaseMsg {
		public:
			JointTrajectory() {
				_MessageType = "trajectory_msgs/JointTrajectory";
			}


			ROSMessages::std_msgs::Header header;
			uint32 seq;
			float  stamp;
			FString frame_id;

			TArray<FString> joint_names;
			TArray<double> points;
			TArray<double> positions;
			TArray<double> velocities;
			TArray<double> accelerations;
			float time_from_start;
		};
	}
}
