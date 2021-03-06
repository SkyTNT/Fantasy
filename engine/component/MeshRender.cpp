#include "MeshRender.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "../object/GameObject.h"
#include "../asset/Material.h"
#include "../asset/Mesh.h"

MeshRender::MeshRender() : Component() {

}

void MeshRender::init() {
}

void MeshRender::tick() {
    auto meshFilter = (MeshFilter *) gameObject->getComponent(typeid(MeshFilter));

    if (!meshFilter || !meshFilter->mesh || !material)
        return;
    auto mesh = meshFilter->mesh;
    Env::setModel(gameObject->transform->getLocalToWorld());
    material->use();
    Env::drawObject(mesh->getObject(), mesh->getCount(), Env::DrawType::Triangle, mesh->hasIndices());
}
