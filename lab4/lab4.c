// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "mouse.h"

extern struct packet mouse_packet;
extern uint8_t byte_index;
extern int count;

// Gesture state machine states
typedef enum {
START,
  DRAW_UP,
  VERTEX,
  DRAW_DOWN,
  END_STATE
} State;
State state = START;

// Accumulates horizontal displacement
uint8_t x_len_total = 0;

// Tracks previous button states for edge detection
uint8_t prev_lb = 0, prev_mb = 0, prev_rb = 0;

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need/ it]
    lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab4/output.txt");

        // handles control over to LCF
        // [LCF handles command line arguments and invokes the right function]
        if (lcf_start(argc, argv))
            return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int(mouse_test_packet)(uint32_t cnt) {
    int ipc_sta;
    message msg;
    uint8_t mouse_mask;

    // Subscribe mouse interrupts
    if(mouse_subscribe_int(&mouse_mask) != OK) return 1;

    // Activate stream mode
    if(mouse_write(0xF4) != OK) return 1;   // With functions that I made
    // if(mouse_enable_data_reporting() != OK) return 1;    // With function given by the teachers

    while(cnt) {
        if((driver_receive(ANY, &msg, &ipc_sta)) != OK) continue;

        if(is_ipc_notify(ipc_sta)) {
            if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
                if(msg.m_notify.interrupts & mouse_mask) {
                    mouse_ih();
                    mouse_sync_bytes();

                    if(byte_index == 3) {
                        mouse_bytes_to_packet();
                        mouse_print_packet(&mouse_packet); //! Porque é que é & e não *?
                        byte_index = 0;
                        cnt--;
                    }
                }
            }
        }
    }

    // Deactivate stream mode
    if(mouse_write(0xF5) != OK) return 1;

    // Unsubscribe mouse interrupts
    if(mouse_unsubscribe_int() != OK) return 1;

    return 0;
}

int(mouse_test_async)(uint8_t idle_time) {
    int ipc_sta;
    message msg;
    uint8_t mouse_mask, timer_mask;

    //! Rever melhor esta parte
    uint8_t limit = idle_time * sys_hz();

    // Subscribe mouse interrupts
    if (mouse_subscribe_int(&mouse_mask) != OK) return 1;

    // Subscribe timer interrupts
    if (timer_subscribe_int(&timer_mask) != OK) return 1;

    // Activate stream mode
    if(mouse_write(0xF4) != OK) return 1;

    while(count < limit) {
        if((driver_receive(ANY, &msg, &ipc_sta)) != OK) continue;

        if(is_ipc_notify(ipc_sta)) {
            if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
                if(msg.m_notify.interrupts & timer_mask) {
                    timer_int_handler();
                }
                if(msg.m_notify.interrupts & mouse_mask) {
                    mouse_ih();
                    mouse_sync_bytes();

                    if (byte_index == 3) {
                        mouse_bytes_to_packet();
                        mouse_print_packet(&mouse_packet);
                        byte_index = 0;
                        count = 0; // If packet concluded, reset count
                    }
                }
            }
        }

    }

    // Deactivate stream mode
    if(mouse_write(0xF5) != OK) return 1;

    // Unsubscribe mouse interrupts
    if(mouse_unsubscribe_int() != OK) return 1;

    // Unsubscribe timer interrupts
    if(timer_unsubscribe_int() != OK) return 1;

  return 0;
}

/**
 * Check if the packet movement is small enough to be considered jitter.
 * Returns true if both delta_x and delta_y are within tolerance.
 */
bool is_jitter(struct packet *p, uint8_t tol) {
    return abs(p->delta_x) <= tol 
        && abs(p->delta_y) <= tol;
}

/**
 * Validate an upward movement:
 * - Vertical displacement > horizontal displacement (slope > 1)
 * - Only small negative X deviations allowed (>= -tol)
 * - Positive Y movement
 */
bool valid_up(struct packet *p, uint8_t tol) {
    return abs(p->delta_y) > abs(p->delta_x)
        && abs(p->delta_x) >= -tol
        && p->delta_y > 0;
}

/**
 * Validate a downward movement:
 * - Vertical displacement > horizontal displacement (slope > 1)
 * - Only small negative X deviations allowed (>= -tol)
 * - Negative Y movement
 */
bool valid_down(struct packet *p, uint8_t tol) {
    return abs(p->delta_y) > abs(p->delta_x)
        && abs(p->delta_x) >= -tol
        && p->delta_y < 0;
}

/**
 * Update the state machine based on the latest mouse packet.
 * x_len: required minimum horizontal displacement
 * tolerance: allowed tolerance for small deviations
 */
void(update_state_machine)(uint8_t x_len, uint8_t tolerance) {
    bool lb = mouse_packet.lb;
    bool mb = mouse_packet.mb;
    bool rb = mouse_packet.rb;
    int dx = mouse_packet.delta_x;
    int dy = mouse_packet.delta_y;

    // Edge detection for button events
    bool left_press = (lb && !prev_lb && !mb && !rb);
    bool left_release = (!lb && prev_lb && !mb && !rb);
    bool right_press = (rb && !prev_rb && !lb && !mb);
    bool right_release = (!rb && prev_rb && !lb && !mb);

    switch (state) {

        case START:
            // Transition: start drawing up when left button pressed alone
            if (left_press) {
            state = DRAW_UP;
            x_len_total = 0;
            }

            break;

        case DRAW_UP:
            // Finish first line on left button release
            if(left_release) {
                state = (x_len_total >= x_len) ? VERTEX : START;
            
                x_len_total = 0;

                break;
            }

            // If left button is still down, process movement:
            if (lb) {
                if (valid_up(&mouse_packet, tolerance)) {
                    // Valid upward step: accumulate horizontal delta
                    x_len_total += dx;
                }
                else if (is_jitter(&mouse_packet, tolerance)) {
                    // Small jitter: ignore
                }
                else {
                    // Invalid movement: reset gesture
                    state = START;
                    x_len_total = 0;
                }  
            }
            else {
                // Unexpected button event: reset
                state = START;
                x_len_total = 0;
            }
            
            break;

        case VERTEX:
            // Transition to drawing down on right button press
            if (right_press) {
                state = DRAW_DOWN;
                x_len_total = 0; 
            }
            else if (is_jitter(&mouse_packet, tolerance)) {
                // Allow small residual movement at vertex
            }
            else if (abs(dx) > tolerance || abs(dy) > tolerance) {
                // Too much movement before pressing right: reset
                state = START;
                x_len_total = 0;
            }
        
            break;

        case DRAW_DOWN:
            // Finish second line on right button release
            if(right_release) {
                if(x_len_total >= x_len) {
                    state = END_STATE;
                }
                else 
                    state = START;

                x_len_total = 0;
            
                break;
            }

            // If right button is still down, process movement:
            if (rb) {
                if (valid_down(&mouse_packet, tolerance)) {
                    // Valid downward step: accumulate horizontal delta
                    x_len_total += dx;
                }
                else if(is_jitter(&mouse_packet, tolerance)) {
                    // Small jitter: ignore
                }
                else {
                    // Invalid movement: reset
                    state = START;
                    x_len_total = 0;
                }
            }
            else {
                // Unexpected button event: reset 
                state = START;
                x_len_total = 0;
            }

            break;

        case END_STATE:
            // Gesture complete: no further action
            break;
    }

    // Update previous button states for next packet
    prev_lb = lb;
    prev_mb = mb;
    prev_rb = rb;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    int ipc_sta;
    message msg;
    uint8_t mouse_mask;

    // Subscribe mouse interrupts
    if(mouse_subscribe_int(&mouse_mask) != OK) return 1;

    // Activate stream mode
    if(mouse_write(0xF4) != OK) return 1;

    state = START;
    x_len_total = 0;
    prev_lb = prev_mb = prev_rb = 0;

    while(state != END_STATE) {
        if((driver_receive(ANY, &msg, &ipc_sta)) != OK) continue;

        if(is_ipc_notify(ipc_sta)) {
            if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
                if(msg.m_notify.interrupts & mouse_mask) {
                    mouse_ih();
                    mouse_sync_bytes();

                    if(byte_index == 3) {
                        mouse_bytes_to_packet();
                        mouse_print_packet(&mouse_packet);
                        update_state_machine(x_len, tolerance);
                        byte_index = 0;
                    }
                }
            }
        }
    }

    // Deactivate stream mode
    if(mouse_write(0xF5) != OK) return 1;

    // Unsubscribe mouse interrupts
    if(mouse_unsubscribe_int() != OK) return 1;

    return 0;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
