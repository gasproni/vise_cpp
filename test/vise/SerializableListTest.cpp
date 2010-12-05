
#include <sstream>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "vise/Serializable.h"
#include "vise/SerializableList.h"





namespace vise
    {

    class SerializableListTest :
        public CPPUNIT_NS::TestFixture
        {
        
        CPPUNIT_TEST_SUITE( SerializableListTest );
        
        CPPUNIT_TEST( testSerialization );
        
        CPPUNIT_TEST_SUITE_END( );

    public:

        void testSerialization( )
            {
            SerializableList serializableList;
	    serializableList.push_back(
                makeSerializableWrapperPtr( ( int )10 ) );

	    serializableList.push_back(
                makeSerializableWrapperPtr( std::string( "ciao" ) ) );
	    serializableList.push_back(
                makeSerializableWrapperPtr( ( double )15.01 ) );
	    serializableList.push_back(
                makeSerializableWrapperPtr( ( long )150 ) );
	    serializableList.push_back(
                makeSerializableWrapperPtr( ( unsigned char )'c' ) );
	    serializableList.push_back(
                makeSerializableWrapperPtr( ( char* )0 ) );
	    
            std::stringstream archiveStream;
            {
	    boost::archive::text_oarchive oa( archiveStream );

	    const SerializableList& serializableList2 = serializableList;	    
	    oa << serializableList2;
	    }

	    SerializableList readSerializableList;	    
	    
	    {
	    boost::archive::text_iarchive ia( archiveStream );

	    ia >> readSerializableList;
	    }

	    CPPUNIT_ASSERT_EQUAL( serializableList.size( ),
				  readSerializableList.size( ) );
	    
	    SerializableList::const_iterator currentSerializableListIt =
		serializableList.begin( );
	    SerializableList::const_iterator endSerializableListIt =
		serializableList.end( );

	    SerializableList::const_iterator currentReadIt =
		readSerializableList.begin( );
	    SerializableList::const_iterator endReadIt =
		readSerializableList.end( );

	    for ( ; currentSerializableListIt != endSerializableListIt;
		  ++currentSerializableListIt, ++currentReadIt )
		{
		CPPUNIT_ASSERT( *currentSerializableListIt == *currentReadIt );
		}

            }

        };
    
      CPPUNIT_TEST_SUITE_REGISTRATION( SerializableListTest );
    }
