#pragma once

#include "view/MenuTypes.h"

class AppController;

// -- 类定义 ----------------------------------------------------------------------
class SettingsBuilder {
public:
    static MenuPage* buildPage(AppController* sys);

private:
    static void buildLanguagePage(AppController* sys, MenuPage* parent);
    static void buildCursorPage(AppController* sys, MenuPage* parent);
    static void buildSleepPage(AppController* sys, MenuPage* parent);
};