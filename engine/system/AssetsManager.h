#pragma once

#include <string>
#include <map>

class Asset;
//��Դ������
class AssetsManager {
public:
    //���س�ʼ��Դ
    static void initAssets();

    //�ͷ�������Դ
    static void freeAssets();

    //ע����Դ
    static void registerAsset(const std::string &name, Asset *asset);

    //��ȡ��Դ
    static Asset *getAsset(const std::string &name);

private:
    static std::map<std::string, Asset *> assetMap;
};
