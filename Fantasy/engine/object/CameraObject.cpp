#include "CameraObject.h"
#include "../component/Camera.h"

CameraObject::CameraObject() : GameObject() {
    addComponent(new Camera());
}

CameraObject::~CameraObject() {

}
