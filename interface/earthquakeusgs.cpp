#include "earthquakeusgs.h"
#include "qjsonobject.h"
#include "mapitem.h"

#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGeoCoordinate>
#include <QTimeZone>
#include <QDateTime>
#include <QTimer>

EarthQuakeUsgs::EarthQuakeUsgs(QObject* parent): QObject(parent), mPoll(new QTimer), mMgr(new QNetworkAccessManager(parent)) {
    // handle get reply
    connect(mMgr, &QNetworkAccessManager::finished, this, &EarthQuakeUsgs::onReply);

    // poll
    connect(mPoll, &QTimer::timeout, this, &EarthQuakeUsgs::pollNewData);
    pollNewData(); // poll once right away
    mPoll->start(5000);
}

EarthQuakeUsgs::~EarthQuakeUsgs() {
    delete mPoll;
}

void EarthQuakeUsgs::pollNewData() {
     QUrl url(UsgsUrl);
     QNetworkRequest networkRequest(url);
     mMgr->get(networkRequest);
}

void EarthQuakeUsgs::onReply(QNetworkReply *reply) {
    if(reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        const auto& msgObj = jsonResponse.object();
        if(msgObj.contains("features")) {
            const auto& features = msgObj["features"].toArray();
            onItems(features);
        }
    } else {
        qDebug() << "Failed to get from USG" << reply->errorString();
    }
}

void EarthQuakeUsgs::onItems(const QJsonArray& features) {
    QList<MapItemPtr> newItems;
    for (const auto& f: features) {
        MapItemPtr newItem(new MapItem);
        QGeoPositionInfo info;
        newItem->setlimitedCoordinate(true); // only use latest location
        const auto& feature = f.toObject();
        if(feature.contains("geometry") && feature["geometry"].isObject()) {
            const auto& geometry = feature["geometry"].toObject();
            if(geometry.contains("coordinates") && geometry["coordinates"].isArray()) {
                const auto& location = geometry["coordinates"].toArray();
                if(location.size() > 1) {
                    const auto& lon = location[0].toDouble();
                    const auto& lat = location[1].toDouble();
                    info.setCoordinate({lat, lon});
                }
            }
        }
        if(feature.contains("id")) {
            newItem->setId(UsgsId + feature["id"].toString());
        }

        if(feature.contains("properties") && feature["properties"].isObject()) {
            QString desc = "<html>";
            const auto& prop = feature["properties"].toObject();
            if(prop.contains("title")) {
                desc = prop["title"].toString();
            } else if (prop.contains("place")) {
                 desc = prop["place"].toString();
            }

            qlonglong timeZon = 0;
            if(prop.contains("tz")) {
                // ms since unix epoch
                timeZon = prop["tz"].toVariant().toLongLong();
            };

            QDateTime time = QDateTime::currentDateTimeUtc();
            if(prop.contains("updated")) {
                updateTime(prop["updated"].toVariant().toLongLong(), timeZon, desc, time);
            } else if (prop.contains("time")) {
                updateTime(prop["time"].toVariant().toLongLong(), timeZon, desc, time);
            }

            desc += "</html>";
            newItem->setDescription(desc);

            info.setTimestamp(time);
        }

        newItem->addCoordinates({info});

        if(!newItem->coordinates().empty()) {
            newItems << newItem;
        }
    }
    emit updateMapItem(newItems);
}

void EarthQuakeUsgs::updateTime(const qlonglong& timeMs, const qlonglong& tz, QString& desc, QDateTime& time) {
    // ms since unix epoch
    time = QDateTime::fromMSecsSinceEpoch(timeMs, QTimeZone(tz));
    desc += "<br>" + time.toString();
}
