// NPVR TEST

#ifndef NPVR_OVR_MANAGER_H_
#define NPVR_OVR_MANAGER_H_

#include <OVR.h>


namespace npvr {

class OVRManager {
public:
  static OVRManager *Instance();
  bool DevicePresent() const;
  OVR::Quatf* &GetOrientation() const;
  OVR::Vector3f* &GetPosition() const;
  ovrHmd &OVRManager::GetConfiguration() const;
private:
  OVRManager();
  ovrHmd     hmd_device_;
};

}  // namespace npvr


#endif  // NPVR_OVR_MANAGER_H_
