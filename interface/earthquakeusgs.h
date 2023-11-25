#ifndef EARTHQUAKEUSGS_H
#define EARTHQUAKEUSGS_H

#include "mapitemfwd.h"

#include <QObject>

class QTimer;
class QNetworkAccessManager;
class QNetworkReply;

class EarthQuakeUsgs : public QObject
{
        Q_OBJECT
public:
    explicit EarthQuakeUsgs(QObject* parent);
    ~EarthQuakeUsgs();

signals:
    void updateMapItem(const QList<MapItemPtr>&);

private slots:
    void pollNewData();
    void onReply(QNetworkReply *reply);

private:
    const QString UsgsUrlVersion = "1.0"; // lazy and lets us switch versions quickly
    const QString UsgsUrl = "https://earthquake.usgs.gov/earthquakes/feed/v" + UsgsUrlVersion + "/summary/" + UsgsUrlVersion + "_hour.geojson";
    const QString UsgsId = "UsgsId-";

    void onItems(const QJsonArray&);
    void updateTime(const qlonglong&,const qlonglong&, QString&,QDateTime&);

    QTimer* mPoll{nullptr};
    QNetworkAccessManager* mMgr{nullptr};
};

#endif // EARTHQUAKEUSGS_H
