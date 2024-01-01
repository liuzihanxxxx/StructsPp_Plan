#ifndef STRUCTSPP_PROJECT_LIST_H
#define STRUCTSPP_PROJECT_LIST_H
#include "concept.h"
//fixme to be continued

namespace utils{
    template <typename _Lt>
    class list{
    protected:
        size_t llong = 10;
        size_t lsize = 0;
        _Lt* _list = new _Lt[llong];

        void flash(){}
    public:
        list(){}
        template<size_t size>
        list(_Lt (*l)[size]){

        }
        virtual void operator =(list<_Lt> l){
            this->llong = l.llong;
            this->lsize = l.lsize;
            this->_list = new _Lt[llong];
        }
        virtual void copyin(list<_Lt> l){
            *this = l;
        }

        void copyin(list_style auto *l){

        }

        ~list(){

        }
    };
}

#endif //STRUCTSPP_PROJECT_LIST_H
