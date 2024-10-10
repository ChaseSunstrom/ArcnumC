#define SPARK_DEFINE_ALL_ALIASES
#include <spark.h>
#include <stdio.h>
#include <string.h>

i32 main()
{
    Application app = CreateApplication(
        CreateWindow(CreateWindowData("Hello", 1000, 1000, SPARK_FALSE))
    );

    UpdateApplication(app);

    DestroyApplication(app);

    return 0;
}
