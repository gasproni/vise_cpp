#ifndef VISE_PLATFORM_H
#define VISE_PLATFORM_H

#ifdef _WIN32

#    ifdef VISE_EXPORT
#        define VISE_API __declspec(dllexport)
#    else
#        define VISE_API __declspec(dllimport)
#    endif
#else

#    define VISE_API

#endif

#endif
