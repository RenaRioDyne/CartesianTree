#include <cstdio>
#include <cstring>

// forward decl
int lccs_dp_main(int, char**);
int lccs_constructive_main(int, char**);

int main(int argc, char **argv)
{
    if (argc == 0) {
        fprintf(stderr, "Usage: %s <lccs> [args]\n", argv[0]);
        return -1;
    }

    if (!strcmp(argv[1], "dp"))
    {
        lccs_dp_main(argc-1, argv+1);
    }

    if (!strcmp(argv[1], "constructive")){
        lccs_constructive_main(argc-1, argv+1);
    }

    if (!strcmp(argv[1], "all")){
        lccs_dp_main(argc-1, argv+1);
        lccs_constructive_main(argc-1, argv+1);
    }


    return 0;
}