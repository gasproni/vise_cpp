#ifndef VISE_CHECKINGSTATE_H
#define VISE_CHECKINGSTATE_H


#include "vise/Platform.h"
#include <string>
#include "vise/Exception.h"
#include "vise/MechanicsState.h"
#include "vise/Serializable.h"
#include "vise/SerializableList.h"
#include "vise/SectionStore.h"




namespace vise
    {
    
    /* When Vise is in the checking state, each call to the grip method
     * retrieves the next recorded value and compares it to the value
     * sent to grip.  If the values don't match, the checking state throws
     * an exception that can be caught by CppUnit, FIT or any other tool
     * that uses vise.  Grip also throws an exception if there are no
     * more values to retrieve.  The closeSection method throws an 
     * exception if there are remaining values that have not been gripped.
     * Together, these behaviors force vise to make exact matches of 
     * values it has recorded.  Any inexact match produces an exception
     * that signifies an error.
     * 
     * The logic that uses the hasThrownInCurrentSection field is there
     * to deal with some behavior that CppUnit exhibits.  The most common
     * way to use Vise in CppUnit is to open and close sections in setUp and
     * tearDown.  In CppUnit, if an exception is thrown in code that is 
     * executed by tearDown, that exception is shown.  Any exception thrown
     * in the actual test method is discared.  This makes sense for most
     * CppUnit tests.  Setup and tearDown are part of the test, not the code
     * under test, so if there is a problem in the test, it would be nice
     * to know about it before assuming that the test indicates a problem
     * with the code under test.
     * 
     *  In Vise, we want the opposite behavior.  If we thrown an exception
     *  in a test method, we know that we will not have gripped all of the 
     *  values we've recorded, so closeSection will throw an exception.  We
     *  are interested in the first error that happened: the initial mismatch.
     *  For that reason, I have logic which only throws an exception in 
     *  tearDown if we haven't thrown an exception from grip. 
     */
    class VISE_API CheckingState : public MechanicsState
	{
    public:


	CheckingState( const SectionStorePtr& store )
	    : grippedValues_( ),
	      currentPosition_( ),
	      hasThrownInCurrentSection_( false ),
	      store_( store )
	    {
	    }


	virtual bool isRecording( ) const
	    {
	    return false;
	    }

	virtual void openSection( const std::string& sectionName );


	virtual void grip( const SerializablePtr& object,
			   const std::string& label );


	virtual void closeSection( );


    protected:


	virtual void getGrippedValues( SerializableList& result )
	    {
	    result = grippedValues_;
	    }


    private:


	void throwFromGrip( const std::string& message )
	    {
	    hasThrownInCurrentSection_ = true;
	    throw Exception( message );
	    }


	SerializableList grippedValues_;
	SerializableList::const_iterator currentPosition_;
	bool hasThrownInCurrentSection_;
	SectionStorePtr store_;
	};

    }


#endif
