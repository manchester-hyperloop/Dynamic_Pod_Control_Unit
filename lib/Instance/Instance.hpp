
#ifndef LIB_INSTANCE_INSTANCE_HPP
#define LIB_INSTANCE_INSTANCE_HPP

// Helper function
template <typename Base, typename T>
inline bool instanceof (const T *)
{
    return std::is_base_of<Base, T>::value;
}

#endif /* LIB_INSTANCE_INSTANCE_HPP */