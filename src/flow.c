#include <pebble.h>
#include "flow_parser.h"


static Window *main_window;
static TextLayer *time_layer;
static TextLayer *info_layer;
static Flow *flow;

static void update_info() {
  static char buffer[8];
  snprintf(buffer, sizeof(buffer), "%d,%d,%d",
                                    (int) flow->config.track_seconds,
                                    (int) flow->config.track_minutes,
                                    (int) flow->config.track_hours);
  text_layer_set_text(info_layer, buffer);
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  parse_flow(iter, flow);
  update_info();
}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char buffer[8];
  strftime(buffer, sizeof(buffer), "%H:%M", tick_time);

  text_layer_set_text(time_layer, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  time_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_text(time_layer, "00:00");
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(time_layer));

  info_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(58, 52) + 60, bounds.size.w, 50));

  text_layer_set_background_color(info_layer, GColorClear);
  text_layer_set_text_color(info_layer, GColorBlack);
  text_layer_set_text(info_layer, "0,0,0");
  text_layer_set_font(info_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(info_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(info_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(time_layer);
  text_layer_destroy(info_layer);
}

static void init() {
  main_window = window_create();

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(main_window, true);

  flow = malloc(sizeof(Flow));

  APP_LOG(APP_LOG_LEVEL_ERROR, "1");
  app_message_register_inbox_received(inbox_received_callback);
  app_message_open(app_message_inbox_size_maximum(), 0);
  APP_LOG(APP_LOG_LEVEL_ERROR, "2");

  update_time();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  APP_LOG(APP_LOG_LEVEL_ERROR, "X");
  window_destroy(main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
