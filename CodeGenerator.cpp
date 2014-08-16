
#include "CodeGenerator.h"

#include <QFile>
#include <QStack>
#include <QDebug>

void CodeGenerator::generate( QTextStream& s, const QVariantHash& var )
{
	prepare();

	int nPosition = 0;
	while( nPosition < m_Commands.size() )
	{
		const Cmd& cmd = m_Commands[nPosition];
		if( cmd.nTarget < 0 )
		{
			QString sLine = cmd.sValue;
			for( auto i = var.begin(); i != var.end(); ++i )
				sLine.replace( "$" + i.key() + "$", i.value().toString() );
			s << sLine;
			++nPosition;
		}
		else
		{
			if( !var.value(cmd.sValue).toInt() )
				nPosition = cmd.nTarget;
			else
				++nPosition;
		}
	}
}

void CodeGenerator::prepare()
{
	if( m_bReady ) return;

	QFile file(m_sResourceName);
	if( !file.open( QIODevice::Text | QIODevice::ReadOnly ) )
		qFatal( "Failed to open file %s!", qPrintable(m_sResourceName) );

	QStack<int> jumpStack;
	while( !file.atEnd() )
	{
		QString sLine = QString::fromUtf8( file.readLine() );

		if( sLine.startsWith( "#if" ) )
		{
			// Save last jump source address
			jumpStack.push( m_Commands.size() );
			// Append conditional jump to command list
			m_Commands.append( Cmd( sLine.remove(0,3).trimmed() ) );
		}
		else if( sLine.startsWith( "#else" ) )
		{
			// Check if we have jump
			Q_ASSERT( !jumpStack.empty() );
			// Get last jump source address
			int& lastJump = jumpStack.back();
			// Check if jump is conditional
			Q_ASSERT( !m_Commands[lastJump].sValue.isEmpty() );
			// Set last jump destination address
			m_Commands[lastJump].nTarget = m_Commands.size()+1;
			// Update last jump source address
			lastJump = m_Commands.size();
			// Append unconditional jump to command list
			m_Commands.append( Cmd() );
		}
		else if( sLine.startsWith( "#endif" ) )
		{
			// Check if we have jump
			Q_ASSERT( !jumpStack.empty() );
			// Get last jump source address
			int lastCondition = jumpStack.back();
			// Set last jump destination address
			m_Commands[lastCondition].nTarget = m_Commands.size();
			// Delete last jump source address
			jumpStack.pop();
		}
		else
		{
			// Add command
			m_Commands.append( Cmd( sLine ) );
		}
	}

	// Check if we have any jumps left
	Q_ASSERT( jumpStack.isEmpty() );

	m_bReady = true;
}
