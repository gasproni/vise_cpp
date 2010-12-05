#include "vise/Vise.h"
#include "vise/SectionStore.h"
#include "vise/FileBasedStore.h"
#include "vise/DefaultMechanics.h"




vise::MechanicsPtr
vise::Vise::s_mechanics( new vise::DefaultMechanics
			 ( vise::SectionStorePtr
			   ( new vise::FileBasedStore( ) ) ) );
