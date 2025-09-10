#include <map>
#include <iostream>
#include <cmath>
#include "graphic.hpp"
#include "car.hpp"
#include "font.hpp"
#include "sound.hpp"

static std::map<std::string, Car> cars {
    {"Kustar", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 134,
        .acceleration = 15'500,
        .reverse = 5,
        .weight = {162},
        .steerspeed = {75},
        .anglerot = {},
        .hp = {100},
        .name = {"Kustar"},
        .skin = {"Kustar"},
        .sound_engine = {"I4"},
        .sound_nitro = {},
    }},
    {"Bullet", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 152,
        .acceleration = 16'500,
        .reverse = 5,
        .weight = {175},
        .steerspeed = {84},
        .anglerot = {},
        .hp = {100},
        .name = {"Bullet"},
        .skin = {"Bullet"},
        .sound_engine = {"V8"},
        .sound_nitro = {},
    }},
    {"Vextune", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 176,
        .acceleration = 14'500,
        .reverse = 5,
        .weight = {189},
        .steerspeed = {64},
        .anglerot = {},
        .hp = {100},
        .name = {"Vextune"},
        .skin = {"Vextune"},
        .sound_engine = {"I4"},
        .sound_nitro = {},
    }},
    {"Bowler", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 196,
        .acceleration = 17'500,
        .reverse = 5,
        .weight = {239},
        .steerspeed = {92},
        .anglerot = {},
        .hp = {100},
        .name = {"Bowler"},
        .skin = {"Bowler"},
        .sound_engine = {"V6"},
        .sound_nitro = {},
    }},
    {"Banger", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 184,
        .acceleration = 18'500,
        .reverse = 5,
        .weight = {169},
        .steerspeed = {74},
        .anglerot = {},
        .hp = {100},
        .name = {"Banger"},
        .skin = {"Banger"},
        .sound_engine = {"I4"},
        .sound_nitro = {},
    }},
    {"Ralier GT", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 204,
        .acceleration = 20'500,
        .reverse = 5,
        .weight = {201},
        .steerspeed = {64},
        .anglerot = {},
        .hp = {100},
        .name = {"Ralier GT"},
        .skin = {"Ralier GT"},
        .sound_engine = {"V8"},
        .sound_nitro = {},
    }},
    { "Bowler XL", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 232,
        .acceleration = 19'500,
        .reverse = 5,
        .weight = {228},
        .steerspeed = {94},
        .anglerot = {},
        .hp = {100},
        .name = {"Bowler XL"},
        .skin = {"Bowler XL"},
        .sound_engine = {"I4"},
        .sound_nitro = {},
    }},
    { "Vegas", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 262,
        .acceleration = 21'500,
        .reverse = 5,
        .weight = {228},
        .steerspeed = {94},
        .anglerot = {},
        .hp = {100},
        .name = {"Vegas"},
        .skin = {"Vegas"},
        .sound_engine = {"V6"},
        .sound_nitro = {},
    }},
    { "BMW Bonus", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 462,
        .acceleration = 25'500,
        .reverse = 5,
        .weight = {128},
        .steerspeed = {54},
        .anglerot = {},
        .hp = {100},
        .name = {"BMW Bonus"},
        .skin = {"BMW Bonus"},
        .sound_engine = {"I4"},
        .sound_nitro = {},
    }},
    { "CHARGER Bonus", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 462,
        .acceleration = 25'500,
        .reverse = 5,
        .weight = {118},
        .steerspeed = {54},
        .anglerot = {},
        .hp = {100},
        .name = {"CHARGER Bonus"},
        .skin = {"CHARGER Bonus"},
        .sound_engine = {"V8"},
        .sound_nitro = {},
    }},
    { "SUPRA Bonus", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 422,
        .acceleration = 28'500,
        .reverse = 5,
        .weight = {118},
        .steerspeed = {54},
        .anglerot = {},
        .hp = {100},
        .name = {"SUPRA Bonus"},
        .skin = {"SUPRA Bonus"},
        .sound_engine = {""},
        .sound_nitro = {},
    }},
    { "SCHOOL BUS BONUS", Car {
        .x = {},
        .y = {},
        .vx = {},
        .vy = {},
        .speed_max = 98,
        .acceleration = 18'500,
        .reverse = 5,
        .weight = {118},
        .steerspeed = {54},
        .anglerot = {},
        .hp = {100},
        .name = {"SCHOOL BUS BONUS"},
        .skin = {"SCHOOL BUS BONUS"},
        .sound_engine = {"I4"},
        .sound_nitro = {},
    }},
};

Car make_player(bool is_server) {
  Car ret = cars.at("BMW Bonus");
  ret.type = (is_server ? Type::server : Type::client);
  return ret;
}

Car make_bot() {
  Car ret = cars.at("SUPRA Bonus");
  ret.type = Type::bot;
  return ret;
}

void draw(sf::RenderWindow& window, const Car& car, float scale, float angle) {
    draw_texture(window, car.x, car.y, car.skin, scale, angle);
    float speed = std::sqrt(car.vx*car.vx + car.vy*car.vy);
    draw_text(window, "Speed: " + std::to_string(int(speed)), car.x, car.y+40, 18, sf::Color(255,0,0));
}

static void physic(Car& car, float dt, bool left, bool right, bool accel, bool reverce) {
    float speed = std::sqrt(car.vx*car.vx + car.vy*car.vy);
    speed = std::min<float>(speed, car.speed_max);
    //std::cout << "speed: " << speed;

    //car.anglerot = sf::radians(std::atan2(car.vx, car.vy)).asDegrees();

    auto steerspeed = car.steerspeed;
    auto speed_ratio = std::min<float>(speed / SPEEDCHECK, 1.0f);
    steerspeed *= speed_ratio;
    if (left) car.anglerot -= steerspeed * dt;
    if (right) car.anglerot += steerspeed * dt;
    
    // Angle to Vector
    auto rad = sf::degrees(car.anglerot).asRadians();
    car.anglerot = std::fmod(car.anglerot, 360.0f);
    if (car.anglerot < 0)
        car.anglerot = 360.0 - car.anglerot;
    auto dx = std::cos(rad);
    auto dy = std::sin(rad);
    //std::cout << ", angle " << car.anglerot;
    
    // Speed Addition
    if (accel) {
        speed += car.acceleration * dt;
    }
    dx *= speed;
    dy *= speed;

    static int state = 0;
    if (!car.sound_engine.empty() && state % (120 * 1) == 0) {
        float speed_ratio = speed / car.speed_max;
        play_sound(car.sound_engine, 30.0f, 1.0f + speed_ratio * 0.2f);
    }
    state++;

    // resistance
    dx -= car.vx * FORCE;
    dy -= car.vy * FORCE;
    if (reverce) {
        dx -= car.vx * car.reverse * dt;
        dy -= car.vy * car.reverse * dt;
    }

    // difference between innertion and wheels
    
    // Moving from standing
    car.vx += dx / car.weight;
    car.vy += dy / car.weight;
    car.x += car.vx * dt;
    car.y += car.vy * dt;

    //std::cout << std::endl;
}

void update(Car& car, float dt) {
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    bool accel = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    bool reverce = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    //std::cout << "player: ";
    physic(car, dt, left, right, accel, reverce);
}

void update_client(Car& car, float dt) {
  /*
  bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
  bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
  bool accel = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
  bool reverce = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
  //std::cout << "player: ";
  physic(car, dt, left, right, accel, reverce);
  */
}

void update_bot(Car& car, float dt) {
    bool left = rand() % 4;
    //std::cout << "bot: ";
    physic(car, dt, left, !left, true, false);
}

void bound(Car& car) {
    if (car.x < 0) {
        car.x = 0;
        car.vx *= -0.5;
    }
    if (car.y < 0) {
        car.y = 0;
        car.vy *= -0.5;
    }
    if (car.x >= WINDOW_X) {
        car.x = WINDOW_X-1;
        car.vx *= -0.5;
    }
    if (car.y >= WINDOW_Y) {
        car.y = WINDOW_Y-1;
        car.vy *= -0.5;
    }
}

void collision_detect(Car& a, Car& b) {
    const auto dx = a.x - b.x;
    const auto dy = a.y - b.y;
    const auto radiiSum = a.hitbox + b.hitbox;
    bool collided = (dx * dx + dy * dy) < (radiiSum * radiiSum);
    if (collided) {
        a.vx *= -0.5;
        a.vy *= -0.5;
        b.vx *= -0.5;
        b.vy *= -0.5;
    }
}
