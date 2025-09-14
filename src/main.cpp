#include "config.h"
#include "Core/Engine.h"
#include "TestApplication.h"

int main()
{
    Crumb::Engine engine(720, 520, "Crumb Engine");

    if (!engine.initialize())
    {
        return -1;
    }

    engine.setApplication(std::make_unique<Crumb::TestApplication>());

    engine.run();

    return 0;
}