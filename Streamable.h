

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include <iostream>

namespace sdds {
    class Streamable {
    public:
        virtual std::ostream& write(std::ostream& ostr) const = 0;
        virtual std::istream& read(std::istream& istr) = 0;
        virtual bool conIO(std::ios& ios) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable();
    };
    std::ostream& operator<<(std::ostream& ostr, const Streamable& src);
    std::istream& operator>>(std::istream& istr, Streamable& src);
}

#endif //SDDS_STREAMABLE_H
