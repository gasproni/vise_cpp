#ifndef VISE_VISE_H
#define VISE_VISE_H

#include "vise/Platform.h"
#include <string>
#include "vise/Serializable.h"
#include "vise/Mechanics.h"



namespace vise
    {

    class VISE_API Vise
	{

    public:

        template< class T >
        static void grip( const T& object,
                          const std::string& label = "" )
	    {
	    s_mechanics->grip( makeSerializableWrapperPtr( object ), label );
	    }


	static inline
        void openSection( const std::string& section )
	    {
	    s_mechanics->openSection( section );
	    }
	
	
	static inline void inspect( )
	    {
	    s_mechanics->inspect( );
	    }
	

	static inline void closeSection( )
	    {
	    s_mechanics->closeSection( );
	    }
	

	static inline void release( )
	    {
	    s_mechanics->release( );
	    }
        
    private:

	Vise( );

	static MechanicsPtr s_mechanics;

	};
    }


#endif
