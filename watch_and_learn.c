#include <pebble.h>
#include "cards.h"

#define NEXT_INTERVAL  (15)    // minutes
#define THRESHOLD      (800)   // mg

static Window *window;
static TextLayer *text_layer;
static uint8_t minute_tick = 0;
static CardBack_t card_back;
static CardBack_t card_front;

static bool flip_detected(AccelData *data, uint32_t num_samples);

void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	if (flip_card() == BACK) {
		window_set_background_color(window, GColorWhite);
    	text_layer_set_text_color(text_layer, GColorBlack);
  } else {
    	window_set_background_color(window, GColorBlack);
    	text_layer_set_text_color(text_layer, GColorWhite);
  }
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	//nothing here yet...
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	rand_card();
}

static void tick_timer_handler(struct tm *tick_time, TimeUnits units_changed) {
  static char time_text[] = "00:00"; // Needs to be static because it's used by the system later.
  strftime(time_text, sizeof(time_text), "%R", tick_time);
  text_layer_set_text(text_layer, time_text);

  if (!(tick_time->tm_min % NEXT_INTERVAL)) {
    rand_card();
    if (get_side() == BACK) {
      flip_card();
	  window_set_background_color(window, GColorBlack);
      text_layer_set_text_color(text_layer, GColorWhite);
    }
  }
}

static void accel_data_handler(AccelData *data, uint32_t num_samples) {
  if (!flip_detected(data, num_samples)) {
    return;
  }

  if (flip_card() == BACK) {
	window_set_background_color(window, GColorWhite);
    text_layer_set_text_color(text_layer, GColorBlack);
  } else {
    window_set_background_color(window, GColorBlack);
    text_layer_set_text_color(text_layer, GColorWhite);
  }
}

static void click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void window_load(Window *window) {
  init_cards(window, card_front, card_back);
	
  window_set_background_color(window, GColorBlack);	
	
  text_layer = text_layer_create(GRect(15, 0, 120, 56));
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer*)text_layer);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  deinit_cards();
}


static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_set_fullscreen(window, true);
  window_set_click_config_provider(window, click_config_provider);
  window_set_background_color(window, GColorBlack);
  window_stack_push(window, animated);

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  tick_timer_handler(current_time, MINUTE_UNIT);

  tick_timer_service_subscribe(MINUTE_UNIT, &tick_timer_handler);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_25HZ);
  accel_data_service_subscribe(25, &accel_data_handler);
}

static void deinit(void) {
  accel_data_service_unsubscribe();
  tick_timer_service_unsubscribe();
  window_destroy(window);
}

bool flip_detected(AccelData *data, uint32_t num_samples) {
  uint8_t i = 0;

  // Look for +y threshold
  while (i < num_samples) {
    if ((data + i)->y > THRESHOLD) {
      break;
    }
    ++i;
  }

  if (i == num_samples) {
    return (false);
  }

  // Look for -z threshold
  while (i < num_samples) {
    if ((data + i)->z < -THRESHOLD) {
      return (true);
    }

    ++i;
  }

  return (false);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
