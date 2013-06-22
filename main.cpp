/*
 * Copyright 2008 Arthur Renato Mello <arthur@mandriva.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <QApplication>
#include <QSettings>

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include "mandrivagalaxy.h"

int main(int argc, char**argv){

	QStringList langList = QString(getenv("LANGUAGE")).split(":");

	KAboutData aboutData("mandriva-galaxy",
						 0,
						 ki18n("Mandriva Galaxy"),
						 "0.1",
						 ki18n("Show Mandriva information at startup"),
						 KAboutData::License_GPL,
						 ki18n("(c) 2008"),
						 ki18n("Show Mandriva information at startup"),
						 "http://www.mandriva.com",
						 "arthur@mandriva.com");

    KCmdLineArgs::init(argc, argv, &aboutData);
	
	KApplication app;

	//Test if we must show mandriva-galaxy
	if(!QSettings().value("showAtStartup", true).toBool())
		return 0;

	MandrivaGalaxy w(langList);

	return app.exec();
}
