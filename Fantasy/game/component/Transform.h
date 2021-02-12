#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

//�任
class Transform : public Component {
public:
    Transform();

    void init() override;

    void tick() override;

    //��ȡ��������
    const glm::vec3 &getPosition();

    //��ȡ����ŷ����
    const glm::vec3 &getEulerAngles();

    //��ȡ�������
    const glm::vec3 &getScale();

    //��ȡ�������
    const glm::vec3 &getLocalPosition();

    //��ȡ���ŷ����
    const glm::vec3 &getLocalEulerAngles();

    //��ȡx��
    const glm::vec3 &getLeft();

    //��ȡy��
    const glm::vec3 &getUp();

    //��ȡz��
    const glm::vec3 &getForward();

    //��ȡ�������任����������ľ���
    const glm::mat4 &getLocalToWorld();

    //��ȡ��������任���������ľ���
    const glm::mat4 &getWorldToLocal();

    //������������
    void setPosition(const glm::vec3 &val);

    //��������ŷ����
    void setEulerAngles(const glm::vec3 &val);

    //�����������
    void setScale(const glm::vec3 &val);

    //�����������
    void setLocalPosition(const glm::vec3 &val);

    //�������ŷ����
    void setLocalEulerAngles(const glm::vec3 &val);

    void recalculate();


private:
    glm::vec3 position, eulerAngles, scale,localPosition,localEulerAngles,left,up,forward;
    glm::qua<float> rotation,localRotation;
    glm::mat4 localToWorld,worldToLocal;
};
