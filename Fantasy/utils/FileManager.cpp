#include "FileManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Utils.h"

#ifdef __ANDROID__
#include <glfm.h>
static int _fc_android_read(void *cookie, char *buf, int size) {
    return AAsset_read((AAsset *)cookie, buf, (size_t)size);
}

static int _fc_android_write(void *cookie, const char *buf, int size) {
    return -1;
}

static fpos_t _fc_android_seek(void *cookie, fpos_t offset, int whence) {
    return AAsset_seek((AAsset *)cookie, offset, whence);
}

static int _fc_android_close(void *cookie) {
    AAsset_close((AAsset *)cookie);
    return 0;
}

static FILE *_fc_android_fopen(const char *filename, const char *mode) {
    ANativeActivity *activity = glfmAndroidGetActivity();
    AAssetManager *assetManager = NULL;
    AAsset *asset = NULL;
    if (activity) {
        assetManager = activity->assetManager;
    }
    if (assetManager && mode && mode[0] == 'r') {
        asset = AAssetManager_open(assetManager, filename, AASSET_MODE_UNKNOWN);
    }
    if (asset) {
        return funopen(asset, _fc_android_read, _fc_android_write, _fc_android_seek,
                       _fc_android_close);
    } else {
        return fopen(filename, mode);
    }
}
#define fopen _fc_android_fopen
#define BasePath ""
#else
#define BasePath "../assets/"
#endif

namespace FileManager{
    std::string loadText(const std::string &path){
        LOG_I("File", "load file " + path);
        FILE *file;
        file =fopen((BasePath+path).c_str(), "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            long length = ftell(file);
            fseek(file, 0, SEEK_SET);

            char *fstr = new char[length+1];
            fread(fstr, length, 1, file);
            fstr[length] = 0;
            fclose(file);
            string ret(fstr);
            delete[] fstr;
            return ret;
        }
        LOG_E("File","load " + path + " field");
        return "";
    }

    unsigned char *loadImage(const std::string &path,int *width,int *height,int *channel){
        FILE *file=fopen((BasePath+path).c_str(), "rb");
        return stbi_load_from_file(file,width,height,channel,0);
    }

    void freeImage(unsigned char *data){
        stbi_image_free(data);
    }
}