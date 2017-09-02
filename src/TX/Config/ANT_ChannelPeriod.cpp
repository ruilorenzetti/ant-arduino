#include <TX/Config/ANT_ChannelPeriod.h>

#include <ANT_defines.h>

#define CHANNEL_PERIOD_LENGTH  0x03

ChannelPeriod::ChannelPeriod() : AntRequest(CHANNEL_PERIOD) {

}

void ChannelPeriod::setChannel(uint8_t channel) {
    _channel = channel;
}

void ChannelPeriod::setPeriod(uint16_t period) {
    _period = period;
}

uint8_t ChannelPeriod::getChannel() {
    return _channel;
}

uint16_t ChannelPeriod::getPeriod() {
    return _period;
}

uint8_t ChannelPeriod::getDataLength() {
    return CHANNEL_PERIOD_LENGTH;
}

uint8_t ChannelPeriod::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return (uint8_t)_period;
    } else {
        return (uint8_t)(_period >> BITS_IN_BYTE);
    }
}