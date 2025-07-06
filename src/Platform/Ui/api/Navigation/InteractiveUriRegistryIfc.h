#ifndef INTERACTIVE_URI_REGISTRY_IFC_H
#define INTERACTIVE_URI_REGISTRY_IFC_H

#include <types/Uri.h>

/**
 * Contains metadata about an interactive QML page.
 */
struct InteractiveMeta {
    /**
     * Type of the interactive item.
     */
    enum class Type {
        Page,
    };

    /**
     * The path to the QML file.
     */
    std::string qmlPath;

    /**
     * The type of the interactive item.
     */
    Type type;

    /**
     * Constructs a new InteractiveMeta with a given type and QML path.
     *
     * @param type The type of the interactive item.
     * @param path The QML path.
     */
    InteractiveMeta(Type const type, std::string const& path) :
        qmlPath {path},
        type {type} {
    }
    InteractiveMeta() = default;
};

/**
 * Interface to register URI mappings for interactive navigation.
 */
class InteractiveUriRegistryIfc {
public:

    /**
     * Registers a URI and its associated metadata.
     *
     * @param uri The unique resource identifier.
     * @param meta Metadata associated with the URI.
     */
    virtual void registerUri(Uri const& uri, InteractiveMeta const& meta) = 0;

    /**
     * Retrieves the metadata for a given URI.
     *
     * @param uri The URI to look up.
     * @return Reference to the associated metadata.
     */
    virtual InteractiveMeta const& meta(Uri const& uri) = 0;

    virtual ~InteractiveUriRegistryIfc() = default;
};

#endif