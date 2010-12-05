#ifndef VISE_DEFAULTMECHANICS_H
#define VISE_DEFAULTMECHANICS_H

#include "vise/Platform.h"

#include <string>
#include "vise/Mechanics.h"
#include "vise/MechanicsState.h"
#include "vise/OutsideSectionState.h"
#include "vise/RecordingState.h"
#include "vise/CheckingState.h"
#include "vise/SectionStore.h"




namespace vise
    {

    /* DefaultMechanics manages the state transitions of Vise.  Essentially,
     * it looks for an existing section with a given name when openSection is 
     * called and if it doesn't find one, it puts Vise into the recording state.  
     * If it does find an existing section with that name, Vise goes into the 
     * checking state.
     */
    class VISE_API DefaultMechanics: public Mechanics
	{
	
    public:


	DefaultMechanics( const SectionStorePtr& store )
	    : store_( store ),
	      state_( new OutsideSectionState( ) )
	    {
	    }
	

	virtual void openSection( const std::string& sectionName )
	    {
	    state_ = store_->hasSection( sectionName ) 
		? MechanicsStatePtr( new CheckingState( store_ ) ) 
		: MechanicsStatePtr( new RecordingState( store_ ) );

	    state_->openSection( sectionName );
	    }


	virtual bool isRecording( ) const
	    {
	    return state_->isRecording( );
	    }


	virtual void grip( const SerializablePtr& object,
			   const std::string& label = "" )
	    {
	    state_->grip( object, label );
	    }
	

	virtual void closeSection( )
	    {
	    state_->closeSection( );
	    state_ =  MechanicsStatePtr( new OutsideSectionState( ) );
	    }


	virtual void inspect( )
	    {
	    state_->inspect( );
	    }


	virtual void release( )
	    {
	    store_->clear( );
	    }


    private:


	SectionStorePtr store_;
	MechanicsStatePtr state_;


	};

    }

#endif
