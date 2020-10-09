#include <stdlib.h>
#include <math.h>
#include <video.h>
#include <input.h>
#include <math.h>

#define bool BOOL
#define true TRUE
#define false FALSE

#define MULT2    << 1
#define MULT4    << 2
#define MULT8    << 3
#define MULT16   << 4
#define MULT32   << 5
#define MULT64   << 6
#define DIV2     >> 1
#define DIV4     >> 2
#define DIV8     >> 3
#define DIV16    >> 4
#define DIV32    >> 5
#define DIV64    >> 6

#define itofix(value)                 value * 65536
#define clipping_tile_size(height)    (height DIV16)
#define  tile_size_number(width)      (width DIV16)
#define shrunk_extract_x(value)       value >> 8

#define RAND320     rand() % 320
#define RAND224     rand() % 224
#define RAND640     rand() % 640

#define SNOW_MAX      25
#define SNOW_X_OFFSET 120
#define SNOW_Y_OFFSET 224

#define LOGO_X_MOVE  10  + (ifmuli(fcos(_vbl_count),50))
#define LOGO_Y_MOVE  40  + (ifmuli(fsin(_vbl_count),18))

#define TEXTER_SPRITES_MAX  39
#define TEXT_SIZE           412
#define TEXT "*** THE BOYS FROM RSE BACK ONCE AGAIN *** THIS TIME ON THE MIGHTY NEO GEO CD! ENJOY THIS LITTLE ONE SCRENER, NOW GO MAKE ONE YOURSELF FOR THIS BEAUTIFUL PLATFORM ***                 * TEXT * 4PLAY                 * GRAPHICS AND DESIGN * GRASS        * CODE AND MUSIC * NAINAIN           GRASS SEND A PERSONNAL GREETING TO NEO-GEO.HU * THE HUNGARIAN NEO-GEO COMMUNITY.                                              "
#define TRIANGLE_MAX         6
#define TRIANGLE_ZOOM_INC   2

#define CDDA_PLAY                                 \
                  asm("loop_track_02:");          \
                  asm(" move.w #0x0002,%d0");     \
                  asm(" tst.b  0x10F6D9");        \
                  asm(" beq.s  loop_track_02");   \
                  asm(" jsr  0xC0056A");          \

#define TRIANGLES_ON
#define LOGO_ON
#define TEXT_ON
#define SNOW_ON

extern PALETTE palettes[];

extern TILEMAP
              snow,
              triangle03down,
              triangle03up,
              triangle02down,
              triangle02up,
              triangle01down,
              triangle01up,
              logo_76, logo_75, logo_74, logo_73, logo_72, logo_71, logo_70, logo_69, logo_68, logo_67, logo_66, logo_65, logo_64, logo_63, logo_62, logo_61, logo_60, logo_59, logo_58, logo_57, logo_56, logo_55, logo_54, logo_53, logo_52, logo_51, logo_50,
              shadow,
              fontA16[],
              fontB16[];

#define SHRUNK_TABLE_SIZE       30
#define LOGO_TABLE_TILES_SIZE   52

static const int shrunk_table[SHRUNK_TABLE_SIZE] =  { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0xE, 0xD, 0xC, 0xB, 0xA, 0x9, 0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1 };
static TILEMAP *logo_tiles[LOGO_TABLE_TILES_SIZE] = { &logo_76, &logo_75, &logo_74, &logo_73, &logo_72, &logo_71, &logo_70, &logo_69, &logo_68, &logo_67, &logo_66, &logo_65, &logo_64, &logo_63, &logo_62, &logo_61, &logo_60, &logo_59, &logo_58, &logo_57, &logo_56, &logo_55, &logo_54, &logo_53, &logo_52, &logo_51, &logo_50, &logo_51, &logo_52, &logo_53, &logo_54, &logo_55, &logo_56, &logo_57, &logo_58, &logo_59, &logo_60, &logo_61, &logo_62, &logo_63, &logo_64, &logo_65, &logo_66, &logo_67, &logo_68, &logo_69, &logo_70, &logo_71, &logo_72, &logo_73, &logo_74, &logo_75 };

typedef struct Logo Logo;
struct Logo {
  int id;
  int id_shadow;
  int shadow_yz;
  WORD tile_index;
};

typedef struct Snow Snow;
struct Snow {
  int id;
  int x;
  int y;
  int yz;
  BYTE size;
  BYTE speed;
  WORD shrunk_index;
  DWORD vbl_delta_move;
  DWORD vbl_delta_zoom;
};

typedef struct Texter Texter;
struct Texter {
  int ids[TEXT_SIZE];
  int xs[TEXT_SIZE];
  PTILEMAP tilemaps[TEXT_SIZE];
};

typedef struct Triangle Triangle;
struct Triangle {
  int id;
  int x;
  int zoom_yz;
  bool zoom_polarity;
  int clipping;
  DWORD vbl_delta_move_update;
  FIXED y;
};

static Snow snows[SNOW_MAX];
static Triangle triangles[TRIANGLE_MAX];
static Logo logo;
static Texter texter;

static void backdrop_color(BYTE index);

static void logo_init();
static void logo_move();
static void logo_update();
static void logo_zoom();

static void snow_init(Snow *psnow, BYTE size);
static void snows_update();
static void snows_field_init();

static void texter_init();
static void texter_update();

static void triangle_init(
  Triangle *triangle,
  FIXED y,
  int clipping,
  DWORD vbl_delta_move_update,
  const TILEMAP *tilemap
);

static void triangles_init();
static void triangle_move(Triangle *triangle);
static void triangle_zoom(Triangle *triangle, BYTE triangle_num);
static void triangles_update();

static void backdrop_color(BYTE index) {
  switch (index) {
  case 0:
    asm("move #0x1000,0x401FFE");
    break;

  case 1:
    asm("move #0x3000,0x401FFE");
    break;

  case 2:
    asm("move #0x0011,0x401FFE");
    break;

  case 3:
    asm("move #0x1011,0x401FFE");
    break;

  case 4:
    asm("move #0x0012,0x401FFE");
    break;

  case 5:
    asm("move #0x1022,0x401FFE");
    break;

  case 6:
    asm("move #0x5023,0x401FFE");
    break;

  case 7:
    asm("move #0x4034,0x401FFE");
    break;

  case 8:
    asm("move #0x4035,0x401FFE");
    break;

  case 9:
    asm("move #0x5045,0x401FFE");
    break;

  case 10:
    asm("move #0x0157,0x401FFE");
    break;

  case 11:
  default:
    asm("move #0x1157,0x401FFE");
    break;
  }
}

static void logo_init() {
  logo.tile_index = 0;
  logo.id_shadow = write_sprite_data(
    LOGO_X_MOVE - 70,
    LOGO_Y_MOVE + 25,
    0xF,
    0xFF,
    clipping_tile_size(96),
    tile_size_number(304),
    (const PTILEMAP)&shadow
  );

  logo.id = write_sprite_data(
    LOGO_X_MOVE,
    LOGO_Y_MOVE,
    0xF,
    0xFF,
    clipping_tile_size(96),
    tile_size_number(304),
    (const PTILEMAP)logo_tiles[0]
  );
}

static void logo_move() {
  change_sprite_pos(
    logo.id,
    LOGO_X_MOVE,
    LOGO_Y_MOVE,
    clipping_tile_size(96)
  );
  change_sprite_pos(
    logo.id_shadow,
    LOGO_X_MOVE - 10 + (logo.shadow_yz DIV8),
    LOGO_Y_MOVE + 57 - (logo.shadow_yz DIV2),
    clipping_tile_size(96)
  );
}

static void logo_zoom() {
  logo.shadow_yz += (logo.tile_index > ((LOGO_TABLE_TILES_SIZE) DIV2))
    ?  3
    : -3;
  if (logo.shadow_yz >= 0xFF) logo.shadow_yz = 0xFF;
  if (logo.shadow_yz <= 0x00) logo.shadow_yz = 0x00;

  if (_vbl_count % 2 == 0) {
    set_current_sprite(logo.id);

    write_sprite_data(
      LOGO_X_MOVE,
      LOGO_Y_MOVE,
      0xF,
      0xFF,
      clipping_tile_size(96),
      tile_size_number(304),
      (const PTILEMAP)logo_tiles[logo.tile_index++]
    );

    change_sprite_zoom(
      logo.id_shadow,
      0xF,
      logo.shadow_yz,
      tile_size_number(304)
    );

    if (logo.tile_index > LOGO_TABLE_TILES_SIZE - 1) logo.tile_index = 0;
    set_current_sprite(logo.id + tile_size_number(304));
  }
}

static void logo_update() {
  logo_move();
  logo_zoom();
}

static void snow_init(Snow *psnow, BYTE size) {
  psnow->x = RAND320 - SNOW_X_OFFSET;
  psnow->y = RAND224 - SNOW_Y_OFFSET;
  psnow->shrunk_index = rand() % SHRUNK_TABLE_SIZE;
  psnow->id = write_sprite_data(
    psnow->x,
    psnow->y,
    shrunk_table[psnow->shrunk_index],
    0xFF,
    clipping_tile_size(16),
    tile_size_number(16),
    (const PTILEMAP)&snow
  );

  if (size > 3) size = 3;

  psnow->size = size;
  psnow->yz = 0xFF;
  psnow->speed = 1;
  psnow->vbl_delta_move = 5;
  psnow->vbl_delta_zoom = 6;

  if (size == 2) {
    psnow->vbl_delta_move = 4;
    psnow->vbl_delta_zoom = 10;
    psnow->yz = 0xAA;
    change_sprite_zoom(
      psnow->id,
      0xA,
      0xAA,
      tile_size_number(16)
    );
  }

  if (size == 3) {
    psnow->vbl_delta_move = 3;
    psnow->vbl_delta_zoom = 16;
    psnow->yz = 0x8C;
    change_sprite_zoom(
      psnow->id,
      0x8,
      0x8C,
      tile_size_number(16)
    );
  }
}

static void snows_update() {
  BYTE i; for (i = 0; i < SNOW_MAX; i++) {
    if (_vbl_count % snows[i].vbl_delta_move  == 0) {
      if (snows[i].x > 320 || snows[i].y > 180) {
        snows[i].x = RAND320 - SNOW_X_OFFSET;
        snows[i].y = 30;
      }

      change_sprite_pos(
        snows[i].id,
        snows[i].x += snows[i].speed,
        snows[i].y += snows[i].speed,
        clipping_tile_size(16)
      );
    }

    if (_vbl_count % snows[i].vbl_delta_zoom == 0) {
      snows[i].shrunk_index++;
      if (snows[i].shrunk_index > SHRUNK_TABLE_SIZE)
        snows[i].shrunk_index = 0;

      change_sprite_zoom(
        snows[i].id,
        shrunk_table[snows[i].shrunk_index],
        snows[i].yz,
        tile_size_number(16)
      );
    }
  }
}

static void snows_field_init() {
  BYTE i = 0;
  for (i = 0; i < SNOW_MAX; i++) snow_init(&snows[i], rand() % 10);
}

static void texter_init() {
  int fontIndex = 0;
  int i = 0;
  int spriteIndex = get_current_sprite();
  int spriteIndexStart = spriteIndex;
  int spriteIndexMax = spriteIndex + TEXTER_SPRITES_MAX;

  for (i = 0; i < TEXT_SIZE; i++) {
    texter.ids[i] = NULL;
    texter.tilemaps[i] = NULL;
    texter.xs[i] = 340 + (i MULT8);
    texter.ids[i] = spriteIndex++;
    if (spriteIndex > spriteIndexMax) spriteIndex = spriteIndexStart;

    if (TEXT[i] >= 33 && TEXT[i] <= 78) { // fontA
      if (TEXT[i] == 33) fontIndex = 0;      // !
      if (TEXT[i] == 42) fontIndex = 1;      // *
      if (TEXT[i] == 44) fontIndex = 2;      // ,
      if (TEXT[i] == 45) fontIndex = 3;      // -
      if (TEXT[i] == 46) fontIndex = 4;      // .
      if (TEXT[i] == 47) fontIndex = 5;      // /
      if (TEXT[i] == 58) fontIndex = 16;     // :
      if (TEXT[i] == 63) fontIndex = 17;     // ?

      if (TEXT[i] >= 48 && TEXT[i] <= 57) fontIndex = TEXT[i] - 42; // 0 - 9
      if (TEXT[i] >= 65 && TEXT[i] <= 78) fontIndex = TEXT[i] - 47; // A - N
      texter.tilemaps[i] = (PTILEMAP)&fontA16[fontIndex];
    } else {
      if (TEXT[i] == 32) {
        texter.ids[i] = NULL;
        texter.tilemaps[i] = NULL;
      } else {
        fontIndex = TEXT[i] - 79;
        texter.tilemaps[i] = (PTILEMAP)&fontB16[fontIndex];
      }
    }
  }
}

static void texter_update() {
  int i;
  int current_sprite;
  for (i = 0; i < TEXT_SIZE; i++) {
    texter.xs[i]--;
    if (texter.xs[i] < 0) {
      current_sprite = get_current_sprite();
      set_current_sprite(texter.ids[i]);
      erase_sprites(1);
      set_current_sprite(current_sprite);
    }
    if (texter.xs[i] < 320 && texter.xs[i] >= 0) {
      if (texter.tilemaps[i] != NULL) {
        current_sprite = get_current_sprite();
        set_current_sprite(texter.ids[i]);
        write_sprite_data(
          texter.xs[i],
          (ifmuli(fsin((_vbl_count - i) * 8), 24) + 148),
          7,
          128,
          clipping_tile_size(16),
          tile_size_number(16),
          (const PTILEMAP)texter.tilemaps[i]
        );
        set_current_sprite(current_sprite);
      }
    }
  }
  if (texter.xs[TEXT_SIZE - 1] <= -100) {
    for (i = 0; i < TEXT_SIZE; i++) texter.xs[i] = 340 + (i MULT8);
  }
}

static void triangle_init(
    Triangle *triangle,
    FIXED y,
    int clipping,
    DWORD vbl_delta_move_update,
    const TILEMAP *tilemap
  ) {
    triangle->zoom_yz = 0xFF;

    triangle->id = write_sprite_data(
                    0,
                    fixtoi(y),
                    0xF,
                    triangle->zoom_yz,
                    clipping,
                    tile_size_number(512),
                    (const PTILEMAP)tilemap
                  );

    triangle->x = 0;
    triangle->y = y;
    triangle->clipping = clipping;
    triangle->zoom_polarity = false;
    triangle->vbl_delta_move_update = vbl_delta_move_update;
}

static void triangles_init() {
  triangle_init(
    &triangles[0],
    0,
    clipping_tile_size(48),
    5,
    (const PTILEMAP)&triangle03up
  );

  triangle_init(
    &triangles[1],
    0,
    clipping_tile_size(32),
    10,
    (const PTILEMAP)&triangle02up
  );

  triangle_init(
    &triangles[2],
    0,
    clipping_tile_size(16),
    15,
    (const PTILEMAP)&triangle01up
  );

  triangle_init(
    &triangles[3],
    itofix(176),
    clipping_tile_size(48),
    5,
    (const PTILEMAP)&triangle03down
  );

  triangle_init(
    &triangles[4],
    itofix(192),
    clipping_tile_size(32),
    10,
    (const PTILEMAP)&triangle02down
  );

  triangle_init(
    &triangles[5],
    itofix(208),
    clipping_tile_size(16), 15,
    (const PTILEMAP)&triangle01down
  );
}

static void triangle_move(Triangle *triangle) {
  if(_vbl_count % triangle->vbl_delta_move_update == 0) {
    change_sprite_pos(
      triangle->id,
      triangle->x += 1,
      fixtoi(triangle->y),
      triangle->clipping
    );
  }
}

static void triangle_zoom(Triangle *triangle, BYTE triangle_num) {
  int move_compensator = TRIANGLE_ZOOM_INC;
  (triangle->zoom_polarity)
    ? (triangle->zoom_yz += TRIANGLE_ZOOM_INC & 0xFF)
    : (triangle->zoom_yz -= TRIANGLE_ZOOM_INC & 0xFF);

   if (triangle->zoom_yz <= 0x00 + TRIANGLE_ZOOM_INC)
     triangle->zoom_polarity = true;

   if (triangle->zoom_yz >= 0xFF - TRIANGLE_ZOOM_INC)
     triangle->zoom_polarity = false;

    change_sprite_zoom(
      triangle->id,
      0xF,
      triangle->zoom_yz,
      tile_size_number(512)
    );

  if (triangle_num >= 3) {
    if (triangle_num == 3) move_compensator *= 12288;
    if (triangle_num == 4) move_compensator *=  8192;
    if (triangle_num == 5) move_compensator *=  4096;

    triangle->y = (!triangle->zoom_polarity)
      ? (fadd(triangle->y, move_compensator))
      : (fadd(triangle->y, move_compensator * -1));

    change_sprite_pos(
      triangle->id,
      triangle->x,
      fixtoi(triangle->y),
      triangle->clipping
    );
  }
}

static void triangles_update() {
  BYTE i; for (i = 0; i < TRIANGLE_MAX; i++) {
    triangle_move(&triangles[i]);
    triangle_zoom(&triangles[i], i);
  }
}

int main(void) {
  BYTE backdrop_color_index = 0;

  CDDA_PLAY
  setpalette(0, 60, (const PPALETTE)&palettes);
  backdrop_color(backdrop_color_index);
  set_current_sprite(3);

  #ifdef SNOW_ON
  snows_field_init();
  #endif

  #ifdef LOGO_ON
  logo_init();
  #endif

  #ifdef TRIANGLES_ON
  triangles_init();
  #endif

  #ifdef TEXT_ON
  texter_init();
  #endif

  while(1){
    wait_vbl();
    #ifdef TRIANGLES_ON
    triangles_update();
    #endif

    #ifdef TEXT_ON
    texter_update();
    #endif

    #ifdef SNOW_ON
    snows_update();
    #endif

    #ifdef LOGO_ON
    logo_update();
    #endif

    if (backdrop_color_index <= 12 && _vbl_count % 10 == 0) {
      backdrop_color(backdrop_color_index++);
    }
  }
}
