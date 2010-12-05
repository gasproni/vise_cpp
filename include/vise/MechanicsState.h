#ifndef VISE_MECHANICSSTATE_H
#define VISE_MECHANICSSTATE_H


#include "vise/Platform.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "vise/Serializable.h"
#include "vise/SerializableList.h"




namespace vise
    {
    
    class VISE_API MechanicsState
	{
    public:

	virtual ~MechanicsState( )
	    {
	    }

	virtual bool isRecording( ) const = 0;

	virtual void openSection( const std::string& sectionName ) = 0;

	virtual void grip( const SerializablePtr& object,
			   const std::string& label ) = 0;

	virtual void closeSection( ) = 0;

	void inspect( );

    protected:

	virtual void getGrippedValues( SerializableList& result ) = 0;

	};


    typedef boost::shared_ptr< MechanicsState > MechanicsStatePtr;

    }


#endif
