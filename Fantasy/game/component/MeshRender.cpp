#include "MeshRender.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "../object/GameObject.h"
#include "../asset/Material.h"
#include "../asset/Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Utils.h>

MeshRender::MeshRender() : Component() {
    material = nullptr;
}

void MeshRender::init() {
    LOG_I("AAA","init");
}

void MeshRender::tick() {
    auto meshFilter = (MeshFilter *) gameObject->getComponent(typeid(MeshFilter));

    if (!meshFilter || !meshFilter->mesh || !material)
        return;
    auto mesh = meshFilter->mesh;
    Env::setModel(gameObject->transform->getMatrix());
    material->use();
            Env::drawObject(mesh->getObject(), mesh->getCount(), Env::DrawType::Triangle, mesh->hasIndices());
}
