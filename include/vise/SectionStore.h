#ifndef VISE_SECTIONSTORE_H
#define VISE_SECTIONSTORE_H


#include "vise/Platform.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include "vise/SerializableList.h"




namespace vise
    {


    class VISE_API SectionStore
        {

    public:

        virtual ~SectionStore( )
            {
            }


        virtual bool hasSection( const std::string& sectionName ) const = 0;

        virtual void saveSection( const std::string& sectionName,
				  const SerializableList& values ) = 0;

        virtual void retrieveSection( const std::string& sectionName,
				      SerializableList& result ) const = 0;

        virtual std::size_t size( const std::string& sectionName ) const = 0;

        virtual void clear( ) = 0;

        };

    typedef boost::shared_ptr< SectionStore > SectionStorePtr;
    }


#endif
