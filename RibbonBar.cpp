#include "Pch.h"
#include "RibbonBar.h"

RibbonBar::Group* RibbonBar::TabContent::AddGroup(const QString& Name)
{
	auto* pGroup = new Group(Name);
	if (pGroup != nullptr)
	{
		m_Layout.addWidget(pGroup);
	}

	return pGroup;
}

RibbonBar::Group::Group(const QString& Name, QWidget* pParent)
	: QWidget(pParent)
{
	auto* pHLayout = new QHBoxLayout;
	if (pHLayout != nullptr)
	{
		pHLayout->setContentsMargins({ 2, 2, 2, 2 });
		pHLayout->addLayout(&m_Layout);
	}

	auto* pGroupLine = new QFrame;
	if (pGroupLine != nullptr)
	{
		pGroupLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
		pGroupLine->setFrameShape(QFrame::Shape::VLine);
		pGroupLine->setFrameShadow(QFrame::Shadow::Sunken);
		pGroupLine->setLineWidth(1);
		pGroupLine->setMidLineWidth(0);

		if (pHLayout != nullptr)
		{
			pHLayout->addWidget(pGroupLine);
		}
	}

	auto* pWidget = new QWidget;
	if (pWidget != nullptr)
	{
		//pWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

		m_Layout.addWidget(pWidget);
	}

	auto* pHLine = new QFrame;
	if (pHLine != nullptr)
	{
		pHLine ->setFrameShape(QFrame::Shape::HLine);
		pHLine ->setFrameShadow(QFrame::Shadow::Sunken);
		pHLine ->setLineWidth(1);
		pHLine ->setMidLineWidth(0);

		m_Layout.addWidget(pHLine);
	}

	auto* pLabel = new QLabel;
	if (pLabel != nullptr)
	{
		pLabel->setText(Name);
		pLabel->setTextFormat(Qt::TextFormat::AutoText);
		pLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		pLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
		pLabel->setGeometry({ 2, 19, 143, 10 });
		pLabel->setFrameShape(QFrame::Shape::NoFrame);
		pLabel->setFrameShadow(QFrame::Shadow::Plain);
		pLabel->setLineWidth(1);
		pLabel->setMidLineWidth(0);

		m_Layout.addWidget(pLabel);
	}

	m_Layout.setSizeConstraint(QLayout::SetDefaultConstraint);
	m_Layout.setMargin(0);

	setLayout(pHLayout);
}

RibbonBar::TabContent::TabContent(QWidget* pParent)
	: QWidget(pParent)
{
	auto* pTabContentLayout = new QGridLayout;
	if (pTabContentLayout != nullptr)
	{
		pTabContentLayout->setMargin(0);
		pTabContentLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);

		setLayout(pTabContentLayout);
	}

	auto* pScrollArea = new QScrollArea;
	if (pScrollArea != nullptr)
	{
		pScrollArea->setFrameShape(QFrame::Shape::NoFrame);
		pScrollArea->setFrameShadow(QFrame::Shadow::Plain);
		pScrollArea->setLineWidth(0);

		if (pTabContentLayout != nullptr)
		{
			pTabContentLayout->addWidget(pScrollArea);
		}
	}

	auto* pScrollAreaLayout = new QGridLayout;
	if (pScrollAreaLayout != nullptr)
	{
		pScrollAreaLayout->setMargin(0);
		pScrollAreaLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);

		if (pScrollArea != nullptr)
		{
			pScrollArea->setLayout(pScrollAreaLayout);
		}
	}

	if (pScrollAreaLayout != nullptr)
	{
		m_Layout.setMargin(6);

		pScrollAreaLayout->addLayout(&m_Layout, 0, 0);
	}

	auto* pSpeacer = new QWidget;
	if (pSpeacer != nullptr)
	{
		pSpeacer->setGeometry(0, 0, 398, 90);
		pSpeacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

		if (pScrollAreaLayout != nullptr)
		{
			pScrollAreaLayout->addWidget(pSpeacer, 0, 1);
		}
	}
}

RibbonBar::Tabs::Tabs(QWidget* pParent)
	: QTabWidget(pParent)
{
	setIconSize({ 16, 16 });
	setAutoFillBackground(true);

	QColor bg = qApp->palette().color(QPalette::Window);
	QColor mid = qApp->palette().color(QPalette::Mid);

	QString styleSheetText = QString(
								 "QTabWidget::pane {"
								 "  border-top: 1px solid rgb(%4, %5, %6);"
								 "  position: absolute;"
								 "  top: -1px;"
								 "}"
								 ""
								 "QTabBar::tab {"
								 "  padding-top: 5px;"
								 "  padding-bottom: 5px;"
								 "  padding-left: 10px;"
								 "  padding-right: 10px;"
								 "  margin-top: 1px;"
								 "}"
								 ""
								 "QTabBar::tab::!selected {"
								 "  border-bottom: 1px solid rgb(%4, %5, %6);"
								 "  background-color:#ffffff;"
								 "}"
								 ""
								 "QTabBar::tab:selected {"
								 "  background-color: rgb(%1, %2, %3);"
								 "  border-top: 1px solid rgb(%4, %5, %6);"
								 "  border-right: 1px solid rgb(%4, %5, %6);"
								 "  border-left: 1px solid rgb(%4, %5, %6);"
								 "  border-bottom: 1px solid rgb(%1, %2, %3);"
								 "}"
								 ""
								 "QTabBar::tab:hover"
								 "{"
								 "  background-color: rgb(205, 232, 255);"
								 "}"
								 ""
								 "QTabBar::tab:selected:hover {"
								 "  background-color: rgb(%1, %2, %3);"
								 "}"
							 ).arg(bg.red()).arg(bg.green()).arg(bg.blue())
							 .arg(mid.red()).arg(mid.green()).arg(mid.blue());

	setStyleSheet(styleSheetText);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::white);
	setPalette(pal);
}

RibbonBar::RibbonBar(QWidget* pParent)
	: QDockWidget(pParent)
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);
	setAllowedAreas(Qt::TopDockWidgetArea);
	setTitleBarWidget(new QWidget());

	auto* pWidget = new QWidget;
	if (pWidget != nullptr)
	{
		pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

		setWidget(pWidget);
	}

	m_Layout.setMargin(0);
	m_Layout.setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
	m_Layout.addWidget(&m_Ribbon);

	if (pWidget != nullptr)
	{
		pWidget->setLayout(&m_Layout);
	}

	auto* pHeadTab = new TabContent(&m_Ribbon);
	if (pHeadTab != nullptr)
	{
		m_Ribbon.addTab(pHeadTab, "");
	}

	m_Ribbon.setTabEnabled(0, false);
}

RibbonBar::TabContent* RibbonBar::AddTab(const QString& Name)
{
	auto AddTabContent = new TabContent(&m_Ribbon);
	if (AddTabContent != nullptr)
	{
		m_Ribbon.addTab(AddTabContent, Name);
	}

	m_Ribbon.setTabEnabled(0, false);

	return AddTabContent;
}

void RibbonBar::RemoveTab(const QString& Name)
{
	for (int Index = 0; Index < m_Ribbon.count(); ++Index)
	{
		if (m_Ribbon.tabText(Index).toLower() != Name.toLower())
		{
			continue;
		}

		QWidget* RemoveTab = m_Ribbon.widget(Index);
		if (RemoveTab != nullptr)
		{
			continue;
		}

		m_Ribbon.removeTab(Index);
		delete RemoveTab;
		break;
	}
}
