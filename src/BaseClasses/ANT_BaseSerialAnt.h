#ifndef ANT_BASESERIALANT_h
#define ANT_BASESERIALANT_h

#include <BaseClasses/ANT_BaseAnt.h>

/**
 * Primary interface for communicating with an Ant Radio via serial.
 * This class provides methods for sending and receiving packets with an Ant radio via the serial port.
 * The Ant radio must be configured with the network stack
 * in order to use this software.
 * <p/>
 * Since this code is designed to run on a microcontroller, with only one thread, you are responsible for reading the
 * data off the serial buffer in a timely manner.  This involves a call to a variant of readPacket(...).
 * If your serial port is receiving data faster than you are reading, you can expect to lose packets.
 * Arduino only has a 128 byte serial buffer so it can overflow if many packets arrive
 * without a call to readPacket(...)
 * <p/>
 * In order to conserve resources, this class only supports storing one response packet in memory at a time.
 * This means that you must fully consume the packet prior to calling readPacket(...), because calling
 * readPacket(...) overwrites the previous response.
 * <p/>
 * This class creates an array of size MAX_FRAME_DATA_SIZE for storing the response packet.  You may want
 * to adjust this value to conserve memory.
 *
 * \author Andrew Rapp
 * \edited by Curtis Malainey
 */

template<class T>
class BaseSerialAnt : virtual public BaseAnt {
public:
    BaseSerialAnt();
    /**
     * Will read as much data on the serial port as possible till either it has a packet, gets an error or runs out of data
     * You may call <i>ant</i>.getResponse().isAvailable() after calling this method to determine if
     * a packet is ready, or <i>ant</i>.getResponse().isError() to determine if
     * a error occurred.
     * <p/>
     * This method should return quickly as it only works with what is available
     * You will want to use this method if you are doing other timely stuff in your loop, where
     * a delay would cause problems.
     * NOTE: calling this method resets the current response, so make sure you first consume the
     * current response
     */
    void readPacket() override;
    /**
     * Starts the serial connection on the specified serial port
     */
    void begin(T &serial);
    /**
     * Sends a AntRequest (TX packet) out the serial port
     */
    void send(AntRequest &request) override;
    /**
     * Associates a serial device with the ANT driver
     */
    virtual void setSerial(T &serial) = 0;
protected:
    virtual uint8_t read() = 0;
    virtual uint8_t available() = 0;
    virtual void write(uint8_t* byte, uint8_t len) = 0;
private:
    void resetResponse();
    // current packet position for response.  just a state variable for packet parsing and has no relevance for the response otherwise
    uint8_t _pos;
    // last byte read
    uint8_t b;
    uint8_t _checksumTotal;
    // buffer for incoming RX packets.  holds only the msg specific frame data, starting after the msg id byte and prior to checksum
    uint8_t _responseFrameData[ANT_MAX_MSG_DATA_SIZE];
};

#endif // ANT_BASESERIALANT_h
