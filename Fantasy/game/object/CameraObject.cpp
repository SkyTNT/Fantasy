#include "CameraObject.h"
#include "../component/Camera.h"

CameraObject::CameraObject() : GameObject() {
    components.push_back(new Camera(this));
}

CameraObject::~CameraObject() {

}
