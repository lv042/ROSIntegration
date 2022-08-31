#include "Conversion/Messages/trajectory_msgs/TrajectoryMsgsJointTrajectoryConverter.h"


UTrajectoryMsgsJointTrajectoryConverter::UTrajectoryMsgsJointTrajectoryConverter()
{
	_MessageType = "trajectory_msgs/JointTrajectory";
}

bool UTrajectoryMsgsJointTrajectoryConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg>& BaseMsg)
{

	auto msg = new ROSMessages::trajectory_msgs::JointTrajectory();
	BaseMsg = TSharedPtr<FROSBaseMsg>(msg);
	return _bson_extract_child_joint_trajectory(message->full_msg_bson_, "msg", msg);
}


bool UTrajectoryMsgsJointTrajectoryConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message)
{
	//auto CastMsg = StaticCastSharedPtr<ROSMessages::trajectory_msgs::JointTrajectory>(BaseMsg);
	//*message = bson_new();
	//_bson_append_joint_trajectory(*message, CastMsg.Get());
	return true;
}

