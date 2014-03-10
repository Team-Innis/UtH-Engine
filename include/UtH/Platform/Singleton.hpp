#pragma once
#ifndef SINGLETON_H_UTH
#define SINGLETON_H_UTH

#include <UtH/Platform/Uncopyable.hpp>

namespace uth
{
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// A template base class for maintaining a single instance of some other class.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////
    template<class C>
    class Singleton : private uth::Uncopyable
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Functions
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /// Get the instance.
        ///
        /// Returns a reference to the local static instance of the templated class.
        ///
        /// \return A reference to the singletoned class.
        ///
        /**/ static C& getInstance()
        {
            static C instance;

            return instance;
        }


    }; // class Singleton

} // namespace uth

#endif