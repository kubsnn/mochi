#include "device_controller.hpp"

namespace mochi::controllers {

    device_info device_controller::getDeviceInfo()
    {
        return deviceService_->getDeviceInfo();
    }

}