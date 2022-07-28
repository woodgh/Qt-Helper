#pragma once

class RibbonBar : public QDockWidget
{
public:
	class Group : public QWidget
	{
	public:
		Group(const QString& Name, QWidget* pParent = nullptr);

		virtual ~Group(void) = default;

	private:
		QVBoxLayout m_Layout;
	};

	class TabContent : public QWidget
	{
	public:
		TabContent(QWidget* pParent = nullptr);

		virtual ~TabContent(void) = default;

	public:
		Group* AddGroup(const QString& Name);

	private:
		QHBoxLayout m_Layout;
	};

	class Tabs : public QTabWidget
	{
	public:
		Tabs(QWidget* pParent = nullptr);

		virtual ~Tabs(void) = default;
	};

public:
	RibbonBar(QWidget* pParent = nullptr);

	virtual ~RibbonBar(void) = default;

public:
	TabContent* AddTab(const QString& Name);

	void RemoveTab(const QString& Name);

public:
	__forceinline QDockWidget* GetWidget(void)
	{
		return this;
	}

private:
	QGridLayout m_Layout;

	Tabs m_Ribbon;
};
