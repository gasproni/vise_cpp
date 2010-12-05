#ifndef VISE_SERIALIZABLEEXPORTS_H
#define VISE_SERIALIZABLEEXPORTS_H

// When under windows Must be included at the end of the Serializable.h file,
// otherwise must be included in the Serializable.cpp one

VISE_CLASS_EXPORT( vise::Serializable );

VISE_CLASS_EXPORT( vise::SerializableWrapper< char > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< unsigned char > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< signed char > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< short > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< unsigned short > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< int > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< unsigned int > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< long > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< unsigned long > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< bool > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< float > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< double > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< long double > );

VISE_CLASS_EXPORT( vise::SerializableWrapper< std::string > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< char* > );
VISE_CLASS_EXPORT( vise::SerializableWrapper< const char* > );

#endif
