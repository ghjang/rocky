#ifndef ROCKY_BASE_TYPENAME_H
#define ROCKY_BASE_TYPENAME_H


#include <boost/type_index.hpp>


/**
 * For type displaying.
 */
template <typename T>
struct TD;


namespace Detail
{
    template <typename T>
    auto getTypeNameOf()
    {
        std::string name = boost::typeindex::type_id_with_cvr<T>().pretty_name();
        auto pos = name.find_last_of(":");
        if (pos != std::string::npos) {
            return name.substr(pos + 1);
        }
        return name;
    }
} // namespace Detail


template <typename T>
std::string type_name_of{ Detail::getTypeNameOf<T>() };

template <typename T>
std::string type_full_name_of{ boost::typeindex::type_id_with_cvr<T>().pretty_name() };


#endif //ROCKY_BASE_TYPENAME_H

