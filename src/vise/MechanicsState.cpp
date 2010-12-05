
#include <sstream>
#include <boost/lexical_cast.hpp>

#include "vise/Exception.h"
#include "vise/MechanicsState.h"


#include <map>



void
vise::MechanicsState::
inspect( )
    {
    std::size_t index = 0;
    std::map< std::string, std::size_t > labelOccurrences;

    SerializableList grippedValues;
    getGrippedValues( grippedValues );

    std::size_t size = grippedValues.size( );

    std::stringstream message;
    message << "Vise contains " 
	    << size
	    << " grip"
	    << ( size != 1 ? "s" : "" )
	    << "\n";
		
    for( SerializableList::const_iterator it = grippedValues.begin( );
	 it != grippedValues.end( );
	 ++it )
	{
	RecordedGrip grip = *it;
	SerializablePtr object = grip.value_;

	message << index
		<< ": <"
		<< object->toString( ) << ">";

	if ( grip.hasLabel( ) )
	    {
	    std::size_t& occurrences = labelOccurrences[ grip.label_ ];

	    message << " "
		    << grip.label_
		    <<  " (" 
		    << occurrences 
		    << ")";
 
	    ++occurrences;
	    }
	message << "\n";
	++index;
	}

    throw Exception( message.str( ) );

    }
