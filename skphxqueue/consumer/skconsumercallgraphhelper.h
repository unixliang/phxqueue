#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <memory>

namespace skphxqueue {

namespace consumer {

class SKConsumerCallGraphHelper
{
public:
    SKConsumerCallGraphHelper();
    virtual ~SKConsumerCallGraphHelper();

    static SKConsumerCallGraphHelper *GetInstance();

    void Init(const int consumer_ossid);
    void FixGraph();

private:
    int consumer_ossid_{0};
};

}
}
