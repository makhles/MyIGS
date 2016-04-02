// DeleteList.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
//
// This class should be used for deleting pointers in a std::list.
// Usage:
//
// std::for_each (my_class_list.begin(),
//                my_class_list.end(),
//                DeleteList<my_class*>());

#ifndef DELETE_LIST_HPP
#define DELETE_LIST_HPP

template <class T>
class DeleteList {
  public:
    bool operator()(T x) const {
        delete x;
        return true;
    }
};

#endif  // DELETE_LIST_HPP