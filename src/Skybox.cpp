
#include "Skybox.h"

using antisocial::Skybox;

Skybox::Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left)
    :   Drawable(),
        _cubeMesh(ModelLoader::loadObj("../Data/Models/cube.obj"))
{
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_cubeMapHandle);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapHandle);
    loadSideTexture(CUBE_MAP_FRONT, front);
    loadSideTexture(CUBE_MAP_BACK, back);
    loadSideTexture(CUBE_MAP_RIGHT, right);
    loadSideTexture(CUBE_MAP_LEFT, left);
    loadSideTexture(CUBE_MAP_TOP, top);
    loadSideTexture(CUBE_MAP_BOTTOM, bottom);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    _skyboxVertices =
    {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f
    };

    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _skyboxVertices.size() * sizeof(float), &_skyboxVertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
}

Skybox::~Skybox()
{
    delete _cubeMesh;
    glDeleteTextures(1, &_cubeMapHandle);
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapHandle);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // if (_cubeMesh)
    // {
    //     _cubeMesh->draw();
    // }
    glDepthMask(GL_TRUE);
}
