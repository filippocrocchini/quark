/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef TOGGLEABLE_H  // NOLINT()
#define TOGGLEABLE_H

class Toggleable {
 public:
    explicit Toggleable(bool enabled) : enabled(enabled) {}
    Toggleable() : enabled(true) {}

    virtual bool isEnabled() {
        return enabled;
    }

    virtual void Enable() {
        enabled = true;
    }

    virtual void Disable() {
        enabled = false;
    }

    virtual void Toggle() {
        enabled = !enabled;
    }

 protected:
    bool enabled;
};

#endif  // NOLINT() TOGGLEABLE_H
