#include "Cube.h"
#include "../component/MeshFilter.h"
#include "../component/MeshRender.h"
#include "../asset/AssetsManager.h"

Cube::Cube() {
    auto meshFilter = new MeshFilter();
    meshFilter->mesh = (Mesh *) AssetsManager::getAsset("mesh/cube");
    addComponent(meshFilter);
    auto meshRender = new MeshRender();
    meshRender->material = (Material *) AssetsManager::getAsset("material/cube");
    addComponent(meshRender);
}

Cube::~Cube() {

}
