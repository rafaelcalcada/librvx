// SPDX-License-Identifier: MIT
// Copyright (c) 2020-2025 RVX Project Contributors

#ifndef __LIBSTEEL_UART__
#define __LIBSTEEL_UART__

#include "globals.h"

// Struct providing access to RVX UART Controller registers
typedef struct
{
  // Write Data (WDATA) Register. Address offset: 0x00
  volatile uint32_t WDATA;
  // Read Data (RDATA) Register. Address offset: 0x04
  volatile uint32_t RDATA;
  // Ready (READY) Register. Address offset: 0x08
  volatile uint32_t READY;
  // RX Status (RXSTATUS) Register. Address offset: 0x0c
  volatile uint32_t RXSTATUS;
} UartController;

/**
 * @brief Read register READY from the UART device. Return true if the device is ready to send
 * data, false otherwise.
 *
 * @param uart Pointer to the UartController
 * @return true
 * @return false
 */
static inline bool uart_ready_to_send(UartController *uart)
{
  return uart->READY == 1;
}

/**
 * @brief Read register RDATA of the UART device. The UART requests an interrupt when it
 * completes receiving new data. The new data can be read by calling this function.
 *
 * @param uart Pointer to the UartController
 * @return uint8_t
 */
static inline uint8_t uart_read(UartController *uart)
{
  return uart->RDATA;
}

/**
 * @brief Write a single byte to register WDATA of the UART device. It awaits the UART to be ready
 * before writing to the register.
 *
 * @param uart Pointer to the UartController
 * @param data A byte as uint8_t
 */
static inline void uart_write(UartController *uart, uint8_t data)
{
  while (!uart_ready_to_send(uart))
    ;
  uart->WDATA = data;
}

/**
 * @brief Send a C-string over the UART device.
 *
 * @param uart Pointer to the UartController
 * @param str A null-terminated C-string
 */
static inline void uart_write_string(UartController *uart, const char *str)
{
  while (*(str) != '\0')
  {
    uart_write(uart, *(str));
    str++;
  }
}

/**
 * @brief Read the RXSTATUS register of the UART controller. Returns true when new data was received
 * but not yet read.
 *
 * @param uart
 * @return true
 * @return false
 */
static inline bool uart_data_received(UartController *uart)
{
  return uart->RXSTATUS == 1;
}

#endif // __LIBSTEEL_UART__
