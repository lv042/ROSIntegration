#pragma once

#include "CoreMinimal.h"
#include "Conversion/Messages/BaseMessageConverter.h"
#include "Conversion/Messages/std_msgs/StdMsgsHeaderConverter.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "TrajectoryMsgsJointTrajectoryConverter.generated.h"


UCLASS()
class ROSINTEGRATION_API UTrajectoryMsgsJointTrajectoryConverter : public UBaseMessageConverter
{
	GENERATED_BODY()

public:
	UTrajectoryMsgsJointTrajectoryConverter();
	virtual bool ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg>& BaseMsg);
	virtual bool ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message);

	static bool _bson_extract_child_joint_trajectory(bson_t *b, FString key, ROSMessages::trajectory_msgs::JointTrajectory *msg, bool LogOnErrors = true)
	{
		bool KeyFound = false;

		if (!UStdMsgsHeaderConverter::_bson_extract_child_header(b, key + ".header", &msg->header)) return false;
		//msg->seq = GetInt32FromBSON(key + ".seq", b, KeyFound); if (!KeyFound) return false;
		//msg->stamp = GetDoubleFromBSON(key + ".stamp", b, KeyFound, LogOnErrors); if (!KeyFound) return false;
		//msg->frame_id = GetFStringFromBSON(key + ".frame_id", b, KeyFound); if (!KeyFound) return false;
		msg->joint_names = GetTArrayFromBSON<FString>(key + ".joint_names", b, KeyFound, [](FString subKey, bson_t* subMsg, bool& subKeyFound) { return GetFStringFromBSON(subKey, subMsg, subKeyFound, false); });
		//msg->points = GetDoubleTArrayFromBSON(key + ".points", b, KeyFound); if (!KeyFound) return false;
		msg->positions = GetDoubleTArrayFromBSON(key + ".points[0].positions", b, KeyFound); if (!KeyFound) return false;
		msg->velocities = GetDoubleTArrayFromBSON(key + ".points[0].velocities", b, KeyFound); if (!KeyFound) return false;
		msg->accelerations = GetDoubleTArrayFromBSON(key + ".points[0].accelerations", b, KeyFound); if (!KeyFound) return false;
		msg->time_from_start = GetDoubleFromBSON(key + ".points[0].time_from_start", b, KeyFound, LogOnErrors); if (!KeyFound) return false;

		if (!KeyFound) return false;
		return true;
	}
/*
	static void _bson_append_child_joint_state(bson_t *b, const char *key, const ROSMessages::sensor_msgs::JointState *msg)
	{
		bson_t child;
		BSON_APPEND_DOCUMENT_BEGIN(b, key, &child);
		_bson_append_joint_state(&child, msg);
		bson_append_document_end(b, &child);
	}

	static void _bson_append_joint_state(bson_t *b, const ROSMessages::sensor_msgs::JointState *msg)
	{
		UStdMsgsHeaderConverter::_bson_append_child_header(b, "header", &msg->header);
		_bson_append_tarray<FString>(b, "name", msg->name, [](bson_t *subb, const char *subKey, FString str) { BSON_APPEND_UTF8(subb, subKey, TCHAR_TO_UTF8(*str)); });
		_bson_append_double_tarray(b, "position", msg->position);
		_bson_append_double_tarray(b, "velocity", msg->velocity);
		_bson_append_double_tarray(b, "effort", msg->effort);
	}
*/
};