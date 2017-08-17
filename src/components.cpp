/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "components.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

const glm::mat4& Transform::GetMatrix(){
    if(dirty){
        glm::mat4 t_matrix = glm::translate(glm::mat4(1), position);
        glm::mat4 p_matrix = glm::translate(glm::mat4(1), pivot);
        glm::mat4 s_matrix = glm::scale(glm::mat4(1), scale);
        glm::mat4 r_matrix = glm::mat4_cast(rotation);
        matrix = t_matrix * r_matrix * p_matrix * s_matrix;
        dirty = false;
    }
    return matrix;
}
