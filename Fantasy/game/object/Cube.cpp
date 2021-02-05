#include "Cube.h"
#include "../component/MeshFilter.h"
#include "../component/MeshRender.h"
#include "../asset/AssetsManager.h"

Cube::Cube() {
    auto meshFilter = new MeshFilter(this);
    meshFilter->mesh = (Mesh *) AssetsManager::getAsset("mesh/cube");
    components.push_back(meshFilter);
    auto meshRender = new MeshRender(this);
    meshRender->material= (Material *) AssetsManager::getAsset("material/cube");
    components.push_back(meshRender);
}

Cube::~Cube() {

}
