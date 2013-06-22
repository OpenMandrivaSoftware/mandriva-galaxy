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

#include <QDesktopWidget>
#include <QFile>
#include <QLocale>
#include <QProcess>
#include <QSettings>

#include "mandrivagalaxy.h"

MandrivaGalaxy::MandrivaGalaxy(QStringList p_langList, QWidget *parent)
: QWidget(parent)
{
	m_ui.setupUi(this);

	connect(m_ui.showAtStartupCheckBox, SIGNAL(stateChanged(int)),
			this, SLOT(slotShowAtStartupChanged(int)));

	//Check LANGUAGE to open the right page
	QString url = QString("/usr/share/mdk/mandrivagalaxy/index-%1.html");
	QStringList langList = p_langList;

	bool urlAvailable = false;
	QStringList::const_iterator it;
	for(it = langList.constBegin(); it != langList.constEnd(); ++it)
	{
		if(QFile::exists(url.arg(*it)))
		{
			url = url.arg(*it);
			urlAvailable = true;
			break;
		}
	}

	if(!urlAvailable)
		url = QString("/usr/share/mdk/mandrivagalaxy/index.html");

	m_ui.webView->load(QUrl(url));

	//Do not let webView treat any link by itself
	m_ui.webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	connect(m_ui.webView, SIGNAL(linkClicked(QUrl)),
			this, SLOT(slotLinkClicked(QUrl)));

	//Resize widget related to desktop resolution
	QDesktopWidget desktop;
	QRect desktopRect = desktop.screenGeometry();

	if(desktopRect.width() < 1024)
		resize(desktopRect.size() * 0.8);	
	else if(desktopRect.width() < 800)
		resize(desktopRect.size() * 0.6);	

	//Move widget to desktop center
	QRect r = rect();
	r.moveCenter(desktopRect.center());
	move(r.topLeft());

	show();
}

MandrivaGalaxy::~MandrivaGalaxy()
{
}

void MandrivaGalaxy::slotShowAtStartupChanged(int state)
{
	QSettings().setValue("showAtStartup", state == Qt::Checked);
}

void MandrivaGalaxy::slotLinkClicked(QUrl url)
{
	QProcess::startDetached("xdg-open", QStringList(url.toString()));
}
