/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef LOADING_BAR_H  // NOLINT()
#define LOADING_BAR_H

#include <quark.h>

class LoadingBar : public Behaviour {
 public:
    LoadingBar() {}
    void Update(double delta) override;
    void LateUpdate(double delta) override;
 private:
    double width = 0, max_width = 0, next_width = 0;
};
#endif  // NOLINT() LOADING_BAR_H
