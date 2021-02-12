#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

//变换
class Transform : public Component {
public:
    Transform();

    void init() override;

    void tick() override;

    //获取世界坐标
    const glm::vec3 &getPosition();

    //获取世界欧拉角
    const glm::vec3 &getEulerAngles();

    //获取相对缩放
    const glm::vec3 &getScale();

    //获取相对坐标
    const glm::vec3 &getLocalPosition();

    //获取相对欧拉角
    const glm::vec3 &getLocalEulerAngles();

    //获取x轴
    const glm::vec3 &getLeft();

    //获取y轴
    const glm::vec3 &getUp();

    //获取z轴
    const glm::vec3 &getForward();

    //获取相对坐标变换到世界坐标的矩阵
    const glm::mat4 &getLocalToWorld();

    //获取世界坐标变换到相对坐标的矩阵
    const glm::mat4 &getWorldToLocal();

    //设置世界坐标
    void setPosition(const glm::vec3 &val);

    //设置世界欧拉角
    void setEulerAngles(const glm::vec3 &val);

    //设置相对缩放
    void setScale(const glm::vec3 &val);

    //设置相对坐标
    void setLocalPosition(const glm::vec3 &val);

    //设置相对欧拉角
    void setLocalEulerAngles(const glm::vec3 &val);

    void recalculate();


private:
    glm::vec3 position, eulerAngles, scale,localPosition,localEulerAngles,left,up,forward;
    glm::qua<float> rotation,localRotation;
    glm::mat4 localToWorld,worldToLocal;
};
