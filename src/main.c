#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"

#include "timer.h"
#include "led.h"

#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// Declare and initialize the temperature array
int temperature[] = {24, 23, 31, 35, 12, 33, 27, 100, 37};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  trace_puts("Chuong Trinh Bat tat quat gio thong qua cam bien nhiet do!");
  trace_puts("Nhiet do > 27 tien hanh bat quat gio, Nhiet do < 27 tat quat gio!");


  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  timer_start();

  blink_led_init();

  uint32_t seconds = 0;

  // Infinite loop
  while (1)
    {
      //blink_led_on();
      timer_sleep(seconds == 0 ? TIMER_FREQUENCY_HZ : BLINK_ON_TICKS);

      //blink_led_off();
      timer_sleep(BLINK_OFF_TICKS);

      ++seconds;
      // Count seconds on the trace device.
      trace_printf("Second %u\n", seconds);

      // Print the current temperature
      trace_printf("Temperature: %d\n", temperature[seconds % 5]);

      // Check if the current temperature is above 30
      if (temperature[seconds % 5] > 27) {
        blink_led_on(); // Turn on the LED
        trace_puts("BAT QUAT GIO, LED GREEN ON!");
      } else {
        blink_led_off(); // Turn off the LED
        trace_puts("TAT QUAT GIO, LED GREEN OFF!");
      }
    }
}

#pragma GCC diagnostic pop
