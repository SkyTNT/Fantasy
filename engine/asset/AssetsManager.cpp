#include "AssetsManager.h"
#include <utils/Utils.h>
#include <asset/Asset.h>
#include <asset/Shader.h>
#include <asset/Texture2D.h>
#include <asset/Mesh.h>
#include <asset/Material.h>


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
            {-0.5f, -0.5f, -0.5f},//下
            {0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f, 0.5f},
            {0.5f, -0.5f, 0.5f},

            {-0.5f, 0.5f, -0.5f},//上
            {0.5f, 0.5f, -0.5f},
            {-0.5f, 0.5f, 0.5f},
            {0.5f, 0.5f, 0.5f},

            {-0.5f, -0.5f, -0.5f},//前
            {0.5f, -0.5f, -0.5f},
            {-0.5f, 0.5f, -0.5f},
            {0.5f, 0.5f, -0.5f},

            {-0.5f, -0.5f, 0.5f},//后
            {0.5f, -0.5f, 0.5f},
            {-0.5f, 0.5f, 0.5f},
            {0.5f, 0.5f, 0.5f},

            {-0.5f, -0.5f, -0.5f},//右
            {-0.5f, -0.5f, 0.5f},
            {-0.5f, 0.5f, -0.5f},
            {-0.5f, 0.5f, 0.5f},

            {0.5f, -0.5f, -0.5f},//左
            {0.5f, -0.5f, 0.5f},
            {0.5f, 0.5f, -0.5f},
            {0.5f, 0.5f, 0.5f},
    };
    glm::vec3 normal[] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},

            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},

            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},

            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},

            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},

            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
    };

    glm::vec2 uv[] = {
            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1},

            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1},

            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1},

            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1},

            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1},

            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1}

    };
    unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2,

            4, 5, 6,
            5, 7, 6,

            8, 9, 10,
            9, 11, 10,

            12, 13, 14,
            13, 15, 14,

            16, 17, 18,
            17, 19, 18,

            20, 21, 22,
            21, 23, 22
    };
    cubeMesh->setVerticesCount(24);
    cubeMesh->setPosition(pos);
    cubeMesh->setNormal(normal);
    cubeMesh->setUV(uv);
    cubeMesh->setIndices(36, indices);
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
