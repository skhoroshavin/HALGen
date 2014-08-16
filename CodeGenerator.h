
#pragma once

#include <QVariant>
#include <QVector>
#include <QTextStream>

class CodeGenerator
{
public:
	inline explicit CodeGenerator( const QString& sResourceName ) : m_sResourceName(sResourceName) { }

	void generate( QTextStream& s, const QVariantHash& var );

private:
	QString m_sResourceName;
	bool m_bReady = false;

	void prepare();

	// Commands
	struct Cmd
	{
		QString sValue;         // Line: Value, Jump: Not Condition
		int     nTarget = -1;	// Line: -1,    Jump: Target

		inline explicit Cmd( const QString& s = QString() ) : sValue(s) { }
	};
	QVector<Cmd> m_Commands;
};
