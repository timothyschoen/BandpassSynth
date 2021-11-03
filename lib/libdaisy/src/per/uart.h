/* 
TODO
- Add flexible config for:
  - data size, stop bits, parity, baud, etc.
  - dma vs interrupt (or not).
  - Error handling
- Transmit function improvements.
- Other UART Peripherals (currently only handles USART1 in UART mode.
- Overflow handling, etc. for Rx Queue.
*/

#pragma once
#ifndef DSY_UART_H
#define DSY_UART_H /**< macro */
#include "daisy_core.h"


namespace daisy
{
/** @addtogroup serial
    @{
    */

/** 
    Uart Peripheral
    @author shensley
    @date March 2020
    */
class UartHandler
{
  public:
    UartHandler() {}
    ~UartHandler() {}

    /** Initializes the UART Peripheral */
    void Init();

    /** Reads the amount of bytes in blocking mode with a 10ms timeout.
        \param *buff Buffer  to read to
    \param size Buff size
    \param timeout How long to timeout for (10ms?)
    \return Data received
     */
    int PollReceive(uint8_t *buff, size_t size, uint32_t timeout);

    /** Starts a DMA Receive callback to fill a buffer of specified size.
    Data is populated into a FIFO queue, and can be queried with the
    functions below.
    Size of the buffer is internally fixed to 256.
    Variable message lengths are transferred to the FIFO queue 
    anytime there is 1 byte-period without incoming data
    \return OK or ERROR
    */
    int StartRx();

    /** \return whether Rx DMA is listening or not. */
    bool RxActive();

    /** Flushes the Receive Queue
    \return OK or ERROR
    */
    int FlushRx();

    /** Sends an amount of data in blocking mode.
    \param *buff Buffer of data to send
    \param size Buffer size
    \return OK or ERROR
     */
    int PollTx(uint8_t *buff, size_t size);

    /** Pops the oldest byte from the FIFO. 
    \return Popped byte
     */
    uint8_t PopRx();

    /** Checks if there are any unread bytes in the FIFO
    \return 1 or 0 ??
     */
    size_t Readable();

    /** \return the result of HAL_UART_GetError() to the user. */
    int CheckError();

  private:
};

/** @} */
} // namespace daisy

#endif
