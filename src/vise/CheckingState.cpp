
#include <sstream>

#include "vise/CheckingState.h"
#include "vise/RecordedGrip.h"




void
vise::CheckingState::
openSection( const std::string& sectionName )
    {
    store_->retrieveSection( sectionName, grippedValues_ );
    currentPosition_ = grippedValues_.begin( );
    }


void
vise::CheckingState::
grip( const SerializablePtr& object,
      const std::string& label )
    {
    if( currentPosition_ == grippedValues_.end( ) )
	{
        throwFromGrip("Vise can't find any more values. "
		      " All have been matched.");
        return;
        } 
    RecordedGrip grip = *currentPosition_;
    ++currentPosition_;
    if ( !grip.value_->equals( *object ) )
	{
	std::stringstream message;
	message << "Vise expected grip "
		<< ( grip.hasLabel( ) ? ( "\"" + grip.label_ + "\" " ) : "" )
		<< "with <" 
		<< grip.value_->toString( )
		<< "> but was grip with <" 
		<< object->toString( ) 
		<< ">";
	throwFromGrip( message.str( ) );
        }       
    }


void
vise::CheckingState::
closeSection( )
    {
    if ( currentPosition_ != grippedValues_.end( ) &&
	 !hasThrownInCurrentSection_ )
	{
	throw Exception( "Vise has values with no remaining grip calls." );
	}
    }
