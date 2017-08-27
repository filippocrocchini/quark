/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef BUTTON_H  // NOLINT()
#define BUTTON_H

#include <quark.h>

#include <functional>

class Button : public Behaviour {
 public:
    explicit Button(std::function<void(void)> on_click);

    void Update(double delta) override;
    void LateUpdate(double delta) override;
 private:
    std::function<void(void)> on_click;
};

#endif  // NOLINT() BUTTON_H
