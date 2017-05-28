#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Channel Event or Channel Response Message
 */
class ChannelEventResponse : public AntResponse {
public:
    ChannelEventResponse();
    uint8_t getChannelNumber();
    uint8_t getMsgId();
    uint8_t getCode();
    uint8_t getExtendedEventParameters();

    static const uint8_t MSG_ID = CHANNEL_RESPONSE;
};