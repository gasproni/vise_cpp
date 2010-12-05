#ifndef VISE_FILEBASEDSTORE_H
#define VISE_FILEBASEDSTORE_H


#include "vise/Platform.h"
#include <string>
#include <boost/filesystem/operations.hpp> // includes boost/filesystem/path.hpp
#include <boost/filesystem/fstream.hpp>
#include "vise/SectionStore.h"




namespace vise
    {
    class VISE_API FileBasedStore : public SectionStore
        {
    public:

	static const std::string FILE_SUFFIX; // == ".vise"
	
	FileBasedStore( const std::string& directoryBase = "." )
	    : directoryBase_( directoryBase )
	    {
	    }
	

        virtual bool hasSection( const std::string& sectionName ) const
	    {
	    return boost::filesystem::exists( fileName( sectionName ) );
	    }


        virtual void saveSection( const std::string& sectionName,
				  const SerializableList& values )
	    {
	    std::ofstream archiveStream( fileName( sectionName ).
					 string( ).c_str( ) );
	    boost::archive::text_oarchive oa( archiveStream );
	    oa << values;
	    }


        virtual void retrieveSection( const std::string& sectionName,
				      SerializableList& result ) const
	    {
	    std::ifstream archiveStream( fileName( sectionName ).
					 string( ).c_str( ) );
	    boost::archive::text_iarchive ia( archiveStream );

	    ia >> result;
	    }


        virtual std::size_t size( const std::string& sectionName ) const
	    {
	    SerializableList resultHolder;
	    retrieveSection( sectionName, resultHolder );
	    return resultHolder.size( );
	    }


        virtual void clear( )
	    {
	    boost::filesystem::directory_iterator endIt;
	    for ( boost::filesystem::directory_iterator dirIt( directoryBase_ );
		  dirIt != endIt;
		  ++dirIt )
		{
		if ( ( *dirIt ).string( ).rfind( FILE_SUFFIX ) !=
		    std::string::npos )
		    {
		    boost::filesystem::remove( *dirIt );
		    }
		}
	    }


    private:


	boost::filesystem::path fileName( const std::string&
					  sectionName ) const
	    {
	    return directoryBase_ / 
		boost::filesystem::path( sectionName + FILE_SUFFIX );
	    }


	boost::filesystem::path directoryBase_;

        };

    }


#endif
