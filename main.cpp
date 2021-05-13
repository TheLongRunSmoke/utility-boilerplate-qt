#include <QtWidgets/QApplication>
#include "utility_boilerplate_qt5/helpers.hpp"
#include "mainwindow.hpp"

int main(int argc, char *argv[]){
	// Load app resources.
	Q_INIT_RESOURCE(utility_boilerplate_qt);
	// Set you own app name and version here.
	QCoreApplication::setApplicationName("Utility Boilerplate Qt");
	QCoreApplication::setApplicationVersion("1.0");
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
	// Create normal Qt application class.
	QApplication app(argc, argv);
	// Parse command line arguments.
	QStringList arguments = UBHelpers::parseFirstArgumentAsFile(app);
	// Create main window.
	MainWindow mainWin;
	// Do something, if has args.
	//if (!arguments.isEmpty())
	//    mainWin.loadFile(arguments.first());
	mainWin.show();
	return app.exec();
}
