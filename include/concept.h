//fixme: Temporarily "unfinished", to be continued
#ifndef STRUCTSPP_PROJECT_CONCEPT_H
#define STRUCTSPP_PROJECT_CONCEPT_H

namespace utils{
    template <class, class>
    constexpr bool is_same = false;
    template <class Ty>
    constexpr bool is_same<Ty, Ty> = true;
    template <typename ty1, typename ty2>
    concept absolute_type = is_same<ty1, ty2> && is_same<ty2, ty1>;

    template <class type>
    concept list_style = requires(type* t){
        {t[0]}->absolute_type<type>;
    };

    template <class type>
    concept pointer_style = requires(type* t){
        {*t}->absolute_type<type>;
    };
}

#endif //STRUCTSPP_PROJECT_CONCEPT_H
