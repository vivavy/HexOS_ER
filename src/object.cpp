#include <object.hh>
#include <vheap.hh>

void *Object::operator new(usize size) {
    return vheap::alloc(size);
}

void Object::operator delete(void *ptr) {
    vheap::free(ptr, sizeof(Object));
}
