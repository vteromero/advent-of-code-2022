#include <cstring>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct rock {
  uint8_t shape[4];
  size_t left_shift;
  size_t right_shift;
  size_t height;
};

void rock_copy(struct rock *dst, const struct rock *src) {
  memcpy(dst, src, sizeof(*src));
}

void rock_shift_left(struct rock *r)
{
  if (r->left_shift == 0) {
    return;
  }
  for (size_t i = 0; i < 4; i++) {
    r->shape[i] <<= 1;
  }
  r->left_shift--;
  r->right_shift++;
}

void rock_shift_right(struct rock *r)
{
  if (r->right_shift == 0) {
    return;
  }
  for (size_t i = 0; i < 4; i++) {
    r->shape[i] >>= 1;
  }
  r->left_shift++;
  r->right_shift--;
}

bool shapes_collide(const uint8_t s1[4], const uint8_t s2[4])
{
  for (size_t i = 0; i < 4; i++) {
    if (s1[i] & s2[i]) {
      return true;
    }
  }
  return false;
}

void merge_shapes(uint8_t s1[4], const uint8_t s2[4])
{
  for (size_t i = 0; i < 4; i++) {
    s1[i] |= s2[i];
  }
}

const size_t NUM_ROCKS = 5;
const size_t TARGET_ROCKS = 2022;

const struct rock rocks[NUM_ROCKS] = {
  // ........ 3
  // ........ 2
  // ........ 1
  // ...####. 0
  {
    .shape = {1<<4 | 1<<3 | 1<<2 | 1<<1, 0, 0, 0},
    .left_shift = 2,
    .right_shift = 1,
    .height = 1
  },
  // ........ 3
  // ....#... 2
  // ...###.. 1
  // ....#... 0
  {
    .shape = {1<<3, 1<<4 | 1<<3 | 1<<2, 1<<3, 0},
    .left_shift = 2,
    .right_shift = 2,
    .height = 3
  },
  // ........ 3
  // .....#.. 2
  // .....#.. 1
  // ...###.. 0
  {
    .shape = {1<<4 | 1<<3 | 1<<2, 1<<2, 1<<2, 0},
    .left_shift = 2,
    .right_shift = 2,
    .height = 3
  },
  // ...#.... 3
  // ...#.... 2
  // ...#.... 1
  // ...#.... 0
  {
    .shape = {1<<4, 1<<4, 1<<4, 1<<4},
    .left_shift = 2,
    .right_shift = 4,
    .height = 4
  },
  // ........ 3
  // ........ 2
  // ...##... 1
  // ...##... 0
  {
    .shape = {1<<4 | 1<<3, 1<<4 | 1<<3, 0, 0},
    .left_shift = 2,
    .right_shift = 3,
    .height = 2
  }
};

int main()
{
  const size_t chamber_sz = TARGET_ROCKS * 4 + 7;
  vector<uint8_t> chamber(chamber_sz, 0);
  size_t top = 0;
  string jet_pattern;

  getline(cin, jet_pattern);

  for (size_t i=0, j=0; i < TARGET_ROCKS; i++) {
    size_t rock_pos = top + 3;
    struct rock r;

    rock_copy(&r, &rocks[i % NUM_ROCKS]);

    while (1) {
      char p = jet_pattern[j++ % jet_pattern.size()];
      switch (p) {
        case '<':
          rock_shift_left(&r);
          if (shapes_collide(r.shape, chamber.data() + rock_pos)) {
            rock_shift_right(&r);
          }
          break;
        case '>':
          rock_shift_right(&r);
          if (shapes_collide(r.shape, chamber.data() + rock_pos)) {
            rock_shift_left(&r);
          }
          break;
      }

      if (rock_pos == 0 || shapes_collide(r.shape, chamber.data() + rock_pos - 1)) {
        merge_shapes(chamber.data() + rock_pos, r.shape);
        top = max(top, rock_pos + r.height);
        break;
      }

      rock_pos--;
    }
  }
  /*cout << "chamber:" << endl;
  for (size_t i = chamber_sz; i-- > 0;) {
    for (size_t j = 8; j-- > 0;) {
      if (chamber[i] & (1<<j)) {
        cout << "#";
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }*/

  cout << top << endl;

  return 0;
}
