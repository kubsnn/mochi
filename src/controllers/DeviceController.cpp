#include "DeviceController.hpp"

namespace mochi::controllers {

    DeviceInfo DeviceController::getDeviceInfo()
    {
        return deviceService_->getDeviceInfo();
    }

}