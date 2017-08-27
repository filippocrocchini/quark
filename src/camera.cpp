/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./camera.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::mat4& projection_matrix, const glm::vec3& clear_color):
     projection_matrix(projection_matrix), clear_color(clear_color) {}

Camera::Camera(): Camera(glm::ortho(0.f, 1.f, 0.f, 1.f, -100.f, 100.f), glm::vec3(0)) {}

void Camera::SetupContext() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(clear_color.r, clear_color.g, clear_color.b, 1);
}
