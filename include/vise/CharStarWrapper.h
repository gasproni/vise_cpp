#ifndef VISE_CHARSTARWRAPPER_H
#define VISE_CHARSTARWRAPPER_H


#include "vise/Platform.h"
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/access.hpp>

#include "vise/SerializationTraits.h"



namespace vise
    {

    class VISE_API CharStarWrapper
	{

    public:

	CharStarWrapper( )
	    : isNull_( true ),
	      wrapped_( )
	    {
	    }


	CharStarWrapper( const char* wrapped )
	    : isNull_( wrapped == 0 ),
	      wrapped_( )
	    {
	    if ( !isNull_ )
		{
		wrapped_ = wrapped;
		}
	    }


	CharStarWrapper( char* wrapped )
	    : isNull_( wrapped == 0 ),
	      wrapped_( )
	    {
	    if ( !isNull_ )
		{
		wrapped_ = wrapped;
		}	    
	    }


	bool operator==( const CharStarWrapper& other ) const
	    {
	    if ( this == &other )
		{
		return true;
		}
	    return isNull_ == other.isNull_ &&
		wrapped_ == other.wrapped_;
	    }


	bool operator!=( const CharStarWrapper& other ) const
	    {
	    return ! ( *this == other );
	    }


	operator std::string( ) const
	    {
	    return wrapped_;
	    }


	const char* get( ) const
	    {
	    return wrapped_.c_str( );
	    }


    private:

	friend class boost::serialization::access;

	template< class Archive >
	void serialize( Archive & ar, unsigned int version )
	    {
	    ar & isNull_;
	    ar & wrapped_;
	    }

	bool isNull_;
	std::string wrapped_;
	};


    template < >
    struct VISE_API SerializationTraits< char* >
	{
	typedef const char* WrappedType;
	typedef CharStarWrapper WrappedTypeContainer;
	static std::string
	toString( const WrappedTypeContainer& container )
	    {
	    return container;
	    }

	};


    template < >
    struct VISE_API SerializationTraits< const char* >
	{
	typedef const char* WrappedType;
	typedef CharStarWrapper WrappedTypeContainer;
	static std::string
	toString( const WrappedTypeContainer& container )
	    {
	    return container;
	    }
	};


    }


#endif
