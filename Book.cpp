

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Book.h"

namespace sdds
{
    Book::Book() : Publication()
    {
        authName = nullptr;
    }
    Book::~Book()
    {
        if (authName)
        {
            delete[] authName;
            authName = nullptr;
        }
    }

    Book::Book(const Book& book) : Publication(book)
    {
        *this = book;
    }

    Book& Book::operator=(const Book& book)
    {
        Publication::operator=(book);

        if (this != &book)
        {

            if (authName)
            {
                delete[] authName;
                authName = nullptr;
            }

            if (book.authName)
            {
                authName = new char[strlen(book.authName) + 1];
                strcpy(authName, book.authName);
            }

        }
        return *this;
    }

    char Book::type() const
    {

        return 'B';
    
    }

    std::ostream& Book::write(std::ostream& ostr)const
    {
        Publication::write(ostr);

        if (conIO(ostr))
        {
            char name[SDDS_AUTHOR_WIDTH + 1]{ 0 };

            strncpy(name, authName, SDDS_AUTHOR_WIDTH);

            ostr << " ";
            ostr.width(SDDS_AUTHOR_WIDTH);
            ostr << std::left;
            ostr.fill(' ');
            ostr << name;
            ostr << " |";
        }
        else
        {
            ostr << '\t';
            ostr << authName;
        }
        return ostr;
    }


    std::istream& Book::read(std::istream& istr)
    {
        char authorName[256] = { 0 };

        Publication::read(istr);

        if (authName)
        {

            delete[] authName;
            authName = nullptr;
        
        }

        if (conIO(istr))
        {

            istr.ignore();

            std::cout << "Author: ";
        
        }
        else
        {

            
            istr.ignore(1, '\t');
        
        
        }

        istr.get(authorName, 255);

        if (!istr.fail())
        {

            authName = new char[strlen(authorName) + 1];
            strcpy(authName, authorName);
        
        }

        return istr;
    }

    void Book::set(int memberId)
    {

        Publication::set(memberId);

        Publication::resetDate();
    
    }

    Book::operator bool() const
    {

        bool outcome = false;

        if (authName)
        {

            if (Publication::operator bool())
            {

                outcome = true;
            
            }

        }
        return outcome;

    }

}