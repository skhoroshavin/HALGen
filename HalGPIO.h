
#pragma once

#include "HalDevice.h"

class HalGPIO;

class HalPins : public QObject
{
	Q_OBJECT
	Q_ENUMS(Mode)

	Q_PROPERTY( bool     isPublic     READ isPublic     WRITE setPublic       )
	Q_PROPERTY( Mode     mode         READ mode         WRITE setMode         )
	Q_PROPERTY( unsigned pinStart     READ pinStart     WRITE setPinStart     )
	Q_PROPERTY( unsigned pinCount     READ pinCount     WRITE setPinCount     )
	Q_PROPERTY( unsigned defaultState READ defaultState WRITE setDefaultState )
public:
	// Public
	inline bool isPublic() const { return m_bPublic; }
	inline void setPublic( bool bPublic ) { m_bPublic = bPublic; }

	// Mode
	enum Mode
	{
		// Output modes
		PushPull,
		OpenDrain,
		// Input modes
		HiZ,
		PullUp
	};
	inline Mode mode() const { return m_nMode; }
	inline void setMode( Mode nMode ) { m_nMode = nMode; }

	// Pin start
	inline unsigned pinStart() const { return m_nPinStart; }
	inline void setPinStart( unsigned nPinStart ) { m_nPinStart = nPinStart; }

	// Pin count
	inline unsigned pinCount() const { return m_nPinCount; }
	inline void setPinCount( unsigned nPinCount ) { m_nPinCount = nPinCount; }

	// Default state (only for output)
	inline unsigned defaultState() const { return m_nDefaultState; }
	inline void setDefaultState( unsigned nState ) { m_nDefaultState = nState; }

	// Utility
	inline unsigned mask() const { return ((1 << m_nPinCount)-1) << m_nPinStart; }
	QString encode( const QString& sVar ) const;
	QString decode( const QString& sVar ) const;

private:
	bool     m_bPublic       = false;
	Mode     m_nMode         = HiZ;
	unsigned m_nPinStart     = 0;
	unsigned m_nPinCount     = 1;
	unsigned m_nDefaultState = 0;

	explicit HalPins( HalGPIO * pParent );
	friend class HalGPIO;
};

class HalGPIO : public HalDevice
{
	Q_OBJECT
public:
	explicit HalGPIO( QObject * pParent );

	inline const QList<HalPins*>& pins() const { return m_Pins; }
	HalPins * accessPins( const QString& sName ) const;
	HalPins * queryPins( const QString& sName );

private:
	QList<HalPins*> m_Pins;
};
