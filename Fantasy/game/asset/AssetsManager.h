#pragma once
#include <string>
#include <map>
#include "Asset.h"

class AssetsManager {
public:
    //加载初始资源
    static void initAssets();
    //释放所有资源
    static void freeAssets();
    //注册资源
    static void registerAsset(const std::string &name,Asset* asset);
    //获取资源
    static Asset* getAsset(const std::string &name);
private:
    static std::map<std::string,Asset*> assetMap;
};

