
#include "Skybox.h"

using antisocial::Skybox;

Skybox::Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left)
    :   _cubeMesh(new Mesh())
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

    std::vector<glm::vec3> skyboxVertices =
    {
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f)
    };

    _cubeMesh->setVertices(skyboxVertices);
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
        std::cerr << "ERROR: could not load image file (" << file << ")" << std::endl;
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
    _cubeMesh->draw();
    glDepthMask(GL_TRUE);
}
