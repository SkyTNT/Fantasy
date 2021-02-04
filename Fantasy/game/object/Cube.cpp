#include "Cube.h"
#include "../component/MeshFilter.h"
#include "../asset/AssetsManager.h"

Cube::Cube() {
    auto meshFilter = new MeshFilter(this);
    meshFilter->mesh = (Mesh *) AssetsManager::getAsset("mesh/cube");
    components.push_back(meshFilter);

}

Cube::~Cube() {

}
