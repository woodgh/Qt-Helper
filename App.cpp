#include "Pch.h"
#include "RibbonBar.h"
#include "WindowManager.h"

#define Locale(Str)\
	QString::fromLocal8Bit(Str)

class MainWindow : public QMainWindow
{
public:
	MainWindow(void)
		: m_pRibbonBar(std::make_unique< class RibbonBar >(this))
		, m_pWindowManager(std::make_unique< class WindowManager >(this))
		, m_statusBar(this)
	{
		addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, m_pRibbonBar->GetWidget());
		{
			auto* pServerTab = m_pRibbonBar->AddTab(Locale("일반"));
			if (pServerTab != nullptr)
			{
				pServerTab->AddGroup(Locale("접속"));
				pServerTab->AddGroup(Locale("봇"));
				pServerTab->AddGroup(Locale("기타"));
				pServerTab->AddGroup(Locale("정보"));
			}

			auto* pCheatTab = m_pRibbonBar->AddTab(Locale("치트"));
			if (pCheatTab != nullptr)
			{
				pCheatTab->AddGroup(Locale("치트 정보"));
			}
		}

		setCentralWidget(m_pWindowManager->GetWidget());

		setStatusBar(&m_statusBar);
	}

	virtual ~MainWindow(void) = default;

private:
	std::unique_ptr< class RibbonBar > m_pRibbonBar = nullptr;

	std::unique_ptr< class WindowManager > m_pWindowManager = nullptr;

	QStatusBar m_statusBar;
};

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	MainWindow Window;

	Window.resize(1024, 768);
	Window.setWindowTitle("TestApp");
	Window.show();

	return app.exec();
}
