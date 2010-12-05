#ifndef VISE_RECORDEDGRIP_H
#define VISE_RECORDEDGRIP_H


#include "vise/Platform.h"
#include <string>
#include "vise/Serializable.h"
#include "vise/Export.h"




namespace vise
    {

    /* RecordedGrip is a handy little class that associates a recorded
     * grip value with any label that a Vise user supplies.
     * 
     * Vise files are a list of RecordedGrip objects.
     */

    struct VISE_API RecordedGrip
	{
	
	SerializablePtr value_;
	
	std::string label_;
	
	RecordedGrip( const SerializablePtr& value,
		      const std::string& label = "" )
	    : value_( value ),
	      label_( label )
	    {
	    }
	

	bool hasLabel( ) const
	    {
	    return !label_.empty( );
	    }


	bool operator==( const RecordedGrip& other ) const
	    {
	    return value_->equals( *( other.value_ ) );
	    }


    private:

	friend class boost::serialization::access;


	/**
	 * Necessary for serialization
	 */
	RecordedGrip( )
	    : value_( ),
	      label_( )
	    {
	    }

	
	template< class Archive >
	void serialize( Archive & ar, unsigned int version )
	    {
	    ar & value_;
	    ar & label_;
	    }
	};

    }

#endif
