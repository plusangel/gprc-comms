#ifndef UTILS_H
#define UTILS_H

#include <array>

#include "platformCommunications.grpc.pb.h"

using platformcomms::Pose;
using platformcomms::Quaternion;
using platformcomms::Vector3D;

using platformcomms::Alert;

class Utils {

public:
    static void set_pose(Pose* aPose, std::array<double, 3> position, std::array<double, 4> quaternion)
    {
        aPose->mutable_position()->set_x(position[0]);
        aPose->mutable_position()->set_y(position[1]);
        aPose->mutable_position()->set_z(position[2]);

        aPose->mutable_orientation()->set_x(quaternion[0]);
        aPose->mutable_orientation()->set_y(quaternion[1]);
        aPose->mutable_orientation()->set_z(quaternion[2]);
        aPose->mutable_orientation()->set_r(quaternion[3]);
    }

    static void set_alert(Alert* alert, std::string title, int64_t timestamp, std::string topic, platformcomms::AlertLevel level)
    {
        alert->set_title(title);
        alert->set_timestamp(timestamp);
        alert->set_topic(topic);
        alert->set_severity(level);
    }
};

#endif //UTILS_H