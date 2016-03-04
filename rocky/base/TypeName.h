#ifndef ROCKY_BASE_TYPENAME_H
#define ROCKY_BASE_TYPENAME_H


#include <regex>
#include <boost/type_index.hpp>

#include "rocky/base/TypeListUtility.h"


/**
 * For type displaying.
 */
template <typename T>
struct TD;


namespace Detail
{
    template <typename T>
    std::string getTypeNameOf()
    {
        std::string name = boost::typeindex::type_id_with_cvr<T>().pretty_name();
        auto pos = name.find_last_of(":");
        if (pos != std::string::npos) {
            return name.substr(pos + 1);
        }
        return name;
    }

    template <typename T>
    std::string getTemplateNameOf()
    {
        std::regex expr{ R"(.*?([a-zA-Z0-9_]+)<.*>)" };
        std::string name = boost::typeindex::type_id_with_cvr<T>().pretty_name();
        std::smatch m;
        if (std::regex_match(name, m, expr)) {
            return m[1].str().c_str();
        }
        return "";
    }
} // namespace Detail


template <typename T>
std::string type_name_of{ Detail::getTypeNameOf<T>() };

template <typename T>
std::string type_full_name_of{ boost::typeindex::type_id_with_cvr<T>().pretty_name() };


template <typename T, typename = void>
std::string template_name_of{};

template <typename T>
std::string template_name_of<T, std::enable_if_t<IsTypeListContainer<std::decay_t<T>>::value>> {
        Detail::getTemplateNameOf<std::decay_t<T>>()
};


template <typename T, typename = void>
std::string name_of{ type_name_of<T> };

template <typename T>
std::string name_of<T, std::enable_if_t<IsTypeListContainer<std::decay_t<T>>::value>> { template_name_of<T> };


#endif //ROCKY_BASE_TYPENAME_H

