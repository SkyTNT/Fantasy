#include "MeshRender.h"
#include "MeshFilter.h"
#include "../object/GameObject.h"
#include "../asset/Material.h"
#include "../asset/Mesh.h"
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

    material->use();
    Env::drawObject(mesh->getObject(), mesh->getCount(), Env::DrawType::Triangle, mesh->hasIndices());
}
