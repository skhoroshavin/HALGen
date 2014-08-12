
#pragma once

#include "HalGPIO.h"

class AvrGPIO : public HalGPIO
{
public:
	explicit AvrGPIO( const QString& sPortName, QObject * pParent );

protected:
	virtual void generateHeader( QTextStream& s ) const;
	virtual void generateSource( QTextStream& s ) const;
	virtual void generateStartup( QTextStream& s ) const;


};
