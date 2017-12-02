// Qt
#include <QApplication>

#include <iostream>
#include <coords/ll.h>
#include <coords/tile.h>
#include <coords/lla.h>


using namespace maptiles;

int main(int argc, char* argv[]) {

	// Set Locale to use points as decimal separator
#ifdef _WIN32
	setlocale(LC_NUMERIC, "en_US.UTF-8");
#else
	setenv("LC_NUMERIC", "en_US.UTF-8", 1);
#endif

  QApplication app(argc, argv);
  // app.setOrganizationName(COMPANY_NAME);
  // app.setApplicationName(APP_NAME);
  // app.setWindowIcon(QIcon(MAPP_ICON_APP));
  app.setAttribute(Qt::AA_UseHighDpiPixmaps);




	{

		// TEST
		coords::ll initial = coords::ll::fromDeg(38.0, -7.0);
		coords::lla withAlt(initial, 100.0);
		coords::tile t(initial, 15);
		coords::tile t2(t.x(), t.y(), t.z());


		std::cout << "Initial " << initial.lat() << " " << initial.lon() << std::endl;
		std::cout << "Initial Deg " << initial.latDeg() << " " << initial.lonDeg() << std::endl;
		std::cout << "Initial Alt " << withAlt.latDeg() << " " << withAlt.lonDeg() << " " << withAlt.alt() << std::endl;

		std::cout << "Tile " << t.x() << " " << t.y() << " " << t.z() << " " <<
			t.world().latDeg() << " " << t.world().lonDeg() << std::endl;
		std::cout << "Tile " << t2.x() << " " << t2.y() << " " << t2.z() << " " <<
			t2.world().latDeg() << " " << t2.world().lonDeg() << std::endl;

	}

	return app.exec();

}
