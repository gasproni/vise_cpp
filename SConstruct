
import os
import os.path
import platform

# Put the appropriate paths in the next four lines.
boostInclude = r'/Users/giovanni/Development/boost/build/include'
boostLib = r'/Users/giovanni/Development/boost/build/lib'
cppUnitInclude = r'/Users/giovanni/Development/cppunit/build/include'
cppUnitLib = r'/Users/giovanni/Development/cppunit/build/lib'

rootDir = os.path.abspath( '.' )

libDir = os.path.join( rootDir, 'lib' )
binDir = os.path.join( rootDir, 'bin' )

cppIncludes = [ cppUnitInclude,
                boostInclude,
                os.path.join( rootDir, 'include' ),
                os.path.join( rootDir, 'src' ),
                os.path.join( rootDir,'test' ) ]

cppLibPath = [ cppUnitLib,
               boostLib,
               libDir ]


env = Environment( ENV = os.environ,
                   CPPPATH = cppIncludes,
                   LIBPATH = cppLibPath )

if platform.system( ) == 'Windows' :
    env.Append( CPPFLAGS = '/nologo /Od /Ob1 /EHsc /MD' + \
                ' /W3 /GR /TP /DWIN32 /D_USRDLL ' + \
                ' /wd4996 /D "_WINDOWS"' )
else :
    env.Append( CPPFLAGS = ' -pthread' )

env[ 'VISE_LIB_DIR' ] = libDir
env[ 'VISE_BIN_DIR' ] = binDir
env[ 'BOOST_LIBS' ] = [ ]
if platform.system( ) != 'Windows' :
    env[ 'BOOST_LIBS' ] = [ 'boost_serialization',
                            'boost_filesystem',
                            'boost_system']

Export( 'env' )


SConscript( 'src/vise/SConscript',
            exports='env',
            variant_dir = 'obj/vise',
            duplicate = 0 )

SConscript( 'test/vise/SConscript',
            exports='env',
            variant_dir = 'obj/vise_test',
            duplicate = 0 )

SConscript( 'examples/SConscript',
            exports='env',
            variant_dir = 'obj/examples',
            duplicate = 0 )
