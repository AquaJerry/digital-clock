#include <SDL2/SDL.h>
#include <array>
#include <ctime>

SDL_Renderer *renderer;
auto when = time(nullptr) % 86400;
const int TEN_HOUR_X = 0;
const int ONE_HOUR_X = 5;
const int TEN_MINUTE_X = 11;
const int ONE_MINUTE_X = 16;
const int TEN_SECOND_X = 22;
const int ONE_SECOND_X = 27;
const std::array<Uint8, 7> sevenSegment{33, 7, 19, 57, 16, 4, 45};
const std::array<Uint8, 10> digits{126, 48, 109, 121, 51,
                                   91,  95, 112, 127, 115};
int hour = when / 3600 % 24;
int minute = (when % 3600) / 60;
int second = when % 60;

void drawDigit(const int digit, const int x) {
  for (Uint8 index = 7, card = digits.at(digit); --index < 7; card >>= 1) {
    if ((1U & card) != 0) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
    Uint8 segment = sevenSegment.at(index);
    int horizontal = (32U & segment) / 32;
    SDL_Rect rect{x + segment % 4, static_cast<int>((223U & segment) / 4),
                  1 + horizontal, 2 - horizontal};
    SDL_RenderFillRect(renderer, &rect);
  }
}

Uint32 loop(Uint32 interval, void * /* unused */) {
  int oneSecond = ++second % 10;
  if (oneSecond == 0) {
    int tenSecond = second / 10;
    if (6 == tenSecond) {
      second = tenSecond = 0;
      int oneMinute = ++minute % 10;
      if (oneMinute == 0) {
        int tenMinute = minute / 10;
        if (6 == tenMinute) {
          minute = tenMinute = 0;
          int oneHour = ++hour % 10;
          int tenHour = hour / 10;
          if (24 == hour) {
            hour = oneHour = tenHour = 0;
          }
          drawDigit(oneHour, ONE_HOUR_X);
          drawDigit(tenHour, TEN_HOUR_X);
        }
        drawDigit(tenMinute, TEN_MINUTE_X);
      }
      drawDigit(oneMinute, ONE_MINUTE_X);
    }
    drawDigit(tenSecond, TEN_SECOND_X);
  }
  drawDigit(oneSecond, ONE_SECOND_X);
  SDL_RenderPresent(renderer);
  return interval;
}

int main() {
  SDL_Window *window;
  SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window,
                              &renderer);
  SDL_RenderSetLogicalSize(renderer, 31, 7);
  drawDigit(hour / 10, TEN_HOUR_X);
  drawDigit(hour % 10, ONE_HOUR_X);
  drawDigit(minute / 10, TEN_MINUTE_X);
  drawDigit(minute % 10, ONE_MINUTE_X);
  drawDigit(second / 10, TEN_SECOND_X);
  auto timer = SDL_AddTimer(1e3, loop, nullptr);
  for (SDL_Event event; true;) {
    if (SDL_PollEvent(&event) != 0) {
      if (SDL_QUIT == event.type) {
        break;
      }
    } else {
      SDL_Delay(99);
    }
  }
  SDL_RemoveTimer(timer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
