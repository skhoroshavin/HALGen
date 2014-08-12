
#include "HalDevice.h"

HalDevice::HalDevice( QObject * pParent ) : QObject(pParent)
{

}

void HalDevice::generate( QTextStream& s, Section nSection ) const
{
	if( !m_bActive ) return;

	switch( nSection )
	{
	case HEADER:
		if( m_bPublic ) generateHeader( s );
		break;
	case SOURCE:
		if( !m_bPublic ) generateHeader( s );
		generateSource( s );
		break;
	case STARTUP:
		generateStartup( s );
		break;
	}

	for( HalDevice * pBlock : findChildren<HalDevice*>() )
		pBlock->generate( s, nSection );
}
