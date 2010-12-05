
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <boost/filesystem/operations.hpp>

#include "vise/FileBasedStore.h"
#include "vise/RecordedGrip.h"




namespace vise
    {

    class FileBasedStoreTest :
        public CPPUNIT_NS::TestFixture
        {
        
        CPPUNIT_TEST_SUITE( FileBasedStoreTest );

        CPPUNIT_TEST( testHasSection );
        CPPUNIT_TEST( testSaveSection );
        CPPUNIT_TEST( testClear );

        CPPUNIT_TEST_SUITE_END( );

        std::string DIRECTORY_BASE;
	FileBasedStore store_;

    public:

        void setUp( )
            {
            DIRECTORY_BASE = "./persistedvisefiles";
            if ( !boost::filesystem::exists( DIRECTORY_BASE ) )
                {
                boost::filesystem::create_directory( DIRECTORY_BASE );
                }
	    store_ = FileBasedStore( DIRECTORY_BASE );
            }


        void testHasSection( )
            {
            CPPUNIT_ASSERT( !store_.hasSection( "testFile" ) );
            }


        void testSaveSection( )
            {
            FileBasedStore store( DIRECTORY_BASE );

	    
            RecordedGrip grip = makeSerializableWrapperPtr( 10 );

            SerializableList allValues;
            allValues.push_back( grip );

            store.saveSection( "anExample", allValues );
            CPPUNIT_ASSERT( store.hasSection( "anExample" ) );
                
            SerializableList retrievedValues;
            store.retrieveSection( "anExample", retrievedValues );
            CPPUNIT_ASSERT( grip == *( retrievedValues.begin( ) ) );

            }


	void testClear( )
	    {
	    FileBasedStore store( DIRECTORY_BASE );

	    std::string sectionName = "alpha";
	    SerializableList allValues;
            allValues.push_back( makeSerializableWrapperPtr( 10 ) );

	    store.saveSection( sectionName, allValues );

	    store.clear();

	    CPPUNIT_ASSERT( ! store.hasSection( sectionName ) );
	}


        };
    
CPPUNIT_TEST_SUITE_REGISTRATION( FileBasedStoreTest );
}

