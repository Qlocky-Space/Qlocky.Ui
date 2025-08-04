#ifndef QR_QUICK_IMAGE_PROVIDER_H
#define QR_QUICK_IMAGE_PROVIDER_H

#include <QQuickImageProvider>

/**
 * Image provider for QR codes in QML.
 * This class extends QQuickImageProvider to provide QR code images
 * based on a given ID. It uses the QrGenerator to create QR code images
 * and returns them as QImage objects.
 *
 * example usage in QML:
 * Image {
 *     source: "image://qr/your-text-here"
 *     fillMode: Image.PreserveAspectFit
 * }
 */
class QrQuickImageProvider : public QQuickImageProvider {
public:

    QrQuickImageProvider();

    /**
     * @see QQuickImageProvider::requestImage
     */
    QImage requestImage(QString const& id, QSize* size, QSize const& requestedSize) override;
};

#endif // QR_QUICK_IMAGE_PROVIDER_H