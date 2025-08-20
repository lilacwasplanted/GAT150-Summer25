#include "Game/SpaceGame.h"

class Animal {
public:
    virtual void Speak() = 0;
};

class Cat : public Animal {
public:
    void Speak() override { std::cout << "meow\n"; }
};

class Dog : public Animal {
public:
    void Speak() override { std::cout << "woof\n"; }
    void Fetch() { std::cout << "got the ball!\n"; }
};

class Bird : public Animal {
public:
    void Speak() override { std::cout << "cheap\n"; }
};

enum class AnimalType {
    Cat,
    Dog,
    Bird
};

Animal* CreateAnimal(AnimalType id) {
    Animal* animal = nullptr;
    switch (id) {
    case AnimalType::Cat:
        animal = new Cat;
        break;
    case AnimalType::Dog:
        animal = new Dog;
        break;
    case AnimalType::Bird:
        animal = new Bird;
        break;
    default:
        break;
    }

    return animal;
}

int main(int argc, char* argv[]) {
    viper::file::SetCurrentDirectory("Assets");
    viper::Logger::Info("current directory {}", viper::file::GetCurrentDirectory());

    auto animal = CreateAnimal(AnimalType::Bird);
    animal->Speak();
    auto dog = dynamic_cast<Dog*>(animal);
    if (dog) {
        dog->Fetch();
    }

    // initialize engine
    viper::Logger::Warning("initialize engine...");
    viper::GetEngine().Initialize();

    // initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    // initialize sounds
    viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
        viper::vec3 color{ 0, 0, 0 };
        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw(viper::GetEngine().GetRenderer());

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
