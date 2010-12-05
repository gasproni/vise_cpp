#ifndef VISE_EXCEPTION_H
#define VISE_EXCEPTION_H


#include "vise/Platform.h"
#include <exception>
#include <string>




namespace vise
    {
    
    class VISE_API Exception : public std::exception
	{

    public:

	Exception( const std::string& what )
	    : what_( what )
	    {
	    }


	~Exception( )
	    throw( )
	    {
	    }


	virtual const char* what( ) const
	    throw( )
	    {
	    return what_.c_str( );
	    }

    private:

	std::string what_;

	};
    
    }

#endif
