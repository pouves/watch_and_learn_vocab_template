#include "content.h"
#include "cards.h"

#define NUMBER_OF_CARDS  (NUMBER_OF_FLASH_CARDS)

// Globals
static enum side_t current_side;
static enum card_t current_card;
static Window *window;
static CardBack_t card_back;
static CardBack_t card_front;
static bool card_used[NUMBER_OF_CARDS];
static uint8_t card_counter = NUMBER_OF_CARDS;

// Private functions
static void load_card(void);
static void init_card_text(void);
static void show_card_text(void);
static void show_card_text_front(void);
static void hide_card_text(void);
static void hide_card_text_front(void);
static void load_card_text(enum card_t aa);
static void reset_card_used(void);

void init_cards(Window *main_window,
                CardBack_t main_card_front,
                CardBack_t main_card_back)
{
  reset_card_used();
  current_card = rand() % NUMBER_OF_CARDS;
  current_side = FRONT;
  window = main_window;
  window_set_background_color(main_window, GColorBlack);
  card_front = main_card_front;
  card_back = main_card_back;
  init_card_text();
  GRect bounds = layer_get_bounds(window_get_root_layer(window));

  load_card();
}

void deinit_cards(void) {
  layer_remove_child_layers(window_get_root_layer(window));
  text_layer_destroy(card_front.front_line_one);
  text_layer_destroy(card_back.back_line_one);
}

enum side_t flip_card(void) {
  if(current_side == FRONT) {
    //layer_set_hidden((Layer*)image_layer_front, true);
	hide_card_text_front();
    show_card_text();
    current_side = BACK;
  } else {
    //layer_set_hidden((Layer *)image_layer_front, false);
    hide_card_text();
	show_card_text_front();
    current_side = FRONT;
  }

  return (current_side);
}

enum side_t get_side(void) {
  return (current_side);
}

void rand_card(void) {
  while (card_used[current_card]) {
    current_card = rand() % NUMBER_OF_CARDS;
  }

  load_card();
}

void load_card(void) {
  //load_card_image();
  load_card_text(current_card);
  card_used[current_card] = true;

  if (!(--card_counter)) {
    reset_card_used();
  }
}

void init_card_text(void) {
  // Create the various text layers
  card_front.front_line_one  = text_layer_create(GRect(0, 55, 144, 100));

  // Set text colors
  text_layer_set_text_color(card_front.front_line_one, GColorWhite);

  // Set background colors
  text_layer_set_background_color(card_front.front_line_one, GColorBlack);

  // Set fonts
  text_layer_set_font(card_front.front_line_one, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));

  // Text alignment
  text_layer_set_text_alignment(card_front.front_line_one, GTextAlignmentCenter);

  // Add as child layers to window root
  layer_add_child(window_get_root_layer(window), (Layer*)card_front.front_line_one);
  
  // Create the various text layers
  card_back.back_line_one   = text_layer_create(GRect(0, 55, 144, 100));

  // Set text colors
  text_layer_set_text_color(card_back.back_line_one, GColorBlack);

  // Set background colors
  text_layer_set_background_color(card_back.back_line_one, GColorClear);

  // Set fonts
  text_layer_set_font(card_back.back_line_one, fonts_get_system_font(FONT_KEY_GOTHIC_24));

  // Text alignment
  text_layer_set_text_alignment(card_back.back_line_one, GTextAlignmentCenter);

  // Add as child layers to window root
  layer_add_child(window_get_root_layer(window), (Layer*)card_back.back_line_one);

  hide_card_text();
}

void show_card_text(void) {
  layer_set_hidden((Layer*)card_back.back_line_one, false);
}

void show_card_text_front(void) {
  layer_set_hidden((Layer*)card_front.front_line_one, false);
}

void hide_card_text(void) {
  layer_set_hidden((Layer*)card_back.back_line_one, true);
}

void hide_card_text_front(void) {
  layer_set_hidden((Layer*)card_front.front_line_one, true);
}

void load_card_text(enum card_t aa) {
  text_layer_set_text(card_front.front_line_one, aa_front_line_one[aa]);
  text_layer_set_text(card_back.back_line_one, aa_back_line_one[aa]);
}

void reset_card_used(void) {
  for (uint8_t i = NUMBER_OF_CARDS; i; --i) {
    card_used[NUMBER_OF_CARDS - i] = false;
  }

  card_counter = NUMBER_OF_CARDS;
  srand(time(NULL));
}
