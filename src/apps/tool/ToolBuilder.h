#pragma once

#include "view/MenuTypes.h"

class AppController;

// -- 类定义 ----------------------------------------------------------------------
class ToolBuilder {
public:
    static MenuPage* buildPage(AppController* sys);
};