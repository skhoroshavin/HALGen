
#include "HalGPIO.h"

HalPins::HalPins( HalGPIO * pParent ) : QObject(pParent) { }

HalGPIO::HalGPIO( QObject * pParent ) : HalDevice(pParent) { }

HalPins * HalGPIO::accessPins( const QString& sName ) const
{
	return findChild<HalPins*>( sName, Qt::FindDirectChildrenOnly );
}

HalPins * HalGPIO::queryPins( const QString& sName )
{
	HalPins * pResult = accessPins( sName );
	if( !pResult )
	{
		pResult = new HalPins( this );
		pResult->setObjectName( sName );
		m_Pins.push_back( pResult );
	}
	return pResult;
}
