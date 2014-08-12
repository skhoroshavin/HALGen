
#include "FileUtils.h"
#include "HalGen.h"

#include <QDebug>

int main( int argc, char *argv[] )
{
	qDebug() << "HAL code generator";
	if( argc < 2 )
	{
		qDebug() << "Usage:";
		qDebug() << "    HALGen <filename>";
		return 1;
	}

	HalGen halGen( argv[1] );
	return halGen.process();
}
