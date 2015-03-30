#ifndef WINDOW_MGR
#define WINDOW_MGR

#include <vector>
#include <string>
#include <iostream>
#include "newscreen.h"

class BitMap;
extern std::ostream& storeOn(std::ostream&, Screen &);
extern BitMap& storeOn(BitMap &, Screen &);

class Window_mgr {
    public:
        using ScreenIndex = std::vector<Screen>::sizetype;

        ScreenIndex addScreen(const Screen&);
        void clear(ScreenIndex);
        void resize(Screen::pos r, Screen::pos c, ScreenIndex i);
    private:
        std::vector<Screen> screens {
            Screen(24, 80, ' ') 
        };
};

inline Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s) {
    screens.push_back(s);
    return screens.size() - 1;
}

inline void Window_mgr::clear(ScreenIndex i) {
    screens[i].height = r;
    screens[i].width = c;
    screens[i].contents = std::string(r * c, ' ');
}

#endif
