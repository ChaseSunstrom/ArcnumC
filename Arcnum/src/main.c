#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define SPARK_DEFINE_ALL_ALIASES
#include <spark.h>
#include <stdio.h>
#include <string.h>

i32 main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Application app = CreateApplication(
        CreateWindow(
            CreateWindowData("Hello", 1000, 1000, SPARK_FALSE)
        )
    );

    UpdateApplication(app);

    DestroyApplication(app);

    return 0;
}
