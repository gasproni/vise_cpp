#ifndef VISE_SERIALIZABLELIST_H
#define VISE_SERIALIZABLELIST_H


#include "vise/Platform.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <list>

#include "vise/RecordedGrip.h"
#include "vise/Export.h"




namespace vise
    {
    typedef VISE_API std::list< RecordedGrip > SerializableList;
    }

#endif
