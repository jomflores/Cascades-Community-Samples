/* Copyright (c) 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <QObject>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
		QObject(app) {

	// create scene document from main.qml asset
	// set parent to created document to ensure it exists for the whole application lifetime
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("BBBBBBrowser", this);

	// create root object for the UI
	AbstractPane *root = qml->createRootObject<AbstractPane>();
	// set created root object as a scene
	app->setScene(root);
}

QString ApplicationUI::formatURLStuff(const QString &msg) {

	QUrl url = msg;
	url = url.toEncoded();
	if (url.scheme().isEmpty()) {
		//if there is a ., let's guess it's an URL
		if (url.toString().contains(".")) {
			url.setScheme("http");
		}
		//if there is no scheme	and no dot search
		else {
			QUrl searchUrl("http://www.google.com/search");
			searchUrl.addQueryItem("q", msg);
			searchUrl.addQueryItem("hl", "en");
			searchUrl.addQueryItem("oq", msg);
			QByteArray baseurl = url.toEncoded();
			url = searchUrl;
		}
	}
	return url.toString();
}
