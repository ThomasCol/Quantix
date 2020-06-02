#ifndef __SOUNDMODE_H__
#define __SOUNDMODE_H__

#include <fmod_common.h>

namespace Quantix::Core
{
	typedef unsigned int QXSoundMode;

	#define QX_SOUNDMODE_DEFAULT						FMOD_DEFAULT
	#define	QX_SOUNDMODE_LOOPOFF						FMOD_LOOP_OFF                               
	#define	QX_SOUNDMODE_LOOPNORMAL						FMOD_LOOP_NORMAL                            
	#define	QX_SOUNDMODE_LOOPBIDI						FMOD_LOOP_BIDI                              
	#define	QX_SOUNDMODE_2D								FMOD_2D                                     
	#define	QX_SOUNDMODE_3D								FMOD_3D                                     
	#define	QX_SOUNDMODE_CREATESTREAM					FMOD_CREATESTREAM                           
	#define	QX_SOUNDMODE_CREATESAMPLE					FMOD_CREATESAMPLE                           
	#define	QX_SOUNDMODE_CREATECOMPRESSEDSAMPLE			FMOD_CREATECOMPRESSEDSAMPLE                 
	#define	QX_SOUNDMODE_OPENUSER						FMOD_OPENUSER                               
	#define	QX_SOUNDMODE_OPENMEMORY						FMOD_OPENMEMORY                             
	#define	QX_SOUNDMODE_OPENMEMORYPOINT				FMOD_OPENMEMORY_POINT                       
	#define	QX_SOUNDMODE_OPENRAW						FMOD_OPENRAW                                
	#define	QX_SOUNDMODE_OPENONLY						FMOD_OPENONLY                               
	#define	QX_SOUNDMODE_ACURRATETIME					FMOD_ACCURATETIME                           
	#define	QX_SOUNDMODE_MPEGSEARCH						FMOD_MPEGSEARCH                             
	#define	QX_SOUNDMODE_NONBLOCKING					FMOD_NONBLOCKING                            
	#define	QX_SOUNDMODE_UNIQUE							FMOD_UNIQUE                                 
	#define	QX_SOUNDMODE_3DHEADRELATIVE					FMOD_3D_HEADRELATIVE                        
	#define	QX_SOUNDMODE_3DWORLDRELATIVE				FMOD_3D_WORLDRELATIVE                       
	#define	QX_SOUNDMODE_3DINVERSEROLLOFF				FMOD_3D_INVERSEROLLOFF                      
	#define	QX_SOUNDMODE_3DLINEARROLLOFF				FMOD_3D_LINEARROLLOFF                       
	#define	QX_SOUNDMODE_3DLINEARSQUAREROLLOFF			FMOD_3D_LINEARSQUAREROLLOFF                 
	#define	QX_SOUNDMODE_3DINVERSETAPEREDROLLOFF		FMOD_3D_INVERSETAPEREDROLLOFF               
	#define	QX_SOUNDMODE_3DCUSTOMROLLOFF				FMOD_3D_CUSTOMROLLOFF                       
	#define	QX_SOUNDMODE_3DIGNOREGEOMETRY				FMOD_3D_IGNOREGEOMETRY                      
	#define	QX_SOUNDMODE_IGNORETAGS						FMOD_IGNORETAGS                             
	#define	QX_SOUNDMODE_LOWMEM							FMOD_LOWMEM                                 
	#define	QX_SOUNDMODE_VIRTUALPLAYFROMSTART			FMOD_VIRTUAL_PLAYFROMSTART                  
}
#endif __SOUNDMODE_H___