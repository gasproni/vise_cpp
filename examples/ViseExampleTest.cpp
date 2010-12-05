
#include <string>
#include "vise/Vise.h"
#include "vise/cppunit/Test.h"

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>


#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>




/* This is a simple of example of Vise in action.
 * The first time you run the test below, it will record the value of barcode 
 * in addItem and the value of the line in the display.
 * 
 * To see how Vise works, run the test once and then comment out one of 
 * the Vise calls.  You should receive a message 
 * which tells you that the Vise has remaining values after test execution.
 *  Go back and uncomment the grip call.  The tests should pass again.
 * 
 * To see some of the other errors, add a new grip 
 * call and see what happens.
 *  Try changing one of the values which is sent to grip also.
 */


namespace examples
    {

    class EncrustedDisplay
	{
	
    public:
	
	void showLine( const char* line )
	    {
	    vise::Vise::grip( line );
	    // ...
	    }
	};


    class Sale
	{
	
	EncrustedDisplay display_;

	
    public:

	Sale( )
	    : display_( )
	    {
	    }
	
	void addItem( const std::string& barcode )
	    {
	    if ( barcode == "1" )
		{
		vise::Vise::grip( barcode );
		display_.showLine( "Milk $3.99" );
		}
	    else if( barcode == "2" )
		{
		display_.showLine( "Cornflakes $2.99" );
		}
		
	    };
	};
    


    class ViseExampleTest : public vise::cppunit::Test
	{
	
	CPPUNIT_TEST_SUITE( ViseExampleTest );
        
        CPPUNIT_TEST( testAddItem );
        CPPUNIT_TEST( testAddAnotherItem );

        CPPUNIT_TEST_SUITE_END( );

    public:

	void testAddItem( )
	    {
	    Sale sale;
	    sale.addItem( "1" );
	    }
	

	void testAddAnotherItem( )
	    {
	    Sale sale;
	    sale.addItem( "2" );
	    }	
	};

    CPPUNIT_TEST_SUITE_REGISTRATION( ViseExampleTest );
    }


int
main( int argc, char* argv[] )
    {
    // Create the event manager and test controller
    CPPUNIT_NS::TestResult controller;

    // Add a listener that colllects test result
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener( &result );        

    // Add a listener that print dots as test run.
    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener( &progress );      

    // Add the top suite to the test runner
    CPPUNIT_NS::TestRunner runner;
    runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
    runner.run( controller );

    // Print test in a compiler compatible format.
    CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
    outputter.write(); 

    return result.wasSuccessful() ? 0 : 1;
    }
