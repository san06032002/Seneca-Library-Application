

#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace sdds {
    Publication::Publication()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;

    }

    Publication::Publication(const Publication& publication) 
    {
        *this = publication;
    }

    Publication& Publication::operator=(const Publication& publication)
    {
        set(publication.m_membership);
        setRef(publication.m_libRef);
        strcpy(m_shelfId, publication.m_shelfId);
        m_date = publication.m_date;

        if (m_title)
        {
            delete[] m_title;
        }
        if (publication.m_title != nullptr) 
        {
            m_title = new char[strlen(publication.m_title) + 1];
            strcpy(m_title, publication.m_title);
        }
        else 
        {
            m_title = nullptr;
        }
        return *this;
    }

    Publication::~Publication()
    
    {
        delete[] m_title;
    }
    void Publication::setDefault() 
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        resetDate();
    }

    void Publication::set(int member_id)
    {
        m_membership = member_id;
    }

    void Publication::setRef(int value)
    {
        m_libRef = value;
    }

    void Publication::resetDate()
    {
        m_date = Date();
    }

    char Publication::type() const
    {
        return 'P';
    }

    bool Publication::onLoan() const
    {
        if (m_membership != 0)
        {
            return true;
        }
        return false;
    }

    Date Publication::checkoutDate() const
    {
        return m_date;
    }

    bool Publication::operator==(const char* title) const 
    {
        if (strstr(m_title, title) != nullptr) 
        {
            return true;
        }
        return false;
    }

    Publication::operator const char* () const 
    {
        return m_title;
    }

    int Publication::getRef() const
    {
        return m_libRef;
    }

    bool Publication::conIO(std::ios& io) const
    {
        if (&io == &std::cin || &io == &std::cout) 
        {
            return true;
        }
        return false;
    }

    std::ostream& Publication::write(std::ostream& os) const
    {
        char title[SDDS_TITLE_WIDTH + 1] = { 0 };
        std::strncpy(title, m_title, SDDS_TITLE_WIDTH);

        if (conIO(os)) 
        {
            os << "| " << m_shelfId << " | " << std::setw(30) << std::left << std::setfill('.') << title << " | ";
            (m_membership != 0) ? os << m_membership : os << " N/A ";
            os << " | " << m_date << " |";
        }
        else
        {
            os << type();
            os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
            os << m_membership;
            os << "\t" << m_date;
        }

        return os;
    }

    std::istream& Publication::read(std::istream& is) 
    {
        char title[256]{}, shelfId[SDDS_SHELF_ID_LEN + 1]{};
        int libraryReference = -1, membership = 0;
        Date date;

        if (m_title) 
        {
            delete[] m_title;
            m_title = nullptr;
        }
        setDefault();

        if (conIO(is))
        {
            std::cout << "Shelf No: ";
            is.getline(shelfId, SDDS_SHELF_ID_LEN + 1);

            if (strlen(shelfId) != SDDS_SHELF_ID_LEN) 
            {
                is.setstate(std::ios::failbit);
            }

            std::cout << "Title: ";
            is.getline(title, 256);

            std::cout << "Date: ";
            is >> date;
        }

        else
        {
            is >> libraryReference;
            is.ignore();
            is.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            is.getline(title, 256, '\t');
            is >> membership;
            is.ignore();
            is >> date;
        }

        if (!date)
        {
            is.setstate(std::ios::failbit);
        }

        if (is) 
        {
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
            strcpy(m_shelfId, shelfId);
            m_membership = membership;
            m_date = date;
            m_libRef = libraryReference;
        }
        return is;
    }

    Publication::operator bool() const 
    {
        if (m_title != nullptr && m_shelfId[0] != '\0') 
        {
            return true;
        }
        return false;

    }
}