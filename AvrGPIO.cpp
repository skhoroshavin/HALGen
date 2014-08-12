
#include "AvrGPIO.h"

#include <QDebug>

AvrGPIO::AvrGPIO( const QString& sPortName, QObject * pParent ) : HalGPIO(pParent)
{
	setObjectName( sPortName );
}

void AvrGPIO::generateHeader( QTextStream& s ) const
{
	for( HalPins * pPins : pins() )
	{
		if( pPins->mode() < HalPins::HiZ )
		{
			QString sReg = pPins->mode() == HalPins::PushPull ? "PORT" : "DDR";
			sReg += objectName();

			QString sOffset;
			if( pPins->pinStart() > 0 ) sOffset = " << " + QString::number(pPins->pinStart());

			s << "inline " << pPins->objectName() << "_write( uint8_t value ) { " << sReg << " = (value" << sOffset << "); }\n";
		}
		s << "\n";
	}

}

void AvrGPIO::generateSource( QTextStream& ) const
{

}

void AvrGPIO::generateStartup( QTextStream& s ) const
{
	unsigned nPORT = 0;
	unsigned nDDR  = 0;

	for( HalPins * pPins : pins() )
	{
		unsigned state = pPins->defaultState() << pPins->pinStart();

		switch( pPins->mode() )
		{
		case HalPins::PushPull:
			nDDR  |= pPins->mask();
			nPORT |= state;
			break;
		case HalPins::OpenDrain:
			nDDR  |= ~state & pPins->mask();
			break;
		case HalPins::HiZ:
			break;
		case HalPins::PullUp:
			nPORT |= pPins->mask();
		}
	}

	s.setIntegerBase( 16 );
	s << "	PORT" << objectName() << " = 0x" << nPORT << ";\n";
	s << "	DDR" << objectName() << "  = 0x" << nDDR  << ";\n";
	s << "\n";
}
