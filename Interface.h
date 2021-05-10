#include <cstdlib>

using ValueType = int;

class IList {
public:
    virtual ValueType& at(size_t idx) = 0;
    virtual const ValueType& at(size_t idx) const = 0;
    virtual ValueType& operator[](size_t idx) = 0;
    virtual const ValueType& operator[](size_t idx) const = 0;

    virtual void pushBack(const ValueType& value) = 0;
    virtual void pushFront(const ValueType& value) = 0;
    virtual void insert(size_t pos, const ValueType& value) = 0;

    virtual void popBack() = 0;
    virtual void popFront() = 0;
    virtual void erase(size_t pos) = 0;

    virtual void reverse() = 0;

    virtual void clear() = 0;
    virtual size_t size() const = 0;
};
