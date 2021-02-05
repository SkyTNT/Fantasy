#include "AssetsManager.h"
#include <utils/Utils.h>
#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "Material.h"


std::map<std::string, Asset *> AssetsManager::assetMap;

void AssetsManager::registerAsset(const std::string &name, Asset *asset) {
    assetMap[name] = asset;
}

Asset *AssetsManager::getAsset(const std::string &name) {
    auto it = assetMap.find(name);
    if (it != assetMap.end()) {
        return it->second;
    }
    LOG_E("AssetsManager", "asset " + name + " can not find");
    return nullptr;
}

void AssetsManager::initAssets() {
    registerAsset("shader/tr", new Shader("tr.vert", "tr.frag"));
    registerAsset("texture/wall", new Texture2D("wall.jpg"));
    registerAsset("texture/face", new Texture2D("face.png"));
    Mesh *cubeMesh = new Mesh();
    glm::vec3 pos[] = {
            {0.5f,  0.5f,  0.0f},
            {0.5f,  -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f},
            {-0.5f, 0.5f,  0.0f}
    };
    glm::vec3 normal[] = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
            {1, 0, 1}
    };
    glm::vec2 uv[] = {
            {1, 0},
            {1, 1},
            {0, 1},
            {0, 0}
    };
    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    cubeMesh->setVerticesCount(4);
    cubeMesh->setPosition(pos);
    cubeMesh->setNormal(normal);
    cubeMesh->setUV(uv);
    cubeMesh->setIndices(6, indices);
    cubeMesh->finish();
    registerAsset("mesh/cube", cubeMesh);
    auto *cubeMaterial = new Material((Shader *) getAsset("shader/tr"));
    cubeMaterial->set("texture0", (Texture2D *) getAsset("texture/wall"));
    cubeMaterial->set("texture1", (Texture2D *) getAsset("texture/face"));
    registerAsset("material/cube", cubeMaterial);
}

void AssetsManager::freeAssets() {
    for (const auto &it:assetMap) {
        delete it.second;
    }
    assetMap.clear();
}
