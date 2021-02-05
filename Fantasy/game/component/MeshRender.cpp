#include "MeshRender.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "../object/GameObject.h"
#include "../asset/Material.h"
#include "../asset/Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../system/Window.h"

MeshRender::MeshRender(GameObject *gameObject) : Component(gameObject) {
    material= nullptr;
}

void MeshRender::init() {

}

void MeshRender::tick() {
    auto meshFilter =(MeshFilter*) gameObject->getComponent(typeid(MeshFilter));
    if (!meshFilter||!meshFilter->mesh||!material)
        return;
    auto mesh=meshFilter->mesh;
    material->set("projection", glm::perspective(glm::radians(45.0f), Window::width * 1.0f / Window::height, 0.1f, 100.0f));
    material->set("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)));
    material->set("model", gameObject->transform->getMatrix());

    material->use();
    Env::drawObject(mesh->getObject(), mesh->getCount(), Env::DrawType::Triangle, mesh->hasIndices());
}
