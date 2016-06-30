#include <pebble.h>
#include "flow_config.h"


static size_t layer_index;
static size_t slice_index;
static size_t pixel_index;

void parse_flow(DictionaryIterator *iter, Flow *flow) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "parse");
  Tuple *tuple = dict_read_first(iter);
  while (tuple) {
    switch (tuple->key) {
      case TRACK_SECONDS:
        APP_LOG(APP_LOG_LEVEL_ERROR, "0 - %d", (int) tuple->value->uint8);
        flow->config.track_seconds = tuple->value->uint8;
        break;

      case TRACK_MINUTES:
        APP_LOG(APP_LOG_LEVEL_ERROR, "1 - %d", (int) tuple->value->uint8);
        flow->config.track_minutes = tuple->value->uint8;
        break;

      case TRACK_HOURS:
        APP_LOG(APP_LOG_LEVEL_ERROR, "2 - %d", (int) tuple->value->uint8);
        flow->config.track_hours = tuple->value->uint8;
        break;
      //
      // case SET_NUM_LAYERS:
      //   flow->num_layers = tuple->value->uint16;
      //   flow->layers = malloc( tuple->value->uint16 * sizeof(FlowLayer) );
      //   layer_index = -1;
      //   break;
      //
      // case ADD_LAYER:
      //   layer_index += 1;
      //   break;
      //
      // case SET_LAYER_BOUNDS:
      //   flow->layers[layer_index].bounds.cstring = tuple->value->cstring;
      //   break;
      //
      // case SET_NUM_SLICES:
      //   flow->layers[layer_index]
      //     .num_slices = tuple->value->uint16;
      //   flow->layers[layer_index]
      //     .slices = malloc( tuple->value->uint16 * sizeof(FlowSlice) );
      //   slice_index = -1;
      //   break;
      //
      // case ADD_SLICE:
      //   slice_index += 1;
      //   break;
      //
      // case SET_SLICE_CONDITIONS:
      //   flow->layers[layer_index]
      //     .slices[slice_index]
      //     .conditions.cstring = tuple->value->cstring;
      //   break;
      //
      // case SET_NUM_PIXELS:
      //   flow->layers[layer_index]
      //     .slices[slice_index]
      //     .num_pixels = tuple->value->uint16;
      //     flow->layers[layer_index]
      //       .slices[slice_index]
      //       .pixels = malloc( tuple->value->uint16 * sizeof(FlowSlice) );
      //   pixel_index = -1;
      //   break;
      //
      // case ADD_PIXEL:
      //   flow->layers[layer_index]
      //     .slices[slice_index]
      //     .pixels[pixel_index].cstring = tuple->value->cstring;
      //   pixel_index += 1;
      //   break;
    }
    tuple = dict_read_next(iter);
  }
}
