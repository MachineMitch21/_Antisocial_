
#include "Sprite.h"

using antisocial::graphics::Sprite;

Sprite::Sprite(const Vector2f& pos, float width, float height)
    :   _position(pos),
        _width(width),
        _height(height)
{
    init_();
}

Sprite::Sprite(float x, float y, float width, float height)
    :   _position(Vector2f(x, y)),
        _width(width),
        _height(height)
{
    init_();
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &_vbo);
}

void Sprite::init_()
{
    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);

    setData_();
}

void Sprite::setData_()
{
    float vertices[] =
    {
        _position.x + _width,   _position.y + _height,
        _position.x,            _position.y + _height,
        _position.x,            _position.y,
        _position.x,            _position.y,
        _position.x + _width,   _position.y,
        _position.x + _width,   _position.y + _height
    };

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Sprite::draw()
{
    glDepthFunc(GL_ALWAYS);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDepthFunc(GL_LEQUAL);
}

void Sprite::setPosition(const Vector2f& pos)
{
    _position = pos;

    setData_();
}

void Sprite::setWidth(float width)
{
    _width = width;

    setData_();
}

void Sprite::setHeight(float height)
{
    _height = height;

    setData_();
}
