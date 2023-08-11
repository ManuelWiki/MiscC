namespace miscc
{
template <class Return, class... Args>
class Function_BaseType {
    using Function_Ptr = Return (*)(Args...);

    Function_Ptr fn = nullptr;
    Return value;

public:
    // Avoid default initialization
    Function_BaseType() = delete;

    // C'tor for single Return paramater
    Function_BaseType(Return v) : value(v) {}

    // C'tor for Function_Ptr parameter
    Function_BaseType(Function_Ptr f) : fn(f) {}

    // The caller (parentheses operator)
    Return operator() (Args... args)
    {
        if (fn == nullptr) return value;
        
        return (*fn)(args...);
    }
};

template <class R, class... A>
class Function_Specializer { public: using type = Function_BaseType<R, A...>; };
template <class R, class... A>
class Function_Specializer<R(A...)> { public: using type = Function_BaseType<R, A...>; };

template <class T>
using Function = typename Function_Specializer<T>::type;
}