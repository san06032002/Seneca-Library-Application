

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include "Publication.h"

namespace sdds
{
    class Book : public Publication
    {
        char* authName{ nullptr };

    public:
        Book();
        ~Book();
        Book(const Book& book);
        Book& operator=(const Book& book);
        char type() const;
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
        virtual void set(int memberId);
        operator bool() const;
    };
}

#endif // SDDS_BOOK_H