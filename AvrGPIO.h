
#pragma once

#include "HalGPIO.h"
#include "CodeGenerator.h"

class AvrGPIO : public HalGPIO
{
public:
	explicit AvrGPIO( const QString& sPortName, QObject * pParent );

protected:
	virtual void generateHeader( QTextStream& s ) const;
	virtual void generateStartup( QTextStream& s ) const;

private:
	static CodeGenerator s_codeGen;
};
