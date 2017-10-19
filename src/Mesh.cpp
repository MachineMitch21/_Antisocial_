
#include "Mesh.h"

using antisocial::Mesh;

Mesh::Mesh()
    :   Drawable()
{
    glGenVertexArrays(1, &_vao);
    init_vbo_map();
    glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& uvs)
    :   Drawable()
{
    glGenVertexArrays(1, &_vao);
    init_vbo_map();
    setVertices(vertices);
    setNormals(normals);
    setUVs(uvs);
}

void Mesh::draw()
{
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

void Mesh::setVertices(const std::vector<glm::vec3>& newVertices)
{
    _vertices = newVertices;

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbos.at(VERTICES));
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(VERTICES);
    glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Mesh::setNormals(const std::vector<glm::vec3>& newNormals)
{
    _normals = newNormals;

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbos.at(NORMALS));
    glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMALS);
    glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Mesh::setUVs(const std::vector<glm::vec2>& newUVs)
{
    _uvs = newUVs;

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbos.at(UVS));
    glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(UVS);
    glVertexAttribPointer(UVS, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}


void Mesh::init_vbo_map()
{
    GLuint vbos[NUM_VBOS];
    glGenBuffers(NUM_VBOS, vbos);

    for (int i = 0; i < NUM_VBOS; i++)
    {
        _vbos.emplace(i, vbos[i]);
    }
}

Mesh::~Mesh()
{
    for (std::map<unsigned int, GLuint>::iterator it = _vbos.begin(); it != _vbos.end(); ++it)
    {
        glDeleteBuffers(1, &it->second);
    }
    glDeleteVertexArrays(1, &_vao);
}