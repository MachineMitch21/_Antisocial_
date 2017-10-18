#ifndef MESH_H
#define MESH_H

#include "AntisocialDLL.h"
#include "Drawable.h"
#include <GL/glew.h>
#include <vector>

using antisocial::Drawable;

namespace antisocial
{
    class
    #ifdef __WIN32__
    ANTISOCIAL_API
    #endif // __WIN32__
    Mesh : public Drawable
    {
    public:
        Mesh(std::vector<float> vertices);
        ~Mesh();

        void draw() override;

    private:
        std::vector<float>  _vertices;
        GLuint              _vao;
        GLuint              _vbo;
    };
}

#endif // MESH_H
