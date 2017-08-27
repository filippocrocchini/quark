/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef CAMERA_H  // NOLINT()
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
 public:
    Camera();
    Camera(const glm::mat4& projection_matrix, const glm::vec3& clear_color);
    void SetupContext();
    const glm::mat4& GetProjectionMatrix() { return projection_matrix; }
 private:
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;
    glm::vec3 clear_color;
};

#endif  // NOLINT() CAMERA_H
