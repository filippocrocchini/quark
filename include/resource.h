/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef RESOURCE_H
#define RESOURCE_H

class Resource {
public:
    virtual bool Load() = 0;
    virtual void onLoad() = 0;
    virtual void onFail() = 0;
    virtual ~Resource() = default;
};

#endif  // RESOURCE_H
