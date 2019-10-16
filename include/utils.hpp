#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <vector>

#include "platformCommunications.grpc.pb.h"

using platformcomms::Pose;
using platformcomms::Quaternion;
using platformcomms::Vector3D;

using platformcomms::AlertLevel;
using platformcomms::PlatformState;
using pStatus = platformcomms::Status;
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

    std::vector<PlatformState> states_list;

    static void statesFactory(std::vector<PlatformState>& list)
    {
        PlatformState* state;
        state->set_status(pStatus::Ready);
        set_pose(state->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
        state->set_liftheight(3.1);
        state->set_stable(true);
        state->set_batterylevel(5.0);
    
        Alert* alert = state->add_alerts();
        Utils::set_alert(alert, "GoToHeight State", 11111, "topic", AlertLevel::Info);

        for (int i = 0; i<10; ++i)
        {
            list.push_back(*state);
        }
    }
};

#endif //UTILS_H