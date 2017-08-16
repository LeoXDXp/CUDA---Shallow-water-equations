#include <iostream>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <stdio.h>

#include "asc_reader.h"
#include "asc_writer.h"

static bool validateGridsize(const char* flagname, int value)
{
    if (value >= 0)
        { return true; }
    std::cout << "Invalid value for --" << flagname << ": "
              << value << std::endl;
    return false;
}

DEFINE_int32(gridsize, 512, "gridsize for new file.");

static const bool gridsize_dummy = gflags::RegisterFlagValidator(&FLAGS_gridsize, &validateGridsize);

int main(int argc, char ** argv)
{
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    // checking command line arguments
    if (argc < 2)
    {
        std::cerr << "You have to specify a scene file." << std::endl;
        return -1;
    }

    CHECK_STRNE(argv[1], "") << "No source file specified.";
    CHECK_STRNE(argv[2], "") << "No destination file specified.";

    float* landscapeheightmap;
    int heightmapheight;
    int heightmapwidth;
    readASC(argv[1], heightmapwidth, heightmapheight, landscapeheightmap);

    int gridsize = FLAGS_gridsize;
    writeASC(argv[2], heightmapwidth, gridsize, landscapeheightmap);


    return 0;
}
