/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef LEVEL_H  // NOLINT()
#define LEVEL_H

#include <quark.h>

class AsteroidBehaviour : public Behaviour {
 public:
    AsteroidBehaviour();
    void Update(double delta) override;
    void LateUpdate(double delta) override;
 private:
    glm::vec2 direction;
    float velocity = 1.f;
    float ang_velocity = 1.f;
};

extern float difficulty;

extern void loadLevelResources();
extern void initLevel(Scene* scene);

#endif  // NOLINT() LEVEL_H
