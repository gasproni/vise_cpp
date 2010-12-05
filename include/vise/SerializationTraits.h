#ifndef VISE_SERIALIZATIONTRAITS_H
#define VISE_SERIALIZATIONTRAITS_H


#include "vise/Platform.h"

#include <boost/lexical_cast.hpp>




namespace vise
    {

    template < class T >
    struct SerializationTraits
	{
	typedef T WrappedType;
	typedef T WrappedTypeContainer;
	static std::string
	toString( const WrappedTypeContainer& container )
	    {
	    return boost::lexical_cast< std::string >( container );
	    }
	};


    /**
     * Pointers are not supported
     */
    template < class T >
    struct VISE_API SerializationTraits< T* >;

    }


#endif
