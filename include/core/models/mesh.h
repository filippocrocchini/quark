#pragma once

class Mesh {
public:
    Mesh() = default;
    ~Mesh() = default;

    const GLuint& getVertexBuffer() const { return vertexBufferId; }
    const GLuint& getIndexBuffer() const { return indexBufferId; }
    const GLuint& getTextureCoordinateBuffer() const { return textureCoordBufferId; }

private:
    GLuint vertexBufferId;
    GLuint indexBufferId;
    GLuint textureCoordBufferId;
};