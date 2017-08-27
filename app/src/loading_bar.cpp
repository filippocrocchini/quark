/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./loading_bar.h"

void LoadingBar::Update(double delta) {
    if (max_width == 0) {
        max_width = parent->GetComponent<Transform>()->scale.x;
    }
    int queue_size = Quark::resource_loader.GetQueueSize();
    int resource_count = Quark::resource_loader.GetResourceCount();
    if (resource_count == 0) {
        width = max_width;
    } else {
        if (queue_size == 0)
            next_width = max_width;
        else
            next_width = max_width/resource_count*(resource_count-queue_size);
        width += (next_width-width)*delta;
    }
    parent->GetComponent<Transform>()->scale.x = width;
}

void LoadingBar::LateUpdate(double delta) {
    parent->GetComponent<Transform>()->dirty = true;
    parent->GetComponent<Transform>()->dirty_2d = true;
}
