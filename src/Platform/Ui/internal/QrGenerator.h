#ifndef QR_GENERATOR_H
#define QR_GENERATOR_H

#include "QrImage.h"

/**
 * Enum representing the size of the QR code.
 */
enum class QrSize {
    Small,
    Medium,
    Large
};

/**
 * QR code generator implementation.
 */
class QrGenerator {
public:

    /**
     * @see QrGeneratorIfc::encodeText
     */
    QrImage encodeText(std::string const& data, QrSize size = QrSize::Large);
};

#endif // QR_GENERATOR_H