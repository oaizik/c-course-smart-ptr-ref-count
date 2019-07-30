#pragma once
#include <exception>
class nullPtrExcep : public _exception {};
//template<class T>
/*class SmartPtr{
private:
    T* pointee;
public:
    SmartPtr(T* realPtr = 0) :pointee(realPtr) {}
    ~SmartPtr() {
        if(pointee)
            delete pointee;
    }
    SmartPtr(SmartPtr<T>& rhs) {//copy
        pointee = rhs.pointee;
        rhs.pointee = 0;
    }
    SmartPtr<T>& operator=(const SmartPtr<T>& rhs) {//op=
        if (this == rhs & )
            return this*;

        delete pointee;

        pointee = rhs.pointee;
        rhs.pointee = 0;
        return *this;
    }
    T* operator->() const {
        if (pointee)
            return pointee;
        else
            throw nullPtrExcep;
    }
    T& operator*() const {
        if (pointee)
            return *pointee;
        else
            throw nullPtrExcep;
    }
    bool operator!() const { pointee ? return false : return true; }//if pointee is null return true
    operator T*() { return pointee; }//problem
    //in case of inheritance must provide convertion operator.
};
template<class V>
class countRef{
private:
    struct countedVal {
        int count;
        V* data;
        countedVal(const V* initValue) :count(1){
            data = new V(initValue);
        }
        ~countedVal() {
            delete data;
        }
    };
    countedVal * Value;
public:
    countRef(const V* initValue = 0 ):Value(new countedVal(initValue)) {}
    countRef(const countRef& rhs) :Value(rhs.Value) {
        ++Value->count;
    }
    countRef& operator=(const countRef& rhs) {
        if (Value == rhs.Value)
            return *this;

        if (--Value->count == 0)
            delete Value;

        Value = rhs.Value;
        ++Value->Count;
        return *this;
    }
    ~countRef() {
        if (--Value->count == 0)
            delete Value;
    }
};*/
class RCObject {
public:
    RCObject() : refCount(0), shareable(true) {}
    virtual ~RCObject() = 0 {}
    RCObject(const RCObject& rhs): refCount(0), shareable(true) {}
    RCObject& operator=(const RCObject& rhs) { return *this; }
    void addReference() {
        ++refCount;
    }
    void removeReference() {
        if (--refCount == 0) delete this;
    }
    void markUnshareable() {
        shareable = false;
    }
    bool isShareable() const {
        return shareable;
    }
    bool isShared() const {
        return refCount > 1;
    }
private:
    int refCount;
    bool shareable;
};
template <class T>
class RCPtr {
private:
    T*  pointee;
    void init(){
        if (pointee == 0)
            return;
        if (pointee->isShareable() == false)
            pointee = new T(*pointee);
        pointee->addReference();
    }
public:
    RCPtr(T* realPtr = 0) : pointee(realPtr) {
        init();
    }
    RCPtr(const RCPtr& rhs):pointee(rhs.pointee) {
        init();
    }
    ~RCPtr() {
        if (pointee)
            pointee->removeReference();
    }
    RCPtr& operator= (const RCPtr& rhs) {
        if (pointee != rhs.pointee) {
            if (pointee) {
                pointee->removeReference();
            }
            pointee = rhs.pointee;
            init();
        }
        return *this;
    }
    T* operator->()const {
        return pointee;
    }
    T&operator*()const {
        return *pointee;
    }
};
template <class X>
struct nodeType{
    RCPtr<X> Val;//smart Shared pointer to 
    nodeType<X>* next;
    nodeType<X>( RCPtr<X>& nSmartPointer, nodeType<X>* nextNode)
        :Val(nSmartPointer),next(nextNode) {

    }
    nodeType<X>(X* realPtr, nodeType<X>* nextNode)
        : Val(realPtr), next(nextNode) {

    }
};
