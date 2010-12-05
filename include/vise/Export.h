
#ifndef VISE_EXPORT_H
#define VISE_EXPORT_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#define VISE_CLASS_EXPORT( x ) BOOST_CLASS_EXPORT( x )

#define VISE_IS_ABSTRACT( x ) BOOST_SERIALIZATION_ASSUME_ABSTRACT( x )


#endif // VISE_EXPORT_H
