
Final Project Milestone 5


#define _CRT_SECURE_NO_WARNINGS
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

namespace sdds {
    LibApp::LibApp(const char* filename): m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), publicationType("Choose the type of publication:") {
        
        if (filename)
        {
            strcpy(m_filename, filename);
        }
        m_changed = false;
        NOLP = 0;
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        publicationType << "Book" << "Publication";

        load();
    }

    LibApp::~LibApp() 
    {
        
        for (int i = 0; i < NOLP; i++)
        {

            delete PPA[i];
        
        }
    }
    
    Publication* LibApp::getPub(int libRef) 
    {

        Publication* result = nullptr;

        int i = 0;

        while (i < NOLP)
        {
            if (PPA[i]->getRef() == libRef)
            {

                result = PPA[i];

            }

            i++;
        }

        

        return result;

    }

    bool LibApp::confirm(const char* message) 
    {
        bool outcome = false;
        Menu menu(message);
        menu << "Yes";

        int returnedValue = menu.run();

        if (returnedValue == 1) {
            outcome = true;
        }

        return outcome;
    }

    void LibApp::load() 
    
    {
        std::cout << "Loading Data" << std::endl;
        std::ifstream infile(m_filename);

        char type{};
        int i = 0;

        while (infile && i < SDDS_LIBRARY_CAPACITY)
        {
            infile >> type;
            infile.ignore();
            if (infile) {
                if (type == 'P')
                    PPA[i] = new Publication;

                else if (type == 'B')
                    PPA[i] = new Book;

                if (PPA[i]) {

                    infile >> *PPA[i];
                    NOLP++;
                    LLRN = PPA[i]->getRef();
                }
            }

            i++;
        }

        
    };

    void LibApp::save() 
    {
        std::cout << "Saving Data" << std::endl;
        std::ofstream outfile(m_filename);
        int i = 0;

        while (i < NOLP)
        {

            if (PPA[i]->getRef() != 0)
            {
                outfile << *PPA[i] << std::endl;
            }
            i++;
        }
       

        outfile.close();
    }

    int LibApp::search(int searchType) {

        char title[256]{};
        int selectType = 0, i = 0, libraryReference = 0;
        char charType;
        PublicationSelector pubSel("Select one of the following found matches:", 15);

        selectType = publicationType.run();
        if (selectType == 1) {
            charType = 'B';
        }
        else if (selectType == 2) {
            charType = 'P';
        }

        std::cin.ignore(1000, '\n');
        std::cout << "Publication Title: ";
        std::cin.getline(title, 256);

        switch (searchType)
        {

        case 1: {

            for (i = 0; i < NOLP; i++) {
                if (PPA[i]->operator==(title) && charType == PPA[i]->type() && PPA[i]->getRef() != 0) {
                    pubSel << PPA[i];
                }
            }
            break;
        }
        case 2: {

            for (i = 0; i < NOLP; i++) {
                if (PPA[i]->operator==(title) && PPA[i]->onLoan() && charType == PPA[i]->type() && PPA[i]->getRef() != 0) {
                    pubSel << PPA[i];
                }
            }
            break;
        }
        case 3: {

            for (i = 0; i < NOLP; i++) {
                if (PPA[i]->operator==(title) && !PPA[i]->onLoan() && charType == PPA[i]->type() && PPA[i]->getRef() != 0) {
                    pubSel << PPA[i];
                }
            }
            break;
        }

        }

        

        if (pubSel) {
            pubSel.sort();
            libraryReference = pubSel.run();

            if (libraryReference > 0)
            {
                std::cout << *getPub(libraryReference) << std::endl;
            }
            else {
                std::cout << "Aborted!" << std::endl;
            }
        }
        else {
            std::cout << "No matches found!" << std::endl;
        }

        return libraryReference;
    }

    void LibApp::returnPub() {
        bool abort = false;
        std::cout << "Return publication to the library" << std::endl;
        int libraryReference = search(2); 
        if (!(libraryReference > 0)) {
            abort = true;
        }

        if (!abort) 
        {
            bool _confirm = confirm("Return Publication?");

            if (_confirm) {
                int loanDays = Date() - getPub(libraryReference)->checkoutDate();
                if (loanDays > SDDS_MAX_LOAN_DAYS) {
                    double penal = (loanDays - SDDS_MAX_LOAN_DAYS) * 0.5;
                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "Please pay $" << penal << " penalty for being " << (loanDays - SDDS_MAX_LOAN_DAYS) << " days late!" << std::endl;
                }
                getPub(libraryReference)->set(0);
                m_changed = true;
            }
            std::cout << "Publication returned" << std::endl;
        }
        std::cout << std::endl;
    }

    void LibApp::newPublication() 
    {
        bool abort = false;

        if (NOLP == SDDS_LIBRARY_CAPACITY)
        {
            std::cout << "Library is at its maximum capacity!" << std::endl;
            abort = true;
        }

        if (!abort) {
            std::cout << "Adding new publication to the library" << std::endl;
            int publType = publicationType.run();
            std::cin.ignore(1000, '\n');

            Publication* publication = nullptr;

            switch (publType)
            {

            case 0: {

                std::cout << "Aborted!" << std::endl;
                abort = true;

                break;
            }
            case 1: {

                publication = new Book;
                std::cin >> *publication;

                break;
            }
            case 2: {

                publication = new Publication;
                std::cin >> *publication;

                break;
            }
            }
            
            if (std::cin.fail())
            {
                std::cin.ignore(1000, '\n');
                std::cin.clear();
                std::cout << "Aborted!" << std::endl;
                exit(0);
            }
            else
            {
                if (!abort && confirm("Add this publication to the library?"))
                {
                    if (!*publication) 
                    {
                        std::cout << "Failed to add publication!" << std::endl;
                        delete publication;
                    }

                    else {
                        LLRN++;
                        publication->setRef(LLRN);
                        PPA[NOLP] = publication;
                        NOLP++;
                        m_changed = true;
                        std::cout << "Publication added" << std::endl;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void LibApp::removePublication() 
    {
        std::cout << "Removing publication from the library" << std::endl;
        int libraryReference = search(1); 
        if (libraryReference) 
        {
            if (confirm("Remove this publication from the library?"))
            {
                getPub(libraryReference)->setRef(0);
                m_changed = true;
                std::cout << "Publication removed" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void LibApp::checkOutPub()
    {
        std::cout << "Checkout publication from the library" << std::endl;
        int libraryReference = search(3); 
        if (libraryReference > 0) 
        {
            bool _confirm = confirm("Check out publication?");
            if (_confirm)
            {
                std::cout << "Enter Membership number: ";
                int inputMembership = getIntegerInput(10000, 99999, "Invalid membership number, try again: ");
                getPub(libraryReference)->set(inputMembership);
                m_changed = true;
                std::cout << "Publication checked out"<< std::endl;
            }
        }
        std::cout << std::endl;
    }
    
    void LibApp::run() {
        int userInMe, userInEx;




        do {


            userInMe = m_mainMenu.run();


            if (userInMe == 0)
            {
                if (m_changed == true) {
                    userInEx = m_exitMenu.run();

                    if (userInEx == 0)
                    {
                        if (confirm("This will discard all the changes are you sure?")) {
                            m_changed = false;
                        }
                    }
                    else if (userInEx == 1)
                    {
                        save();
                    }
                    else if (userInEx == 2)
                    {
                        userInMe = 1;
                    }
                   
                }
                std::cout << std::endl;
            }
            else if (userInMe == 1)
            {
                newPublication();
            }
            else if (userInMe == 2)
            {
                removePublication();
            }
            else if (userInMe == 3)
            {
                checkOutPub();
            }
            else if (userInMe == 4)
            {
                returnPub();
            }

            
        }
        while (userInMe != 0); 
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Thanks for using Seneca Library Application" << std::endl;
    }
}