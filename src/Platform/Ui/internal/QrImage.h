#ifndef QR_IMAGE_H
#define QR_IMAGE_H

#include <QImage>

#include "QRCodeGen/qrcodegen.hpp"

/**
 * Wrapper class for QR code images.
 */
class QrImage {
public:

    /**
     * Creates a QrImage from a qrcodegen::QrCode object.
     * @param qr The QR code to convert into an image.
     * @return A QrImage representing the QR code.
     */
    static QrImage fromQrCode(qrcodegen::QrCode const& qr);

    QrImage() = delete;

    /**
     * Converts the QR code to a QImage.
     * @param size The size of the QR code in pixels.
     * @return A QImage representing the QR code.
     */
    QImage toImage(int32_t const size = 256) const;

private:

    QrImage(qrcodegen::QrCode const& qr) :
        m_qrCode(qr) {
    }

    qrcodegen::QrCode m_qrCode;
};

#endif