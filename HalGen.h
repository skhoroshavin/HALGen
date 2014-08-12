
#pragma once

#include <QVector>

#include "HalDevice.h"

class HalGen
{
public:
	explicit HalGen( const QString& sFileName );

	int process();

private:
	QString m_sJSONName;

	QString m_sName;
	QString m_sHeaderName;
	QString m_sSourceName;
	void prepare();

	void generateHeader();
	void generateSource();

	QVector<HalDevice*> m_Devices;
};
