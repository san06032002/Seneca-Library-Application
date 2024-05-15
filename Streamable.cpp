
#include "Streamable.h"

namespace sdds {

    Streamable::~Streamable() {};

    std::ostream& operator<<(std::ostream& ostr, const Streamable& src) {
        if (src) {
            src.write(ostr);
        }
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Streamable& src) {
        src.read(istr);
        return istr;
    }
}