
#pragma once

#include <QTextStream>
#include <QObject>

class HalDevice : public QObject
{
	Q_OBJECT
public:
	explicit HalDevice( QObject * pParent );

	// Block state
	inline bool isActive() const { return m_bActive; }
	inline void activate() { m_bActive = true; }

	// Public state
	inline bool isPublic() const { return m_bPublic; }
	inline void makePublic() { activate(); m_bPublic = true; }

	// Generate code
	enum Section
	{
		HEADER,
		SOURCE,
		STARTUP
	};
	void generate( QTextStream& s, Section nSection ) const;

protected:
	// Generators
	virtual void generateHeader( QTextStream& ) const { }
	virtual void generateSource( QTextStream& ) const { }
	virtual void generateStartup( QTextStream& ) const { }

private:
	bool m_bActive = false;
	bool m_bPublic = false;
};
