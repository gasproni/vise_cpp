#ifndef VISE_RECORDINGSTATE_H
#define VISE_RECORDINGSTATE_H


#include "vise/Platform.h"
#include <string>
#include "vise/MechanicsState.h"
#include "vise/Serializable.h"
#include "vise/SerializableList.h"
#include "vise/SectionStore.h"




namespace vise
    {
    
    class VISE_API RecordingState : public MechanicsState
	{
    public:


	RecordingState( const SectionStorePtr& store )
	    : grippedValues_( ),
	      sectionName_( ),
	      store_( store )
	    {
	    }


	
	void openSection( const std::string& sectionName )
	    {
		sectionName_ = sectionName;
	    }


	 void grip( const SerializablePtr& object,
		    const std::string& label )
	    {
	    grippedValues_.push_back( RecordedGrip( object, label ) );
	    }


	 void closeSection()
	    {
	    store_->saveSection( sectionName_, grippedValues_ );
	    }
	

	 bool isRecording( ) const
	    {
	    return true;
	    }


    protected:


	virtual void getGrippedValues( SerializableList& result )
	    {
	    result = grippedValues_;
	    }


    private:


	SerializableList grippedValues_;
	std::string sectionName_;
	SectionStorePtr store_;
	};

    }


#endif
