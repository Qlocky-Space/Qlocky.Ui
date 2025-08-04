#include "QrQuickImageProvider.h"

#include "QrGenerator.h"

QrQuickImageProvider::QrQuickImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image) {
}

QImage QrQuickImageProvider::requestImage(QString const& id, QSize* size, QSize const& requestedSize) {
    QrGenerator qrGenerator {};

    QrImage qrImage = qrGenerator.encodeText(id.toStdString(), QrSize::Large);
    QImage image = qrImage.toImage(requestedSize.width() > 0 ? requestedSize.width() : 256);
    if (size) {
        *size = image.size();
    }
    return image;
}
