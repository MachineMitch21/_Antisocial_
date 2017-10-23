
#include "Skybox.h"

using antisocial::Skybox;



Skybox::Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left)
    :   Drawable(),
        _cubeMesh(ModelLoader::loadObj("../Data/Models/skybox.obj")),
        _textureType(GL_TEXTURE_CUBE_MAP),
        _textureUnit(0)
{
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_skyboxTexture);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture);
    loadSideTexture(CUBE_MAP_FRONT, front);
    loadSideTexture(CUBE_MAP_BACK, back);
    loadSideTexture(CUBE_MAP_RIGHT, right);
    loadSideTexture(CUBE_MAP_LEFT, left);
    loadSideTexture(CUBE_MAP_TOP, top);
    loadSideTexture(CUBE_MAP_BOTTOM, bottom);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

Skybox::Skybox(std::string singleTextureSky)
    :   Drawable(),
        _cubeMesh(ModelLoader::loadObj("../Data/Models/skybox.obj")),
        _textureType(GL_TEXTURE_2D),
        _textureUnit(1)
{
    //Allocates space for texture and stores handle in _handle
    glGenTextures(1, &_skyboxTexture);
    //Sets _handle to current GL texture
    glBindTexture(GL_TEXTURE_2D, _skyboxTexture);

    //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    int width, height, numComponents;

    unsigned char* _data = stbi_load(singleTextureSky.c_str(), &width, &height, &numComponents, 4);

    if (_data == NULL)
    {
        std::cerr << "Texture2D (" << singleTextureSky << ") was not loaded successfully" << std::endl;
        stbi_image_free(_data);
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(_data);
}

Skybox::~Skybox()
{
    delete _cubeMesh;
    glDeleteTextures(1, &_skyboxTexture);
}

bool Skybox::loadSideTexture(GLenum side, std::string file)
{
    int force_channels = 4;
    unsigned char* data;
    int x, y, n;
    data = stbi_load(file.c_str(), &x, &y, &n, force_channels);

    if (data == NULL)
    {
        std::cerr << "ERROR: could not load image file for SKYBOX (" << file << ")" << std::endl;
        return false;
    }

    glTexImage2D(side, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    return true;
}

void Skybox::draw()
{
    glDepthMask(GL_FALSE);
    glActiveTexture(GL_TEXTURE0 + _textureUnit);
    glBindTexture(_textureType, _skyboxTexture);
    if (_cubeMesh)
    {
        _cubeMesh->draw();
    }
    glDepthMask(GL_TRUE);
}
