/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./components.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/quaternion.hpp>

const glm::mat4& Transform::GetMatrix() {
    if (dirty) {
        glm::mat4 t_matrix = glm::translate(glm::mat4(1), position);
        glm::mat4 p_matrix = glm::translate(glm::mat4(1), pivot);
        glm::mat4 s_matrix = glm::scale(glm::mat4(1), scale);
        glm::mat4 r_matrix = glm::mat4_cast(rotation);
        matrix = t_matrix * r_matrix * p_matrix * s_matrix;
        dirty = false;
    }
    return matrix;
}

const glm::mat3& Transform::GetMatrix2D() {
    if (dirty_2d) {
        glm::mat3 t_matrix = glm::translate(glm::mat3(1), glm::vec2(position));
        glm::mat3 p_matrix = glm::translate(glm::mat3(1), glm::vec2(pivot));
        glm::mat3 s_matrix = glm::scale(glm::mat3(1), glm::vec2(scale));
        glm::mat3 r_matrix = glm::rotate(glm::mat3(1), glm::eulerAngles(rotation).z);
        matrix_2d = t_matrix * r_matrix * p_matrix * s_matrix;
        matrix_2d[2][2] = 0;
        dirty_2d = false;
    }
    return matrix_2d;
}

glm::vec2 Transform::ApplyTo(const glm::vec2& vector) {
    return glm::vec2(GetMatrix2D() * glm::vec3(vector, 0));
}
