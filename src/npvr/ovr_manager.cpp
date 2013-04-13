// NPVR TEST

#include <npvr/ovr_manager.h>


using namespace npvr;

OVRManager *OVRManager::Instance() {
  static OVRManager instance;
  return &instance;
}

OVRManager::OVRManager() :
    hmd_device_(NULL),
    sensor_fusion_(NULL) {
  OVR::System::Init();
  device_manager_ = OVR::DeviceManager::Create();
  device_manager_->SetMessageHandler(this);
  OVR::HMDDevice* hmd_device = device_manager_->EnumerateDevices<OVR::HMDDevice>().CreateDevice();
  if (hmd_device) {
    SetDevice(hmd_device);
  }
}

OVRManager::~OVRManager() {
  SetDevice(NULL);
  OVR::System::Destroy();
}

void OVRManager::OnMessage(const OVR::Message &message) {
  switch(message.Type) {
  case OVR::MessageType::Message_DeviceAdded:
    break;
  case OVR::MessageType::Message_DeviceRemoved:
    // TODO: Verify that the removed device is the one we're using.
    if (hmd_device_) {
      hmd_device_->Release();
      hmd_device_ = NULL;
    }
    break;
  default:
    break;
  }
}

OVR::HMDDevice* OVRManager::GetDevice() const {
  return hmd_device_;
}

void OVRManager::SetDevice(OVR::HMDDevice* device) {
  if (hmd_device_ == device) {
    return;
  }
  if (hmd_device_) {
    // Release existing device.
    hmd_device_->Release();
    delete sensor_fusion_;
  }
  if (!device) {
    return;
  }
  hmd_device_ = device;
  sensor_fusion_ = new OVR::SensorFusion();
  sensor_fusion_->AttachToSensor(hmd_device_->GetSensor());
}

bool OVRManager::DevicePresent() const {
  return hmd_device_ != NULL;
}

OVR::Quatf &OVRManager::GetOrientation() const {
  return sensor_fusion_->GetOrientation();
}

void OVRManager::ResetOrientation() {
  sensor_fusion_->Reset();
}
