#include "InteractiveUriRegistry.h"

void InteractiveUriRegistry::registerUri(Uri const& uri, InteractiveMeta const& meta) {
    if (m_map.count(uri) > 0) {
        return;
    }

    m_map[uri] = meta;
}

InteractiveMeta const& InteractiveUriRegistry::meta(Uri const& uri) {
    return m_map.at(uri);
}
