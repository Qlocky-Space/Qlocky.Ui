#ifndef NL80211_UTIL_H
#define NL80211_UTIL_H

#include <linux/nl80211.h>

class Nl80211Util {
public:

    static char const* channelTypeName(nl80211_channel_type channel_type) {
        switch (channel_type) {
            case NL80211_CHAN_NO_HT:
                return "NO HT";
            case NL80211_CHAN_HT20:
                return "HT20";
            case NL80211_CHAN_HT40MINUS:
                return "HT40-";
            case NL80211_CHAN_HT40PLUS:
                return "HT40+";
            default:
                return "unknown";
        }
    }

    static char const* channelWidthName(nl80211_chan_width width) {
        switch (width) {
            case NL80211_CHAN_WIDTH_20_NOHT:
                return "20 MHz (no HT)";
            case NL80211_CHAN_WIDTH_20:
                return "20 MHz";
            case NL80211_CHAN_WIDTH_40:
                return "40 MHz";
            case NL80211_CHAN_WIDTH_80:
                return "80 MHz";
            case NL80211_CHAN_WIDTH_80P80:
                return "80+80 MHz";
            case NL80211_CHAN_WIDTH_160:
                return "160 MHz";
            case NL80211_CHAN_WIDTH_5:
                return "5 MHz";
            case NL80211_CHAN_WIDTH_10:
                return "10 MHz";
            case NL80211_CHAN_WIDTH_320:
                return "320 MHz";
            default:
                return "unknown";
        }
    }
};

#endif