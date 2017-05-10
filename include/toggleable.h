/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef TOGGLEABLE_H
#define TOGGLEABLE_H

class Toggleable {
public:
    Toggleable() : enabled(true) {}
    Toggleable(bool enabled) : enabled(enabled){}

    virtual bool isEnabled(){
        return enabled;
    }

    virtual void Enable(){
        enabled = true;
    }

    virtual void Disable(){
        enabled = false;
    }

    virtual void Toggle(){
        enabled = !enabled;
    }

protected:
    bool enabled;
};

#endif  // TOGGLEABLE_H
