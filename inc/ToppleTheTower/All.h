#pragma once

#include "Actor.h"
#include "Collision.h"
#include "Object.h"
#include "Director.h"

namespace Singleton
{
    Director& _d()
    {
        return Director::getInstance();
    }
}