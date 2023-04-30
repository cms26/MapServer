#include "httpserver.h"
#include "mapitemsmodel.h"
#include "mapitem.h"

#include <QtHttpServer>

const static int PortNumber = 80;

HttpServer::HttpServer(QObject* parent, MapItemsModel* dataModel) : QObject(parent), mServer(new QHttpServer(parent)), mDataModel(dataModel) {
    QHttpServer httpServer;

    mServer->route("/map-items/", [=] (const QHttpServerRequest &request) {
        switch(request.method()) {;
        case QHttpServerRequest::Method::Put:
            return onAddMapItem(request.body());
        case QHttpServerRequest::Method::Get:
            return onRequestMapItems();
        default:
            return QHttpServerResponse(QHttpServerResponse::StatusCode::InternalServerError); // unknown case
        }
    });

    qDebug() << "Listening on port" << PortNumber;
    mServer->listen(QHostAddress::LocalHost, PortNumber);
}

HttpServer::~HttpServer() {
   qDebug() << "Server shut down";
}

QHttpServerResponse HttpServer::onRequestMapItems() {
    if(mDataModel) {
        return QHttpServerResponse(mDataModel->mapItems());
    }

    return QHttpServerResponse("No data",
                               QHttpServerResponse::StatusCode::InternalServerError);
}

QHttpServerResponse HttpServer::onAddMapItem(const QByteArray& mapData) {
    QJsonParseError* err{nullptr};
    const auto& jsonData = QJsonDocument::fromJson(mapData, err);
    if(err) {
        return QHttpServerResponse(err->errorString(),
                                   QHttpServerResponse::StatusCode::InternalServerError); // unknown case
    }

    onData(jsonData);

    return QHttpServerResponse("");
}

void HttpServer::onData(const QJsonDocument& parsedData) {
    if(!parsedData.isArray()) {
        qWarning() << "Map data is not an array - its invalid. Not adding data.";
        return;
    }
    const auto& array = parsedData.array();

    QList<MapItemPtr> newItems;
    newItems.reserve(array.size());

    for(const auto& item: array) {
        MapItemPtr mapitem(new MapItem());
        mapitem->fromJson(item.toObject());
        newItems << mapitem;
    }
    emit updateMapItem(newItems);
}

