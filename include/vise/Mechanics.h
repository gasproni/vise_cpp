#ifndef VISE_MECHANICS_H
#define VISE_MECHANICS_H

#include "vise/Platform.h"

#include <string>
#include <boost/shared_ptr.hpp>
#include "vise/Serializable.h"




namespace vise
    {

    /* Mechanics defines the fundamental abstraction of Vise.  It
     * allows users to open and close sections, it defines an
     * inspect method which lets users see the current contents of the
     * vise, and it defines a release method which releases all griped
     * values and essentially puts vise back into the recording state. 
     */

    class VISE_API Mechanics
	{
    public:

	virtual ~Mechanics( )
	    {
	    }


	virtual void openSection( const std::string& sectionName ) = 0;

	virtual void closeSection( ) = 0;

	virtual bool isRecording( ) const = 0;

	virtual void grip( const SerializablePtr& object,
			   const std::string& label = "" ) = 0;

	virtual void inspect( ) = 0;

	virtual void release( ) = 0;

	};

    typedef boost::shared_ptr< Mechanics > MechanicsPtr;

    }


#endif
