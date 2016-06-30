typedef union {
  struct {
    GRect bounds;
  } data;
  char cstring[sizeof(GRect)];
} Bounds;

typedef union {
  struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
  } data;
  char cstring[3];
} FlowConditions;

typedef union {
  struct {
    uint8_t x;
    uint8_t y;
    uint8_t argb;
  } data;
  char cstring[3];
} FlowPixel;

typedef struct {
  FlowConditions conditions;
  size_t num_pixels;
  FlowPixel *pixels;
} FlowSlice;

typedef struct {
  Bounds bounds;
  size_t num_slices;
  FlowSlice *slices;
} FlowLayer;

typedef struct {
  uint8_t track_seconds;
  uint8_t track_minutes;
  uint8_t track_hours;
} FlowConfig;

typedef struct {
  FlowConfig config;
  size_t num_layers;
  FlowLayer *layers;
} Flow;

enum FlowCommand {
  TRACK_SECONDS,
  TRACK_MINUTES,
  TRACK_HOURS,
  SET_NUM_LAYERS,
  ADD_LAYER,
  SET_LAYER_BOUNDS,
  SET_NUM_SLICES,
  ADD_SLICE,
  SET_SLICE_CONDITIONS,
  SET_NUM_PIXELS,
  ADD_PIXEL
};
