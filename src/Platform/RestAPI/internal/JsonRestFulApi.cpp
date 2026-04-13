#include "JsonRestFulApi.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

namespace {

RestApiCode mapReplyError(QNetworkReply const& reply) {
    if (reply.error() == QNetworkReply::OperationCanceledError) {
        return RestApiCode::Canceled;
    }

    QVariant const statusCode {reply.attribute(QNetworkRequest::HttpStatusCodeAttribute)};
    if (statusCode.isValid() && statusCode.toInt() >= 400) {
        return RestApiCode::HttpError;
    }

    if (reply.error() != QNetworkReply::NoError) {
        return RestApiCode::NetworkError;
    }

    return RestApiCode::Unknown;
}

QNetworkRequest createRequest(RestApiRequestOptions const& options) {
    QUrl const url {QString::fromStdString(options.url)};
    QNetworkRequest request {url};
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);

    if (!options.contentType.empty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QString::fromStdString(options.contentType));
    }

    for (RestApiHeader const& header : options.headers) {
        request.setRawHeader(QByteArray::fromStdString(header.name), QByteArray::fromStdString(header.value));
    }

    return request;
}

} // namespace

JsonRestFulApi::JsonRestFulApi(TaskExecutorIfc& taskExecutor) :
    RestApi {taskExecutor},
    m_networkAccessManager {} {
}

void JsonRestFulApi::requestRaw(Method method, RestApiRequestOptions const& options, RawCallback callback) {
    QUrl const url {QString::fromStdString(options.url)};
    if (!url.isValid()) {
        callback(RawResult::error(RestApiCode::InvalidUrl));
        return;
    }

    QNetworkRequest const request {createRequest(options)};
    QByteArray const body {QByteArray::fromStdString(options.body)};

    QNetworkReply* reply {nullptr};
    switch (method) {
        case Method::Head:
            reply = m_networkAccessManager.head(request);
            break;
        case Method::Get:
            reply = m_networkAccessManager.get(request);
            break;
        case Method::Post:
            reply = m_networkAccessManager.post(request, body);
            break;
        case Method::Put:
            reply = m_networkAccessManager.put(request, body);
            break;
        case Method::Patch:
            reply = m_networkAccessManager.sendCustomRequest(request, "PATCH", body);
            break;
        case Method::Delete:
            reply = m_networkAccessManager.deleteResource(request);
            break;
    }

    QObject::connect(reply, &QNetworkReply::finished, [reply, callback = std::move(callback)]() mutable {
        std::unique_ptr<QNetworkReply, void (*)(QNetworkReply*)> replyGuard(reply, [](QNetworkReply* currentReply) {
            if (currentReply != nullptr) {
                currentReply->deleteLater();
            }
        });

        RestApiCode const errorCode {mapReplyError(*reply)};
        if (errorCode != RestApiCode::Unknown) {
            callback(RawResult::error(errorCode));
            return;
        }

        callback(RawResult::success(reply->readAll().toStdString()));
    });
}