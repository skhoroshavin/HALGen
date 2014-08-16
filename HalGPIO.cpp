
#include "HalGPIO.h"

HalPins::HalPins( HalGPIO * pParent ) : QObject(pParent) { }

QString HalPins::encode( const QString& sVar ) const
{
	return pinStart() > 0 ? "(" + sVar + " << " + QString::number(pinStart()) + ")" : sVar;
}

QString HalPins::decode( const QString& sVar ) const
{
	QString sRes = sVar + " & 0x" + QString::number( mask(), 16 );
	if( pinStart() > 0 ) sRes = "((" + sRes + ") >> " + QString::number(pinStart()) + ")";
	return sRes;
}

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
