#include "Game/SpaceGame.h"
#include "Renderer/Texture.h"

using namespace std;

#define JSON_READ(value, data) viper::json::Read(value, #data, data)

class Animal {
public:
    virtual void Speak() = 0;
};

class Cat : public Animal {
public:
    void Speak() override { cout << "meow\n"; }
};

class Dog : public Animal {
public:
    void Speak() override { cout << "woof\n"; }
    void Fetch() { cout << "got the ball!\n"; }
};

class Bird : public Animal {
public:
    void Speak() override { cout << "cheap\n"; }
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
    // load the json data from a file
    string buffer;
    viper::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    cout << buffer << endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::json::Load("json.txt", document);

    // read/show the data from the json file
    string name;
    int age;
    float speed;
    bool isAwake;
    viper::vec2 position;
    viper::vec3 color;

    // read the json data
    viper::json::Read(document, "name", name);
    viper::json::Read(document, "age", age);
    viper::json::Read(document, "speed", speed);
    viper::json::Read(document, "isAwake", isAwake);
    viper::json::Read(document, "position", position);
    viper::json::Read(document, "color", color);

    // show the data
    cout << name << " " << age << " " << speed << " " << isAwake << endl;
    cout << position.x << " " << position.y << endl;
    cout << color.r << " " << color.g << " " << color.b << " " << endl;

    // initialize engine
    viper::Logger::Warning("initialize engine...");
    viper::GetEngine().Initialize();

    // initialize game
    unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
    game->Initialize();

    // initialize sounds
    AUDIO.AddSound("bass.wav", "bass");
    AUDIO.AddSound("snare.wav", "snare");
    AUDIO.AddSound("clap.wav", "clap");
    AUDIO.AddSound("close-hat.wav", "close-hat");
    AUDIO.AddSound("open-hat.wav", "open-hat");


	auto texture = viper::ResourceManager::Instance().Get<viper::Texture>("luigi.jpg", RENDERER);

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
        game->Update(TIME.GetDeltaTime());

        if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
        viper::vec3 color{ 0, 0, 0 };
        RENDERER.SetColor(color.r, color.g, color.b);
        RENDERER.Clear();

        game->Draw(RENDERER);
        //RENDERER.DrawTexture(texture.get(), 30.0f,30.0f,4.0f,45.0f);
        RENDERER.Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
