/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef LOADING_BAR_H
#define LOADING_BAR_H

#include "quark.h"

class LoadingBar : public Behaviour {
public:
    LoadingBar(ResourceLoader* resource_loader, int resource_amount) : resource_loader(resource_loader) , resource_amount(resource_amount){}
    virtual void Update(double delta) override;
    virtual void LateUpdate(double delta) override;
private:
    ResourceLoader* resource_loader;
    int resource_amount;
    double width = 0, max_width = 0, next_width = 0;
};
#endif //  LOADING_BAR_H
