#ifndef IFT_SCOPED_GLOBAL_LOCK_HPP
#define IFT_SCOPED_GLOBAL_LOCK_HPP

namespace ift {

class scoped_global_lock
{
public:
    scoped_global_lock();
    ~scoped_global_lock() throw ();
    static bool locked();
private:
    static int mutex;
    static __thread int recurse;
};

}

#endif
