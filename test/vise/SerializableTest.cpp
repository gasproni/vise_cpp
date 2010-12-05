
#include <sstream>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "vise/Serializable.h"




namespace vise
    {

    class SerializableTest :
        public CPPUNIT_NS::TestFixture
        {
        
        CPPUNIT_TEST_SUITE( SerializableTest );
        
        CPPUNIT_TEST( testEquality );
        CPPUNIT_TEST( testDifferenceDifferentTypes );
        CPPUNIT_TEST( testDifferenceSameType );
        CPPUNIT_TEST( testSerializationNullCharStar );
        CPPUNIT_TEST( testSerialization );
        
        CPPUNIT_TEST_SUITE_END( );

    public:


        void testEquality( )
            {
            SerializableWrapper< int > obj1( 10 );
            SerializableWrapper< int > obj2( 10 );

            CPPUNIT_ASSERT( obj1 == obj2 );
            }
        

        void testDifferenceDifferentTypes( )
            {
            SerializableWrapper< int > intObj( 10 );
            SerializableWrapper< char > charObj( 'c' );

            CPPUNIT_ASSERT( intObj != charObj );
            }


        void testDifferenceSameType( )
            {
            SerializableWrapper< int > intObj1( 10 );
            SerializableWrapper< int > intObj2( 20 );
	    
            CPPUNIT_ASSERT( intObj1 != intObj2 );
            }


        void testSerializationNullCharStar( )
            {
	    char* nullStr = 0;
	    assertSerializationWorks( nullStr );
	    assertSerializationWorks( ( const char* )nullStr );
            }


        void testSerialization( )
            {
	    assertSerializationWorks( 'c' );
	    
	    assertSerializationWorks( ( unsigned char )'c' );
	    assertSerializationWorks( ( signed char )'c' );
	    assertSerializationWorks( ( short )10 );
	    assertSerializationWorks( ( unsigned short )10 );
	    assertSerializationWorks( ( int )10 );
	    assertSerializationWorks( ( unsigned int )10 );
	    assertSerializationWorks( ( long )10 );
	    assertSerializationWorks( ( unsigned long )10 );
	    assertSerializationWorks( true );
	    assertSerializationWorks( false );
	    assertSerializationWorks( ( float )10.3 );
	    assertSerializationWorks( ( double )10.3 );
	    /* Doesn't work in Mac OS X with gcc 3.2.1
	    assertSerializationWorks( ( long double )10.3 );
	    */
	    assertSerializationWorks( std::string( "hey!" ) );
	    assertSerializationWorks( std::string( "" ) );
	    assertSerializationWorks( "hey" );
	    char* str = new char[ 2 ];
	    str[ 0 ] = 'a';
	    str[ 1 ] = '\0';
	    assertSerializationWorks( str );
	    delete[ ] str;
	    }


	template < class TypeT >
	void assertSerializationWorks( TypeT wrappedObject )
	    {
            SerializablePtr serializable =
		makeSerializableWrapperPtr( wrappedObject );

	    std::stringstream archiveStream;
	    {
	    boost::archive::text_oarchive oa( archiveStream );
	    oa << serializable;
	    }
	
	    SerializablePtr readSerializable;	    
	    
	    {
	    boost::archive::text_iarchive ia( archiveStream );	    
	    ia >> readSerializable;
	    }
	    CPPUNIT_ASSERT( serializable->equals( *readSerializable ) );
	  }

	};

      CPPUNIT_TEST_SUITE_REGISTRATION( SerializableTest );
    }

