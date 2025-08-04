#include "QrImage.h"

#include <QPainter>

QrImage QrImage::fromQrCode(qrcodegen::QrCode const& qr) {
    return QrImage(qr);
}

QImage QrImage::toImage(int32_t const size) const {
    int16_t const border = 1;

    int const qrSize = m_qrCode.getSize();
    int const totalSize = qrSize + 2 * border;
    // Calculate scaling factor to fit requested size
    int const pixelSize = size / totalSize;
    int const imageSize = pixelSize * totalSize;
    // Create the output image
    QImage image(imageSize, imageSize, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);

    // Draw each QR module (black square)
    for (int y = 0; y < qrSize; ++y) {
        for (int x = 0; x < qrSize; ++x) {
            if (m_qrCode.getModule(x, y)) {
                int xPos = (x + border) * pixelSize;
                int yPos = (y + border) * pixelSize;
                painter.drawRect(xPos, yPos, pixelSize, pixelSize);
            }
        }
    }

    return image;
}
