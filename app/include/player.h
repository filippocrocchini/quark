/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef PLAYER_H  // NOLINT()
#define PLAYER_H

#include <quark.h>

class PlayerBehaviour : public Behaviour {
 public:
    PlayerBehaviour(float speed, float rot_speed);
    void Update(double delta) override;
    void LateUpdate(double delta) override;
 private:
    float speed, rot_speed;
};

extern void loadPlayerResources();
extern void initPlayer(Scene* scene);

#endif  // NOLINT() PLAYER_H
