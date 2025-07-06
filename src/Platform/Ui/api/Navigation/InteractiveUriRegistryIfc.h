#ifndef INTERACTIVE_URI_REGISTRY_IFC_H
#define INTERACTIVE_URI_REGISTRY_IFC_H

#include <types/Uri.h>

struct InteractiveMeta {
    enum class Type {
        Page,
    };

    std::string qmlPath;
    Type type;

    InteractiveMeta() = default;
    InteractiveMeta(Type const type, std::string const& path) :
        qmlPath {path},
        type {type} {
    }
};

/**
 * Interface to register uri's for InteractiveNavigation.
 */
class InteractiveUriRegistryIfc {
public:

    /**
     * Navigates to the default page.
     */
    virtual void registerUri(Uri const& uri, InteractiveMeta const& meta) = 0;

    /**
     * Navigates back to the previous page.
     */
    virtual InteractiveMeta const& meta(Uri const& uri) = 0;

    virtual ~InteractiveUriRegistryIfc() = default;
};

#endif