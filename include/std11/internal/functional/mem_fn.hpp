/*
 * mem_fn.hpp
 *
 */

#ifndef STDBP_STD11_INTERNAL_FUNCTIONAL_MEM_FN_HPP_
#define STDBP_STD11_INTERNAL_FUNCTIONAL_MEM_FN_HPP_

namespace std11 {

template <class R, class T, class F>
class mem_fn_t {
    F f_;

public:
    typedef R result_type;

    explicit mem_fn_t(F f) : f_(f) {}

    // 0
    result_type operator()(T& obj)
        { return (obj.*f_)(); }

    result_type operator()(const T& obj) const
        { return (obj.*f_)(); }

    result_type operator()(T* obj)
        { return (obj->*f_)(); }

    result_type operator()(const T* obj) const
        { return (obj->*f_)(); }

    // 1
    template <class A1>
    result_type operator()(T& obj, A1 a1)
        { return (obj.*f_)(a1); }

    template <class A1>
    result_type operator()(const T& obj, A1 a1) const
        { return (obj.*f_)(a1); }

    template <class A1>
    result_type operator()(T* obj, A1 a1)
        { return (obj->*f_)(a1); }

    template <class A1>
    result_type operator()(const T* obj, A1 a1) const
        { return (obj->*f_)(a1); }

    // 2
    template <class A1, class A2>
    result_type operator()(T& obj, A1 a1, A2 a2)
        { return (obj.*f_)(a1, a2); }

    template <class A1, class A2>
    result_type operator()(const T& obj, A1 a1, A2 a2) const
        { return (obj.*f_)(a1, a2); }

    template <class A1, class A2>
    result_type operator()(T* obj, A1 a1, A2 a2)
        { return (obj->*f_)(a1, a2); }

    template <class A1, class A2>
    result_type operator()(const T* obj, A1 a1, A2 a2) const
        { return (obj->*f_)(a1, a2); }

    // 3
    template <class A1, class A2, class A3>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3)
        { return (obj.*f_)(a1, a2, a3); }

    template <class A1, class A2, class A3>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3) const
        { return (obj.*f_)(a1, a2, a3); }

    template <class A1, class A2, class A3>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3)
        { return (obj->*f_)(a1, a2, a3); }

    template <class A1, class A2, class A3>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3) const
        { return (obj->*f_)(a1, a2, a3); }

    // 4
    template <class A1, class A2, class A3, class A4>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3, A4 a4)
        { return (obj.*f_)(a1, a2, a3, a4); }

    template <class A1, class A2, class A3, class A4>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3, A4 a4) const
        { return (obj.*f_)(a1, a2, a3, a4); }

    template <class A1, class A2, class A3, class A4>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3, A4 a4)
        { return (obj->*f_)(a1, a2, a3, a4); }

    template <class A1, class A2, class A3, class A4>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3, A4 a4) const
        { return (obj->*f_)(a1, a2, a3, a4); }

    // 5
    template <class A1, class A2, class A3, class A4, class A5>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        { return (obj.*f_)(a1, a2, a3, a4, a5); }

    template <class A1, class A2, class A3, class A4, class A5>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        { return (obj.*f_)(a1, a2, a3, a4, a5); }

    template <class A1, class A2, class A3, class A4, class A5>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
        { return (obj->*f_)(a1, a2, a3, a4, a5); }

    template <class A1, class A2, class A3, class A4, class A5>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
        { return (obj->*f_)(a1, a2, a3, a4, a5); }

    // 6
    template <class A1, class A2, class A3, class A4, class A5, class A6>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6); }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6); }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6); }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6); }

    // 7
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6, a7); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6, a7); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6, a7); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6, a7); }

    // 8
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6, a7, a8); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6, a7, a8); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6, a7, a8); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6, a7, a8); }

    // 9
    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    result_type operator()(T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    result_type operator()(const T& obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
        { return (obj.*f_)(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    result_type operator()(T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    result_type operator()(const T* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
        { return (obj->*f_)(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
};


// mem_fn
template <class R, class T>
mem_fn_t<R, T, R (T::*)()>
    mem_fn(R (T::*f)())
{
    return mem_fn_t<R, T, R (T::*)()>(f);
}

template <class R, class T>
mem_fn_t<R, T, R (T::*)() const>
    mem_fn(R (T::*f)() const)
{
    return mem_fn_t<R, T, R (T::*)() const>(f);
}

template <class R, class T, class A1>
mem_fn_t<R, T, R (T::*)(A1)>
    mem_fn(R (T::*f)(A1))
{
    return mem_fn_t<R, T, R (T::*)(A1)>(f);
}

template <class R, class T, class A1>
mem_fn_t<R, T, R (T::*)(A1) const>
    mem_fn(R (T::*f)(A1) const)
{
    return mem_fn_t<R, T, R (T::*)(A1) const>(f);
}

template <class R, class T, class A1, class A2>
mem_fn_t<R, T, R (T::*)(A1, A2)>
    mem_fn(R (T::*f)(A1, A2))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2)>(f);
}

template <class R, class T, class A1, class A2>
mem_fn_t<R, T, R (T::*)(A1, A2) const>
    mem_fn(R (T::*f)(A1, A2) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2) const>(f);
}

template <class R, class T, class A1, class A2, class A3>
mem_fn_t<R, T, R (T::*)(A1, A2, A3)>
    mem_fn(R (T::*f)(A1, A2, A3))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3)>(f);
}

template <class R, class T, class A1, class A2, class A3>
mem_fn_t<R, T, R (T::*)(A1, A2, A3) const>
    mem_fn(R (T::*f)(A1, A2, A3) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3) const>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4)>
    mem_fn(R (T::*f)(A1, A2, A3, A4))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4)>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4) const>
    mem_fn(R (T::*f)(A1, A2, A3, A4) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4) const>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5)>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5)>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5) const>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5) const>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6)>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6)>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6) const>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6) const>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6, class A7>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7)>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6, A7))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7)>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6, class A7>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7) const>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6, A7) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7) const>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6, class A7, class A8>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8)>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6, A7, A8))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8)>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6, class A7, class A8>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8) const>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6, A7, A8) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8) const>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6, class A7, class A8, class A9>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9))
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9)>(f);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5,
                            class A6, class A7, class A8, class A9>
mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const>
    mem_fn(R (T::*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const)
{
    return mem_fn_t<R, T, R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const>(f);
}

}  // namespace shand

#endif /* STDBP_STD11_INTERNAL_FUNCTIONAL_MEM_FN_HPP_ */
