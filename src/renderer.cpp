/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "renderer.h"

#include <GL/glew.h>

void Renderer::drawRectangleMesh(RectangleMesh* mesh){
    glLoadIdentity();

    glColor3f(mesh->r, mesh->g, mesh->b);
    glBegin(GL_QUADS);
    glVertex2d(mesh->x, mesh->y);
    glVertex2d(mesh->x+mesh->width, mesh->y);
    glVertex2d(mesh->x+mesh->width, mesh->y+mesh->height);
    glVertex2d(mesh->x, mesh->y+mesh->height);
    glEnd();
}
