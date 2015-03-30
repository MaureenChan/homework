#include <string>
#include <iostream>

class Screen {
    public :
        // friend
        friend class Window_mgr;
        typedef std::string::sizetype pos;
        // constructors
        Screen() = default;
        Screen(pos ht, pos wd, char c) :
            height(ht), width(wd), contents(ht * wd, c) {}
        Screen(pos ht = 0, pos wd = 0) :
            cursor(0), height(ht), width(wd), contents(ht * wd, ' ') {}

        // get()
        char get() const {
            return contents[cursor];
        }

        inline char get(pos ht, pos wd) const;
        
        // clear()
        Screen &clear(char = bkground);

        // move()
        Screen &move(pos r, pos c);
        // set()
        Screen &set(char);
        Screen &set(pos, pos, char);

        // display()
        Screen &display(std::ostream &os) const {
            do_display(os);
            return *this;
        }

        const Screen &display(std::ostream &os) const {
            do_display(os);
            return *this;
        }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
        static const char bkground = ' ';
        // do_display()
        void do_display(std::ostream &os) const {
            os << contents;
        }

};
