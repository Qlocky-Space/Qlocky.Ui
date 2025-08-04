#include "QrGenerator.h"

#include "QRCodeGen/qrcodegen.hpp"

using qrcodegen::QrCode;

QrImage QrGenerator::encodeText(std::string const& data, QrSize size) {
    QrCode::Ecc eccLevel;
    switch (size) {
        case QrSize::Small:
            eccLevel = QrCode::Ecc::LOW;
            break;
        case QrSize::Medium:
            eccLevel = QrCode::Ecc::MEDIUM;
            break;
        case QrSize::Large:
            eccLevel = QrCode::Ecc::HIGH;
            break;
        default:
            eccLevel = QrCode::Ecc::MEDIUM; // Default to medium if size is unknown
            break;
    }

    // Create a QR Code generator
    QrCode qr = QrCode::encodeText(data.c_str(), eccLevel);

    return QrImage::fromQrCode(qr);
}