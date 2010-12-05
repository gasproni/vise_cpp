#ifndef VISE_SERIALIZABLE_H
#define VISE_SERIALIZABLE_H


#include "vise/Platform.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>

#include "vise/Export.h"
#include "vise/CharStarWrapper.h"
#include "vise/SerializationTraits.h"




namespace vise
    {
    
    class VISE_API Serializable
	{

    public:


	virtual ~Serializable( )
	    {
	    }


	virtual bool equals( const Serializable& other ) const = 0;

	virtual std::string toString( ) const = 0;
	
	bool operator==( const Serializable& other ) const
	    {
	    return this->equals( other );
	    }


	bool operator!=( const Serializable& other ) const
	    {
	    return !( *this == other );
	    }


    protected:

	Serializable( )
	    {
	    }

    private:

	friend class boost::serialization::access;
	
	template< class Archive >
	void serialize( Archive & ar, unsigned int version )
	    {
	    }

	};

    
    VISE_API typedef boost::shared_ptr< Serializable > SerializablePtr;


    template< class TypeT >
    class SerializableWrapper : public Serializable
	{
    public:


	SerializableWrapper( const TypeT& wrapped )
	    : wrapped_( wrapped )
	    {
	    }


	typename SerializationTraits< TypeT >::WrappedType
	get( ) const
	    {
	    return wrapped_;
	    }


	virtual std::string toString( ) const
	    {
	    return SerializationTraits< TypeT >::toString( wrapped_ );
	    }


	virtual bool equals( const Serializable& other ) const
	    {
	    const SerializableWrapper* otherPtr =
		dynamic_cast< const SerializableWrapper* >( &other );

	    return otherPtr != 0 &&
		this->wrapped_ == otherPtr->wrapped_;
	    }


    private:

	friend class boost::serialization::access;


	/**
	 * Necessary for serialization
	 */
	SerializableWrapper( )
	    : wrapped_( )
	    {
	    }

	
	template< class Archive >
	void serialize( Archive & ar, unsigned int version )
	    {
	    ar & boost::serialization::base_object< Serializable >( *this );
	    ar & wrapped_;
	    }

	typename SerializationTraits< TypeT >::WrappedTypeContainer
	wrapped_;
	
	};


    template < class TypeT >
    SerializablePtr makeSerializableWrapperPtr( const TypeT& obj )
	{
	return SerializablePtr( new SerializableWrapper< TypeT >( obj ) );
	}


    inline SerializablePtr makeSerializableWrapperPtr( const char* obj )
	{
	return SerializablePtr( new SerializableWrapper< const char* >( obj ) );
	}

    }

VISE_IS_ABSTRACT( vise::Serializable );

#ifdef _WIN32
#    include "vise/SerializableExports.h"
# endif // _WIN32

#endif
