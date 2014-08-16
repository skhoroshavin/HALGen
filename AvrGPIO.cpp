
#include "AvrGPIO.h"

CodeGenerator AvrGPIO::s_codeGen = CodeGenerator(":/_AvrGPIO.h");

AvrGPIO::AvrGPIO( const QString& sPortName, QObject * pParent ) : HalGPIO(pParent)
{
	setObjectName( sPortName );
}

void AvrGPIO::generateHeader( QTextStream& s ) const
{
	for( HalPins * pPins : pins() )
	{
		QVariantHash var;
		var["NAME"] = pPins->objectName();
		var["CLEARMASK"] = "0x" + QString::number( ~pPins->mask() & 0xff, 16 );

		if( pPins->mode() < HalPins::HiZ )
		{
			var["HAS_OUTPUT"] = true;
			var["OUTREG"]     = (pPins->mode() == HalPins::PushPull ? "PORT" : "DDR") + objectName();
			var["OUTPUT"]     = pPins->encode( "v" );
		}

		if( pPins->mode() > HalPins::PushPull )
		{
			var["HAS_INPUT"] = true;
			var["INPUT"] = pPins->decode( "PIN" + objectName() );
		}

		s_codeGen.generate( s, var );
	}
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
