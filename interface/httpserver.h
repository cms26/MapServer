#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "mapitemfwd.h"

#include <QObject>
#include <QHttpServerRequest>
#include <QHttpServerResponse>

class QHttpServer;
class QJsonDocument;
class MapItemsModel;

class HttpServer final : public QObject
{
    Q_OBJECT
public:
    explicit HttpServer(QObject* parent = nullptr, MapItemsModel* dataModel = nullptr);
    ~HttpServer();

signals:
    void updateMapItem(const QList<MapItemPtr>&);

private slots:
    QHttpServerResponse onRequestMapItems();
    QHttpServerResponse onAddMapItem(const QByteArray&);

private:
    void onData(const QJsonDocument&);

    QHttpServer* mServer{nullptr};
    MapItemsModel* mDataModel{nullptr};
};

#endif // HTTPSERVER_H
