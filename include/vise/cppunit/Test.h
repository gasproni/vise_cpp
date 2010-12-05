#ifndef VISE_TEST_H
#define VISE_TEST_H


#include <string>
#include <boost/lexical_cast.hpp>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "vise/Vise.h"




namespace vise
    {
    namespace cppunit
	{
	class Test :
        public CPPUNIT_NS::TestFixture
	    {

	    public:


	    void setUp( )
		{
		// No getName available, in order for this to work,
		// the tests must be always executed in the same order.
		static std::size_t index = 0;
		std::string prefix = "ViseTest_";
		Vise::openSection( prefix + boost::lexical_cast< std::string >( index ) );
		++index;
		}


	    void tearDown( )
		{
		Vise::closeSection( );
		}
                
	    };
    
	}
    }


#endif
