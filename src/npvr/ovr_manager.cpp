// NPVR TEST

#include <npvr/ovr_manager.h>


using namespace npvr;

OVRManager *OVRManager::Instance() {
  static OVRManager instance;
  return &instance;
}

OVRManager::OVRManager() {
	ovr_Initialize();
	ovrHmd hmd_devive = ovrHmd_Create(0);
	hmd_device_ = hmd_devive;

	ovrHmd_ConfigureTracking(hmd_devive, ovrTrackingCap_Orientation |
		ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position, 0);
}

bool OVRManager::DevicePresent() const {
  return hmd_device_;
}

OVR::Quatf* &OVRManager::GetOrientation() const {

	static ovrPosef eyeRenderPose[2];

	ovrEyeType eye = hmd_device_->EyeRenderOrder[0];
	eyeRenderPose[0] = ovrHmd_GetEyePose(hmd_device_, eye);

	OVR::Quatf* orientation = new OVR::Quatf(eyeRenderPose[0].Orientation.x, eyeRenderPose[0].Orientation.y, eyeRenderPose[0].Orientation.z, eyeRenderPose[0].Orientation.w);
	
	return orientation;
}

OVR::Vector3f* &OVRManager::GetPosition() const {

	static ovrPosef eyeRenderPose[2];

	ovrEyeType eye = hmd_device_->EyeRenderOrder[0];
	eyeRenderPose[0] = ovrHmd_GetEyePose(hmd_device_, eye);	

	OVR::Vector3f* position = new OVR::Vector3f(eyeRenderPose[0].Position.x, eyeRenderPose[0].Position.y, eyeRenderPose[0].Position.z);

	return position;
}

ovrHmd &OVRManager::GetConfiguration() const {

	ovrHmd test = hmd_device_;
	return test;
}

