/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "loading_bar.h"


void LoadingBar::Update(double delta){
    if(max_width==0){
        max_width = parent->GetComponent<Transform>()->scale.x;
    }

    if(resource_loader->GetQueueSize() == 0)
        next_width = max_width;
    else
        next_width = max_width/resource_amount*(resource_amount-resource_loader->GetQueueSize());

    width += (next_width-width)*delta;

    parent->GetComponent<Transform>()->scale.x = width;
}

void LoadingBar::LateUpdate(double delta){
    parent->GetComponent<Transform>()->dirty = true;
    parent->GetComponent<Transform>()->dirty_2d = true;
}
