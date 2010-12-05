#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "vise/DefaultMechanics.h"
#include "vise/FakeSectionStore.h"




namespace vise
    {

    class DefaultMechanicsTest :
        public CPPUNIT_NS::TestFixture
        {
        
        CPPUNIT_TEST_SUITE( DefaultMechanicsTest );
        
        CPPUNIT_TEST( testSaveSection );
        CPPUNIT_TEST( testGrip );
        CPPUNIT_TEST( testSwitchOffRecording );
        CPPUNIT_TEST( testGripPlaybackFailed );
        CPPUNIT_TEST( testGripPlaybackErrorTooFew );
        CPPUNIT_TEST( testGripPlaybackErrorTooMany );
        CPPUNIT_TEST( testMultiple );
        CPPUNIT_TEST( testInspectSingle );
        CPPUNIT_TEST( testInspectMultiple );
        CPPUNIT_TEST( testInspectNone );
        CPPUNIT_TEST( testNoThrowFromCloseIfAlreadyThrown );
        CPPUNIT_TEST( testReleaseVise );
        CPPUNIT_TEST( testGripWithNoOpen );
        CPPUNIT_TEST( testCloseWithNoOpen );
        CPPUNIT_TEST( testResetToOutsideSectionOnClose );
        CPPUNIT_TEST( testGripWithLabel );
        CPPUNIT_TEST( testGripWithAdvancingLabel );
        CPPUNIT_TEST( testFailureOfGripWithLabel );

        CPPUNIT_TEST_SUITE_END( );

        SectionStorePtr store_;
        MechanicsPtr vise_;

    public:

        
        void setUp( )
            {
            store_ = SectionStorePtr( new FakeSectionStore( ) );
            vise_ = MechanicsPtr( new DefaultMechanics( store_ ) );
            }


        void testSaveSection( )
            {
            vise_->openSection( "aSection" );
            CPPUNIT_ASSERT( vise_->isRecording( ) );
            }


        void testGrip( )
            {
            vise_->openSection( "aSection" );
            vise_->grip( makeSerializableWrapperPtr( 3 ) );
            vise_->closeSection( );
            CPPUNIT_ASSERT( 1 == store_->size( "aSection" ) );
            }


        void testSwitchOffRecording( )
            {
            vise_->openSection( "aSection" );
            CPPUNIT_ASSERT( vise_->isRecording( ) );
            
            SerializableList variables;

            store_->saveSection( "anotherSection", variables );
            vise_->openSection( "anotherSection" );
            CPPUNIT_ASSERT( !vise_->isRecording( ) );
            }


        void testGripPlaybackFailed( )
            {
            SerializableList variables;
            variables.push_back( RecordedGrip( makeSerializableWrapperPtr( 2 ) ) );

            store_->saveSection( "aSection", variables );

            vise_->openSection( "aSection" );
            try
                {
                vise_->grip( makeSerializableWrapperPtr( 3 ) );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL
                    ( std::string( "Vise expected grip with <2> "
                                   "but was grip with <3>" ),
                      std::string( e.what( ) ) );
                }
            
            vise_->closeSection( );
            }


        void testGripPlaybackErrorTooFew( )
            {
            SerializableList variables;
            store_->saveSection( "aSection", variables );
            vise_->openSection( "aSection" );
            try
                {
                vise_->grip( makeSerializableWrapperPtr( 3 ) );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL
                    ( std::string( "Vise can't find any more values.  "
                                   "All have been matched." ),
                      std::string( e.what( ) ) );
                }
            vise_->closeSection( );
            }           


          void testGripPlaybackErrorTooMany( )
            {
            SerializableList variables;
            variables.push_back( RecordedGrip( makeSerializableWrapperPtr( 3 ) ) );
            store_->saveSection( "aSection", variables );
            vise_->openSection( "aSection" );
            try
                {
                vise_->closeSection( );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL
                    ( std::string( "Vise has values with no "
                                   "remaining grip calls." ),
                      std::string( e.what( ) ) );
                }
            }


        void testMultiple( )
            {
            // Make a preexisting aSection
            SerializableList variables;
            variables.push_back( RecordedGrip
                                 ( makeSerializableWrapperPtr( "a" ) ) );
            store_->saveSection( "aSection", variables );
            
            // Open the existing section
            vise_->openSection( "aSection" );
            vise_->grip( makeSerializableWrapperPtr( "a" ) );
            vise_->closeSection( );
            
            // Open a nonexisting section for recording
            vise_->openSection( "bSection" );
            vise_->closeSection( );
            
            // Open for retrieval an see that the things from 
            // aSection aren't there
            vise_->openSection( "bSection" );
            vise_->closeSection( );
            
            }


        void testInspectSingle( )
            {
            vise_->openSection( "aSection" );
            vise_->grip( makeSerializableWrapperPtr( "a" ) );
            try
                {
                vise_->inspect( );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                vise_->closeSection( );
                CPPUNIT_ASSERT_EQUAL( std::string( "Vise contains "
                                                   "1 grip\n0: <a>\n" ),
                                      std::string( e.what( ) ) );
                }
            catch ( ... )
                {
                vise_->closeSection( );
                throw;
                }
            }


        void testInspectMultiple( )
            {
            vise_->openSection( "aSection" );
            vise_->grip( makeSerializableWrapperPtr( "a" ) );
            vise_->grip( makeSerializableWrapperPtr( "b" ) );
            try
                {
                vise_->inspect( );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                vise_->closeSection( );
                CPPUNIT_ASSERT_EQUAL( std::string( "Vise contains 2 "
                                                   "grips\n0: <a>\n1: <b>\n" ),
                                      std::string( e.what( ) ) );
                }
            catch ( ... )
                {
                vise_->closeSection( );
                throw;
                }
            }   


        void testInspectNone( )
            {
            vise_->openSection( "aSection" );
            try
                {
                vise_->inspect( );
                CPPUNIT_FAIL("expected vise exception");
                }
            catch ( Exception e )
                {
                vise_->closeSection();
                CPPUNIT_ASSERT_EQUAL( std::string( "Vise contains 0 grips\n" ),
                                      std::string( e.what( ) ) );
                }
            catch ( ... )
                {
                vise_->closeSection();
                throw;
                }
            }   


        void testNoThrowFromCloseIfAlreadyThrown( )
            {
            // record a section
            vise_->openSection( "aSection" );
            vise_->grip( makeSerializableWrapperPtr( "a" ) );
            vise_->grip( makeSerializableWrapperPtr( "b" ) );
            vise_->closeSection( );
            
            // grip a failure but leave one remaining
            vise_->openSection( "aSection" );
            try
                {
                vise_->grip( makeSerializableWrapperPtr( "c" ) );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                }
            
            // close section without an exception
            vise_->closeSection( );
            }


        void testReleaseVise( )
            {
            //   record a section
            vise_->openSection( "aSection" );
            vise_->grip( makeSerializableWrapperPtr( "a" ) );
            vise_->grip( makeSerializableWrapperPtr( "b" ) );
            vise_->closeSection( );
            
            vise_->release( );
            
            vise_->openSection( "aSection" );
            CPPUNIT_ASSERT( vise_->isRecording( ) );
            vise_->closeSection( );
            }


        void testGripWithNoOpen( )
            {
            try
                {
                vise_->grip( makeSerializableWrapperPtr( "a" ) );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL( std::string( "invalid state error: "
                                                   "grip called without a"
                                                   " call to openSection" ),
                                      std::string( e.what( ) ) );
                }
            }


        void testCloseWithNoOpen( )
            {
            try
                {
                vise_->closeSection( );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL( std::string( "invalid state error: "
                                                   "closeSection called "
                                                   "without a call to "
                                                   "openSection" ),
                                      std::string( e.what() ) );
                }
            }


        void testResetToOutsideSectionOnClose( )
            {
            try
                {
                vise_->openSection( "a" );
                vise_->closeSection( );
                vise_->grip( makeSerializableWrapperPtr( "a" ) );
                CPPUNIT_FAIL( "expected vise exception" );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL( std::string( "invalid state "
                                                   "error: grip "
                                                   "called without "
                                                   "a call to "
                                                   "openSection" ),
                                      std::string( e.what() ) );
                }
            }        


        void testGripWithLabel( )
            {
            vise_->openSection( "a" );
            vise_->grip( makeSerializableWrapperPtr( "1" ),
                         "inner loop value" );
            vise_->closeSection( );
            vise_->openSection( "a" );
            try
                {
                vise_->inspect();
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL(
                    std::string( "Vise contains 1 grip\n0: <1> inner "
                                 "loop value (0)\n" ),
                    std::string( e.what( ) ) );
                }
            vise_->grip( makeSerializableWrapperPtr( "1" ) );
            vise_->closeSection( );
            }

        
        void testGripWithAdvancingLabel( )
            {
            vise_->openSection( "a" );
            vise_->grip( makeSerializableWrapperPtr( "1" ),
                         "inner loop value" );
            vise_->grip( makeSerializableWrapperPtr( "1" ),
                         "inner loop value" );
            vise_->closeSection( );
            vise_->openSection( "a" );
            try
                {
                vise_->inspect( );
                }
            catch ( Exception e )
                {
                CPPUNIT_ASSERT_EQUAL( 
                    std::string( "Vise contains 2 grips\n" 
                                 "0: <1> inner loop value (0)\n"
                                 "1: <1> inner loop value (1)\n" ),
                    std::string( e.what() ) );
                }
            vise_->grip( makeSerializableWrapperPtr( "1" ) );
            vise_->grip( makeSerializableWrapperPtr( "1" ) );
            vise_->closeSection( );
            }


        void testFailureOfGripWithLabel( )
            {
            vise_->openSection( "a" );
            vise_->grip( makeSerializableWrapperPtr( "1" ),
                         "inner loop value" );
            vise_->closeSection( );
            vise_->openSection( "a" );
            try
                {
                vise_->grip( makeSerializableWrapperPtr( "2" ) );
                }
            catch ( Exception e )
                {
                vise_->closeSection( );
                CPPUNIT_ASSERT_EQUAL
                    ( std::string( "Vise expected grip \"inner loop "
                                   "value\" with <1> but was grip "
                                   "with <2>" ),
                      std::string( e.what( ) ) ); 
                }
            catch ( ... )
                {
                vise_->closeSection( );
                throw;
                }
                
            }
        
        };
    
    CPPUNIT_TEST_SUITE_REGISTRATION( DefaultMechanicsTest );
    }

