#ifndef VISE_OUTSIDESECTIONSTATE_H
#define VISE_OUTSIDESECTIONSTATE_H


#include "vise/Platform.h"
#include <string>
#include "vise/MechanicsState.h"
#include "vise/Exception.h"
#include "vise/Serializable.h"
#include "vise/SerializableList.h"




namespace vise
    {
    
    class VISE_API OutsideSectionState : public MechanicsState
	{
    public:


	OutsideSectionState( )
	    : PREFIX( "invalid state error: " )
	    {
	    }


	void openSection( const std::string& sectionName )
	    {
	    }


	 void grip( const SerializablePtr& object,
		    const std::string& label )
	    {
	    throw Exception( PREFIX + "grip called without a "
			     "call to openSection" );
	    }


	 void closeSection( )
	    {
	    throw Exception( PREFIX + "closeSection called without a"
			     " call to openSection");
	    }
	

	 bool isRecording( ) const
	    {
	    return false;
	    }


    protected:


	virtual void getGrippedValues( SerializableList& result )
	    {
	    throw Exception( PREFIX + 
			     "getGrippedValues called without a"
			     " call to openSection");
	    }

    private:

	const std::string PREFIX;

	};

    }


#endif
