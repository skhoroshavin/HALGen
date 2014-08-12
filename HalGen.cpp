
#include "HalGen.h"

#include "AvrGPIO.h"

#include <QFile>
#include <QFileInfo>

HalGen::HalGen( const QString& sFileName ) : m_sJSONName(sFileName) { }

int HalGen::process()
{
	m_Devices.push_back( new AvrGPIO( "A", 0 ) );
	m_Devices.push_back( new AvrGPIO( "B", 0 ) );

	HalGPIO * pPortA = qobject_cast<HalGPIO*>( m_Devices[0] );

	HalPins * pLED = pPortA->queryPins( "LED" );
	pLED->setMode( HalPins::PushPull );
	pLED->setPinStart( 2 );

	for( HalDevice * pDevice : m_Devices )
		pDevice->makePublic();

	prepare();
	generateHeader();
	generateSource();
	return 0;
}

void HalGen::prepare()
{
	QFileInfo fileInfo(m_sJSONName);
	m_sName = fileInfo.baseName();

	QString sPath = fileInfo.absolutePath();
	QString sFullName = sPath + "/" + m_sName;
	m_sHeaderName = sFullName + ".h";
	m_sSourceName = sFullName + ".c";
}

void HalGen::generateHeader()
{
	QString sGuardName = "__" + m_sName.toUpper() + "_H__";

	QFile file( m_sHeaderName );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
		qFatal( "Failed to open file %s for writing", qPrintable( m_sHeaderName ) );
	QTextStream s( &file );

	s << "#ifndef " << sGuardName << "\n";
	s << "#define " << sGuardName << "\n";
	s << "\n";

	for( HalDevice * pBlock : m_Devices )
		pBlock->generate( s, HalDevice::HEADER );

	s << "void initialize_hal();\n";
	s << "\n";

	s << "#endif /* " << sGuardName << " */\n";
}

void HalGen::generateSource()
{
	QFile file( m_sSourceName );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
		qFatal( "Failed to open file %s for writing", qPrintable( m_sSourceName ) );
	QTextStream s( &file );

	s << "\n";
	s << "#include \"" << m_sName << ".h\"\n";
	s << "\n";

	for( HalDevice * pBlock : m_Devices )
		pBlock->generate( s, HalDevice::SOURCE );

	s << "void initialize_hal()\n";
	s << "{\n";

	for( HalDevice * pBlock : m_Devices )
		pBlock->generate( s, HalDevice::STARTUP );

	s << "}\n";
	s << "\n";
}
