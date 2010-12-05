#ifndef VISE_FAKESECTIONSTORE_H
#define VISE_FAKESECTIONSTORE_H


#include <map>
#include <string>
#include "vise/SectionStore.h"
#include "vise/SerializableList.h"




namespace vise
    {
    
    class FakeSectionStore : public SectionStore
	{

	typedef std::map< std::string, SerializableList > SectionMap;

    public:


        virtual bool hasSection( const std::string& sectionName ) const
	    {
	    return sections_.find( sectionName ) != sections_.end( );
	    }


        virtual void saveSection( const std::string& sectionName,
				  const SerializableList& values )
	    {
	    sections_[ sectionName ] = values;
	    }


        virtual void retrieveSection( const std::string& sectionName,
				      SerializableList& result ) const
	    {
	    SectionMap::const_iterator resultHolder =
		sections_.find( sectionName );
	    
	    if ( resultHolder != sections_.end( ) )
		{
		result = resultHolder->second;
		}
	    }


        virtual std::size_t size( const std::string& sectionName ) const
	    {	    

	    SectionMap::const_iterator resultHolder =
		sections_.find( sectionName );

	    if ( resultHolder != sections_.end( ) )
		{
		return ( resultHolder->second ).size( );
		}
	    return 0;
	    }


        virtual void clear( )
	    {
	    sections_.clear( );
	    }

    private:

	SectionMap sections_;
	};

    }



#endif
