
#include "FileUtils.h"

#include <QDebug>
#include <QFile>

QJsonDocument openJSONFile( const QString& sFileName )
{
	QFile file( sFileName );
	if( !file.open( QIODevice::Text | QIODevice::ReadOnly ) )
	{
		qDebug() << "Failed to open file:" << sFileName;
		return QJsonDocument();
	}

	QByteArray data = file.readAll();
	QJsonParseError jsRes;
	QJsonDocument jsDoc = QJsonDocument::fromJson( data, &jsRes );
	if( jsRes.error != QJsonParseError::NoError )
	{
		qDebug() << "Failed to parse JSON:" << sFileName;
		qDebug() << jsRes.errorString();
		return QJsonDocument();
	}

	return jsDoc;
}
