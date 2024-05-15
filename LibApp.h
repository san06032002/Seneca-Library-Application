

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include <iostream>
#include "Menu.h"
#include "Lib.h"
#include "Streamable.h"
#include "Publication.h"
#include "Book.h"

namespace sdds {
    class LibApp {
    private:
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        char m_filename[SDDS_MAX_FILENAME + 1];
        Publication* PPA[SDDS_LIBRARY_CAPACITY]; 
        int NOLP; 
        int LLRN; 
        Menu publicationType;       
        bool confirm(const char* message);
        void load();
        void save();
        int search(int searchType);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();

    public:
        LibApp(const char* fileName);
        ~LibApp();     
        void run();
        
        Publication* getPub(int libRef);

    };
}

#endif